#pragma once

#include "nodes/body.h"
#include "nodes/core.h"
#include "nodes/expr.h"
#include "nodes/type.h"
#include "visitors/tast_visitor.h"
#include <cstdint>
#include <exception>
#include <variant>
namespace TAST {
  class ReturnException : public std::exception {
    public:
      SymbolValue value;
      ReturnException(SymbolValue value): value{value} {}
  };

  class BreakException : public std::exception {
    public:
      BreakException() {}
  };

  class InterpeterException : public std::runtime_error {
  public:
      InterpeterException(const std::string& message)
          : std::runtime_error("(Interpreter Error) " + message) {}
  };

  typedef uint64_t ScopeId;

  struct Scope {
    ScopeId id;
    std::map<std::string, SymbolValue> bindings;
  };

  struct Scopes {
    std::vector<Scope> scopes;
    Scopes(): scopes{} {}
    void push(Scope scope) {
      scopes.push_back(scope);
    }

    // pop until the scope with the given id is reached
    void pop(const Scope& scope) {
      Scope last = scopes.back();
      while (last.id != scope.id) {
        scopes.pop_back();
        last = scopes.back();
      }
      scopes.pop_back();
    }

    Opt<SymbolValue> lookup(std::string iden) {
      for (auto it = scopes.rbegin(); it != scopes.rend(); ++it) {
        auto scope = *it;
        auto binding = scope.bindings.find(iden);
        if (binding != scope.bindings.end()) {
          return SymbolValue(binding->second);
        }
      }
      return Opt<SymbolValue>{};
    }

    SymbolValue lookup_or_throw(std::string iden) {
      auto id = lookup(iden);
      if (!id.has_value()) {
        throw InterpeterException(fmt::format("cannot find identifier \"{}\"", iden));
      }
      return id.value();
    }

    void insert_binding(std::string name, SymbolValue value) {
      if (scopes.size() == 0) {
        throw InterpeterException(fmt::format("no scope to insert identifier \"{}\"", name));
      }
      scopes.back().bindings.insert({ name, value });
    }
  };

  class InterpreterVisitor : public Visitor<SymbolValue> {
    private:
    Scopes scopes;
    SymbolValue with_scope(NodeId id, std::function<SymbolValue()> body)
    {
      Scope scope = {
        .id = id,
      };
      scopes.push(scope);
      SymbolValue result = body();
      scopes.pop(scope);
      return result;
    }

    const Crate& crate;
    public:
    InterpreterVisitor(const Crate& crate) : crate{crate}, scopes() {}

    SymbolValue interpret() {
      return visit(crate);
    }

    SymbolValue visit(const Crate& crate) override {
      // find main
      Body* main_body = nullptr;
      for (const auto& [id, body] : crate.bodies) {
        spdlog::debug("body: {}", body->ns.to_string());
        if (body->ns.path[0] == "main") {
          main_body = body.get();
          break;
        }
      }
      if (main_body == nullptr) {
        throw InterpeterException("No main function found");
      }

      // create the global scope
      scopes = Scopes();

      visit(*main_body);
      return {UnitValue{}};
    }

    SymbolValue visit(const Body& body) override{
      try {
        return with_scope(body.id, [&]{
          return visit(*body.expr);
        });
      } catch (const ReturnException& e) {
        return e.value;
      }
    }

    SymbolValue visit(const Expr& expr) override {
      auto result = std::visit(overloaded {
        [&](const P<Block>& block) { return visit(*block); },
        [&](const P<Ret>& ret) { return visit(*ret); },
        [&](const Break& br) { return visit(br); },
        [&](const P<Loop>& loop) { return visit(*loop); },
        [&](const P<If>& ifExpr) { return visit(*ifExpr); },
        [&](const Lit& lit) { return visit(lit); },
        [&](const AST::Ident& ident) { return visit(ident); },
        [&](const P<Binary>& binary) { return visit(*binary); },
        [&](const P<Call>& call) { return visit(*call); },
      }, expr.kind);
      spdlog::debug("node {}: {}", expr.id, result.to_string());
      return result;
    }

    SymbolValue visit(const Break& br) {
      throw BreakException();
    }

    SymbolValue visit(const Loop& loop) override {
      while (true) {
        try {
          visit(*loop.block);
        } catch (const BreakException& e) {
          break;
        }
      }
      return {UnitValue{}};
    }

