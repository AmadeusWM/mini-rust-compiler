#pragma once

#include "infer_ctx.h"
#include "nodes/core.h"
#include "nodes/type.h"
#include "visitors/apply_infererence_visitor.h"
#include "visitors/tast_visitor.h"
#include <spdlog/spdlog.h>
#include <variant>
namespace TAST {
class TypecheckException : public std::runtime_error {
public:
    TypecheckException(const std::string& message)
        : std::runtime_error("(Type Check Error) " + message) {}
};

typedef uint64_t ScopeId;

struct Binding {
  NodeId id;
  bool mut;
  bool initialized;
};

struct TypeScope {
  ScopeId id;
  std::map<std::string, Binding> bindings;
};

struct TypeScopes {
  std::vector<TypeScope> scopes;
  TypeScopes(): scopes{} {}

  TypeScopes clone() {
    TypeScopes new_scopes;
    for (const auto& scope : scopes) {
      TypeScope new_scope;
      new_scope.id = scope.id;
      for (const auto& [key, binding] : scope.bindings) {
        new_scope.bindings[key] = binding;
      }
      new_scopes.scopes.push_back(new_scope);
    }
    return new_scopes;
  }

  void push(TypeScope scope) {
    scopes.push_back(scope);
  }

  // pop until the scope with the given id is reached
  void pop(const TypeScope& scope) {
    TypeScope last = scopes.back();
    while (last.id != scope.id) {
      scopes.pop_back();
      last = scopes.back();
    }
    scopes.pop_back();
  }

  Opt<Binding*> lookup(std::string iden) {
    for (auto it = scopes.rbegin(); it != scopes.rend(); ++it) {
      auto& scope = *it;
      auto binding = scope.bindings.find(iden);
      if (binding != scope.bindings.end()) {
        return Opt<Binding*>(&binding->second);
      }
    }
    return Opt<Binding*>{};
  }

  Binding* lookup_or_throw(std::string iden) {
    auto binding = lookup(iden);
    if (!binding.has_value()) {
      throw TypecheckException(fmt::format("cannot find identifier \"{}\"", iden));
    }
    return binding.value();
  }

  void insert_binding(std::string name, Binding binding) {
    if (scopes.size() == 0) {
      throw TypecheckException(fmt::format("no scope to insert identifier \"{}\"", name));
    }
    scopes.back().bindings.insert({ name, binding });
  }
};

/**
* inferencing: https://rustc-dev-guide.rust-lang.org/type-inference.html
*/
class TypecheckVisitor : public MutWalkVisitor {
  private:
  NodeId active_body_id;
  Crate& crate;
  InferCtx infer_ctx;
  TypeScopes scopes;

  void with_scope(NodeId id, std::function<void()> body)
  {
    TypeScope scope = {
      .id = id,
    };
    scopes.push(scope);
    body();
    scopes.pop(scope);
  }

  Ty lookup_type(std::string name) {
    auto binding = scopes.lookup(name);
    if (!binding.has_value()) {
      throw TypecheckException(fmt::format("cannot find identifier \"{}\"", name));
    }
    return infer_ctx.getType(binding.value()->id);
  }

  public:
  TypecheckVisitor(Crate& crate) : crate{crate}{}

  void typecheck() {
    this->visit(crate);
  }

  void visit(Crate& crate) override {
    for (const auto& [key, body] : crate.bodies) {
      // reset the inference context for each body
      infer_ctx = InferCtx();
      visit(*body);
      // resolve all the types
      ApplyInferenceVisitor(infer_ctx).visit(*body);
    }
  }

  void visit(Body& body) override {
    infer_ctx.add(body.id, body.ty);
    active_body_id = body.id;
    with_scope(body.id, [&]{
      for (const auto& param : body.params) {
        visit(*param);
      }
      visit(*body.expr);
    });
  }

  void visit(Param& param){
    std::visit(overloaded {
      [&](const AST::Ident& ident) {
        scopes.insert_binding(ident.identifier, { .id = param.id, .mut = param.mut, .initialized = true });
        infer_ctx.add(param.id, param.ty);
      }
    }, param.pat->kind);
  }
  void visit(Block& block) override {
    with_scope(block.id, [&]{
      for (const auto& stmt : block.statements) {
        visit(*stmt);
      }
      if (block.expr.has_value()) {
        visit(*block.expr.value());
        infer_ctx.eq(block.id, block.expr.value()->id);
      } else {
        infer_ctx.add(block.id, Ty{Unit{}});
      }
    });
  }

