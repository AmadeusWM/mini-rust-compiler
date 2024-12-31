#pragma once

#include "infer_ctx.h"
#include "nodes/core.h"
#include "visitors/apply_infererence_visitor.h"
#include "visitors/tast_visitor.h"
#include <spdlog/spdlog.h>
namespace TAST {
class TypecheckException : public std::runtime_error {
public:
    TypecheckException(const std::string& message)
        : std::runtime_error("(Type Check Error) " + message) {}
};

typedef uint64_t ScopeId;

struct TypeScope {
  ScopeId id;
  std::map<std::string, NodeId> bindings;
};

struct TypeScopes {
  std::vector<TypeScope> scopes;
  TypeScopes(): scopes{} {}
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

  Opt<NodeId> lookup(std::string iden) {
    for (auto it = scopes.rbegin(); it != scopes.rend(); ++it) {
      auto scope = *it;
      auto binding = scope.bindings.find(iden);
      if (binding != scope.bindings.end()) {
        return Opt<NodeId>(binding->second);
      }
    }
    return Opt<NodeId>{};
  }

  NodeId lookup_or_throw(std::string iden) {
    auto id = lookup(iden);
    if (!id.has_value()) {
      throw TypecheckException(fmt::format("cannot find identifier \"{}\"", iden));
    }
    return id.value();
  }

  void insert_binding(std::string name, NodeId id) {
    if (scopes.size() == 0) {
      throw TypecheckException(fmt::format("no scope to insert identifier \"{}\"", name));
    }
    scopes.back().bindings.insert({ name, id });
  }
};

/**
* inferencing: https://rustc-dev-guide.rust-lang.org/type-inference.html
*/
class TypecheckVisitor : public MutWalkVisitor {
  private:
  Crate& crate;
  InferCtx infer_ctx;
  TypeScopes scopes;

  void with_scope(NodeId id, std::function<void()> body)
  {
    spdlog::debug("entering scope: {}", id);
    TypeScope scope = {
      .id = id,
    };
    scopes.push(scope);
    body();
    spdlog::debug("exiting scope: {}", id);
    scopes.pop(scope);
  }

  Ty lookup_type(std::string name) {
    auto id = scopes.lookup(name);
    if (!id.has_value()) {
      throw TypecheckException(fmt::format("cannot find identifier \"{}\"", name));
    }
    return infer_ctx.getType(id.value());
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
   visit(*body.expr);
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
          spdlog::debug("1");
          scopes.insert_binding(ident.identifier, let.id);
          spdlog::debug("2");

          infer_ctx.add(let.id, let.ty);
          spdlog::debug("3");
          infer_ctx.eq(let.id, let.initializer.value()->id);
          spdlog::debug("4");
        }
      }, let.pat->kind);
    }
    else {
      std::visit(overloaded {
        [this, &let](const AST::Ident& ident) {
          scopes.insert_binding(ident.identifier, let.id);
          infer_ctx.add(let.id, let.ty);
        }
      }, let.pat->kind);
    }
  }

  void visit(Expr& expr) override {
    spdlog::debug("visiting: {}", expr.id);
    std::visit(overloaded {
      [&](P<Block>& block) {
        visit(*block);
        infer_ctx.eq(expr.id, block->id);
      },
      [&](Lit& lit) { infer_ctx.add(expr.id, resolve_lit(lit)); },
      [&](AST::Ident& ident) {
        auto id = scopes.lookup_or_throw(ident.identifier);
        infer_ctx.eq(expr.id, id);
      },
      [&](P<Binary>& binary) {
        resolve_binary(*binary);
        infer_ctx.eq(expr.id, binary->lhs->id);
        infer_ctx.eq(expr.id, binary->rhs->id);
      },
      [&](P<Call>& call) {
        resolve_call(*call);
        infer_ctx.eq(expr.id, call->id);
      },
    }, expr.kind);
  }

  Ty resolve_call(Call& call) {
    // this->crate.bodies;
    return {};
  }

  Ty resolve_binary(Binary& bin) {
    visit(*bin.lhs);
    visit(*bin.rhs);

    // TODO: proper testing between types (e.g. strings cannot be added)
    Opt<Ty> ty = bin.lhs->ty.resolve(bin.rhs->ty);
    if (ty.has_value()) {
      return ty.value();
    }
    else {
      throw TypecheckException(fmt::format("Binary operation between incompattible types '{}' and '{}' at nodes: {} and {}", bin.lhs->ty.to_string(), bin.rhs->ty.to_string(), bin.lhs->id, bin.rhs->id));
    }
  }

  Ty resolve_lit(Lit& lit) {
    return std::visit(overloaded {
      [&](int i) { return Ty(InferTy(IntVar{})); },
      [&](std::string s) { return Ty(StrTy{}); }
    }, lit.kind);
  }

  void visit(Call& call) override {

  }
};
}