    SymbolValue visit(const If& ifExpr) override {
      auto cond = visit(*ifExpr.cond);
      if (cond.as_bool()) {
        return visit(*ifExpr.then_block);
      } else {
        if (ifExpr.else_block.has_value()) {
          return visit(*ifExpr.else_block.value());
        }
      }
      return {UnitValue{}};
    }

    SymbolValue visit(const Ret& ret) override {
      throw ReturnException(visit(*ret.expr));
    }

    SymbolValue visit(const Lit& lit) override {
      return std::visit(overloaded {
        [&](const std::string& s) {
          return SymbolValue(StrValue(s));
        },
        [&](const int& i) {
          if (std::holds_alternative<InferTy>(lit.ty.kind)) {
            const auto& infer = std::get<InferTy>(lit.ty.kind);
            if (std::holds_alternative<IntVar>(infer)) {
              return SymbolValue(static_cast<int32_t>(i));
            } else {
              throw InterpeterException(fmt::format("Node {} is not an inferrable integer", lit.id));
            }
          }
          else if (std::holds_alternative<IntTy>(lit.ty.kind)) {
            const auto& int_ty = std::get<IntTy>(lit.ty.kind);
            std::visit(overloaded {
              [&](const I8) {
                return SymbolValue(IntValue(static_cast<int8_t>(i)));
              },
              [&](const I32) {
                return SymbolValue(IntValue(static_cast<int32_t>(i)));
              },
            }, int_ty);
            return SymbolValue(IntValue(i));
          }
          else {
            throw InterpeterException("Type is not an integer");
          }
          return SymbolValue(IntValue(i));
        },
        [&](const bool& b) { return SymbolValue(BoolValue(b)); }
      }, lit.kind);
    }

    SymbolValue visit(const AST::Ident& ident) {
      return scopes.lookup_or_throw(ident.identifier);
    }

    SymbolValue visit(const Binary& binary) {
      auto lhs = visit(*binary.lhs);
      auto rhs = visit(*binary.rhs);
      if (binary.lhs->ty.isInt()) {
        auto l_int = std::get<IntValue>(lhs.kind);
        auto r_int = std::get<IntValue>(rhs.kind);
        return std::visit(overloaded {
          [&](const auto& l, const auto &r){ return SymbolValue(IntValue(l + r)); }
        }, l_int, r_int);
      } else if (binary.lhs->ty.isFloat()) {
        auto l_float = std::get<FloatValue>(lhs.kind);
        auto r_float = std::get<FloatValue>(rhs.kind);
        return std::visit(overloaded {
          [&](const auto& l, const auto &r){ return SymbolValue(FloatValue(l + r)); }
        }, l_float, r_float);
      } else {
        throw InterpeterException("Cannot add non-numeric types");
      }
    }

    SymbolValue visit(const Block& block) override {
      return with_scope(block.id, [&]{
        for (const auto& stmt : block.statements) {
          visit(*stmt);
        }
        if (block.expr.has_value()) {
          return visit(*block.expr.value());
        }
        return SymbolValue{UnitValue{}};
      });
    }

    SymbolValue visit(const Stmt& stmt) override {
      return std::visit(overloaded {
        [this](const P<Let>& let) { return visit(*let); },
        [this](const P<Expr>& expr) { return visit(*expr); },
        [this](const P<Semi>& semi) { return visit(*semi->expr); }
      }, stmt.kind);
      return {UnitValue{}};
    }

    SymbolValue visit(const Let& let) override {
      scopes.push({.id = let.id, .bindings = {}});
      if (let.initializer.has_value()){
        auto result = visit(*let.initializer.value());
        std::visit(overloaded {
          [&](const AST::Ident& ident) {
            scopes.insert_binding(ident.identifier, result);
          }
        }, let.pat->kind);
      }
      return {UnitValue{}};
    }

    SymbolValue visit(const Call& call) override {
      auto body_it = crate.bodies.find(call.callee);
      if (body_it == crate.bodies.end()) {
        throw InterpeterException(fmt::format("No function with id {}", call.callee));
      }
      const auto& body = *body_it->second;
      return with_scope(call.id, [&]{
        // todo: put the function arguments in the scope
        for (int i = 0; i < call.params.size(); i++) {
          const auto& call_param = call.params[i];
          const auto& callee_param = body.params[i];
          std::visit(overloaded {
           [&](const AST::Ident& ident)  {
              scopes.insert_binding(ident.identifier, visit(*call_param));
           }
          }, callee_param->pat->kind);
        }
        return visit(body);
      });
    }
  };
}