  void visit(Stmt& stmt) override {
    std::visit(overloaded {
      [this](const P<Let>& let) { visit(*let); },
      [this](const P<Expr>& expr) { visit(*expr); },
      [this](const P<Semi>& semi) { visit(*semi->expr); }
    }, stmt.kind);
  }
  void visit(Let& let) override {
    scopes.push(TypeScope{let.id, {}});
    if (let.initializer.has_value()) {
      visit(*let.initializer.value());
      std::visit(overloaded {
        [this, &let](const AST::Ident& ident) {
          scopes.insert_binding(ident.identifier, {.id = let.id, .mut = let.mut, .initialized = true } );

          infer_ctx.add(let.id, let.ty);
          infer_ctx.eq(let.id, let.initializer.value()->id);
        }
      }, let.pat->kind);
    }
    else {
      std::visit(overloaded {
        [this, &let](const AST::Ident& ident) {
          scopes.insert_binding(ident.identifier, { .id = let.id, .mut = let.mut, .initialized = false });
          infer_ctx.add(let.id, let.ty);
        }
      }, let.pat->kind);
    }
  }

  void visit(Expr& expr) override {
    spdlog::debug("visiting: {}", expr.id);
    std::visit(overloaded {
      [&](P<Print>& printExpr) {
        std::visit(overloaded {
          [&](const AST::Ident& ident) {
            auto binding = scopes.lookup_or_throw(ident.identifier);
            if (!binding->initialized) {
              throw TypecheckException(fmt::format("Cannot print variable {}, it is not yet initialized", ident.identifier));
           }
          },
          [&](const auto& other) {}
        }, printExpr->kind);
        infer_ctx.add(expr.id, Ty { Unit{} });
      },
      [&](P<Block>& block) {
        visit(*block);
        infer_ctx.eq(expr.id, block->id);
      },
      [&](P<Ret>& ret) {
        visit(*ret);
        infer_ctx.eq(ret->id, active_body_id);
        infer_ctx.eq(expr.id, ret->id);
      },
      [&](P<Assign>& assign) {
        visit(*assign);
        // TODO: also equal to function body's type?
        infer_ctx.add(expr.id, {InferTy{TyVar{}}});
      },
      [&](Break& ret) {
        infer_ctx.add(expr.id, {InferTy{TyVar{}}});
      },
      [&](P<Loop>& loop){
        visit(*loop);
        infer_ctx.eq(expr.id, loop->block->id);
      },
      [&](P<If>& ifExpr){
        visit(*ifExpr);
        infer_ctx.eq(expr.id, ifExpr->then_block->id);
        if (ifExpr->else_block.has_value()) {
          infer_ctx.eq(expr.id, ifExpr->else_block.value()->id);
        }
      },
      [&](Lit& lit) {
        visit(lit);
        infer_ctx.eq(expr.id, lit.id);
      },
      [&](AST::Ident& ident) {
        auto binding = scopes.lookup_or_throw(ident.identifier);
        if (!binding->initialized) {
          throw TypecheckException(fmt::format("Variable {} is used, but not yet initialized", ident.identifier));
        }
        infer_ctx.eq(expr.id, binding->id);
      },
      [&](P<Binary>& binary) {
        visit(*binary);
        infer_ctx.eq(expr.id, binary->id);
      },
      [&](P<Unary>& unary) {
        visit(*unary);
        infer_ctx.eq(expr.id, unary->id);
      },
      [&](P<Call>& call) {
        visit(*call);
        infer_ctx.eq(expr.id, call->id);
      },
    }, expr.kind);
  }

  void visit(Assign& assign) override {
    visit(*assign.rhs);
    Binding* binding = scopes.lookup_or_throw(assign.lhs.identifier);
    if (!binding->mut) {
      throw std::runtime_error(fmt::format("Cannot assign to immutable variable {}", assign.lhs.identifier));
    }
    infer_ctx.eq(binding->id, assign.rhs->id);
    spdlog::debug("Settings {} to initialized!", assign.lhs.identifier);
    binding->initialized = true;
  }

  void visit(Loop& loop) override {
    with_scope(loop.id, [&]{
      visit(*loop.block);
      infer_ctx.eq(loop.id, loop.block->id);
    });
  }

  void visit(If& ifExpr) override {
    auto else_scopes = scopes.clone(); // save scopes before visiting then block (for else)
    visit(*ifExpr.cond);
    infer_ctx.eq(ifExpr.cond->id, {BoolTy{}});

    visit(*ifExpr.then_block);
    auto if_scopes = scopes.clone(); // save scopes after visiting then block
    if (ifExpr.else_block.has_value()) {
      this->scopes = else_scopes;
      visit(*ifExpr.else_block.value());
      infer_ctx.eq(ifExpr.then_block->id, ifExpr.else_block.value()->id);

      // check if variables are eith initialized or not initialized in both branches
      for (const auto& scope : if_scopes.scopes) {
        for (auto& [ident, binding] : scope.bindings) {
          const auto if_initialized = binding.initialized;
          const auto else_binding = this->scopes.lookup_or_throw(ident);
          spdlog::debug("looked up: {}", ident);
          spdlog::debug("\t if initialized: {}", binding.initialized);
          spdlog::debug("\t else initialized: {}", else_binding->initialized);
          const auto else_initialized = else_binding->initialized;
          if (if_initialized != else_initialized) {
            throw std::runtime_error(
              fmt::format("Variable {} must be initialized in both branches", ident));
          }
        }
      }
    }
  }

  void visit(Ret& ret) override {
    visit(*ret.expr);
    infer_ctx.eq(ret.id, ret.expr->id);
  }

  void visit(Lit& lit) override {
    infer_ctx.add(lit.id, resolve_lit(lit));
  }

  void visit(Binary& bin) override {
    visit(*bin.lhs);
    visit(*bin.rhs);
    // infer types
    std::visit(overloaded {
      [&](const AST::Bin::Add& add) {
        infer_ctx.eq(bin.lhs->id, bin.rhs->id);
        infer_ctx.add(bin.id, infer_ctx.getType(bin.lhs->id));
      },
      [&](const AST::Bin::Sub& sub) {
        infer_ctx.eq(bin.lhs->id, bin.rhs->id);
        infer_ctx.add(bin.id, infer_ctx.getType(bin.lhs->id));
      },
      [&](const AST::Bin::Mul& mul) {
        infer_ctx.eq(bin.lhs->id, bin.rhs->id);
        infer_ctx.add(bin.id, infer_ctx.getType(bin.lhs->id));
      },
      [&](const AST::Bin::Div& div) {
        infer_ctx.eq(bin.lhs->id, bin.rhs->id);
        infer_ctx.add(bin.id, infer_ctx.getType(bin.lhs->id));
      },
      [&](const AST::Bin::Mod& mod) {
        infer_ctx.eq(bin.lhs->id, bin.rhs->id);
        infer_ctx.add(bin.id, infer_ctx.getType(bin.lhs->id));
      },
      [&](const AST::Bin::And& and_op) {
        infer_ctx.eq(bin.lhs->id, bin.rhs->id);
        infer_ctx.add(bin.id, Ty{BoolTy{}});
      },
      [&](const AST::Bin::Or& or_op) {
        infer_ctx.eq(bin.lhs->id, bin.rhs->id);
        infer_ctx.add(bin.id, Ty{BoolTy{}});
      },
      [&](const AST::Bin::Eq& eq) {
        infer_ctx.eq(bin.lhs->id, bin.rhs->id);
        infer_ctx.add(bin.id, Ty{BoolTy{}});
      },
      [&](const AST::Bin::Ne& ne) {
        infer_ctx.eq(bin.lhs->id, bin.rhs->id);
        infer_ctx.add(bin.id, Ty{BoolTy{}});
      },
      [&](const AST::Bin::Lt& lt) {
        infer_ctx.eq(bin.lhs->id, bin.rhs->id);
        infer_ctx.add(bin.id, Ty{BoolTy{}});
      },
      [&](const AST::Bin::Le& le) {
        infer_ctx.eq(bin.lhs->id, bin.rhs->id);
        infer_ctx.add(bin.id, Ty{BoolTy{}});
      },
      [&](const AST::Bin::Gt& gt) {
        infer_ctx.eq(bin.lhs->id, bin.rhs->id);
        infer_ctx.add(bin.id, Ty{BoolTy{}});
      },
      [&](const AST::Bin::Ge& ge) {
        infer_ctx.eq(bin.lhs->id, bin.rhs->id);
        infer_ctx.add(bin.id, Ty{BoolTy{}});
      }
    }, bin.op);

    Ty lhs_ty = infer_ctx.getType(bin.lhs->id);
    Ty rhs_ty = infer_ctx.getType(bin.rhs->id);
    Ty ty = lhs_ty.resolve(rhs_ty).value();

    std::visit(overloaded {
      [&](const AST::Bin::Add& add) {
        if (!(ty.isInt() || ty.isFloat())) {
          throw TypecheckException("Invalid types for operator +");
        }
      },
      [&](const AST::Bin::Sub& sub) {
        if (!(ty.isInt() || ty.isFloat())) {
          throw TypecheckException("Invalid types for operator -");
        }
      },
      [&](const AST::Bin::Mul& mul) {
        if (!(ty.isInt() || ty.isFloat())) {
          throw TypecheckException("Invalid types for operator *");
        }
      },
      [&](const AST::Bin::Div& div) {
        if (!(ty.isInt() || ty.isFloat())) {
          throw TypecheckException("Invalid types for operator /");
        }
      },
      [&](const AST::Bin::Mod& mod) {
        if (!(ty.isInt() || ty.isFloat())) {
          throw TypecheckException("Invalid types for operator %");
        }
      },
      [&](const AST::Bin::And& and_op) {
        if (!ty.isBool()) {
          throw TypecheckException("Invalid types for operator &&");
        }
      },
      [&](const AST::Bin::Or& or_op) {
        if (!ty.isBool()) {
          throw TypecheckException("Invalid types for operator ||");
        }
      },
      [&](const AST::Bin::Eq& eq) {
      },
      [&](const AST::Bin::Ne& ne) {
      },
      [&](const AST::Bin::Lt& lt) {
        if (!(ty.isInt() || ty.isFloat())) {
          throw TypecheckException("Invalid types for operator <");
        }
      },
      [&](const AST::Bin::Le& le) {
        if (!(ty.isInt() || ty.isFloat())) {
          throw TypecheckException("Invalid types for operator <=");
        }
      },
      [&](const AST::Bin::Gt& gt) {
        if (!(ty.isInt() || ty.isFloat())) {
          throw TypecheckException("Invalid types for operator >");
        }
      },
      [&](const AST::Bin::Ge& ge) {
        if (!(ty.isInt() || ty.isFloat())) {
          throw TypecheckException("Invalid types for operator >=");
        }
      }
    }, bin.op);
  }

  void visit(Unary& unary) override {
    visit(*unary.expr);
    std::visit(overloaded {
      [&](const AST::Un::Neg& neg) {
        infer_ctx.add(unary.id, infer_ctx.getType(unary.expr->id));
      },
      [&](const AST::Un::Pos& pos) {
        infer_ctx.add(unary.id, infer_ctx.getType(unary.expr->id));
      },
      [&](const AST::Un::Not& not_op) {
        infer_ctx.add(unary.id, Ty{BoolTy{}});
      },
    }, unary.op);

    Ty ty = infer_ctx.getType(unary.expr->id);

    std::visit(overloaded {
      [&](const AST::Un::Neg& neg) {
        if (!(ty.isInt() || ty.isFloat())) {
          throw TypecheckException("Invalid type for operator -");
        }
      },
      [&](const AST::Un::Pos& pos) {
        if (!(ty.isInt() || ty.isFloat())) {
          throw TypecheckException("Invalid type for operator +");
        }
      },
      [&](const AST::Un::Not& not_op) {
        if (!ty.isBool()) {
          throw TypecheckException("Invalid type for operator !");
        }
      }
    }, unary.op);
  }

  Ty resolve_lit(Lit& lit) {
    return std::visit(overloaded {
      [&](int64_t i) { return Ty(InferTy(IntVar{})); },
      [&](std::string s) { return Ty(StrTy{}); },
      [&](bool b) { return Ty(BoolTy{}); },
      [&](double f) { return Ty(InferTy{FloatVar{}}); },
      [&](std::monostate m) { return Ty(Unit{}); }
    }, lit.kind);
  }

  void visit(Call& call) override {
    const auto& body = crate.bodies[call.callee];
    if (call.params.size() != body->params.size()) {
      throw TypecheckException(fmt::format("Function call to '{}' has {} arguments, but expected {}", body->id, call.params.size(), body->params.size()));
    }
    for (int i = 0; i < call.params.size(); i++) {
      const auto& call_param = call.params[i];
      const auto& callee_param = body->params[i];
      visit(*call_param);
      infer_ctx.add(callee_param->id, callee_param->ty);
      infer_ctx.eq(callee_param->id, call_param->id);
    }
    infer_ctx.add(body->id, body->ty);
    infer_ctx.eq(body->id, call.id);
  }
};
}
