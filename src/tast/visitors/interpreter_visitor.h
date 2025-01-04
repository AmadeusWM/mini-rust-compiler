#pragma once

#include "nodes/body.h"
#include "nodes/core.h"
#include "nodes/expr.h"
#include "nodes/type.h"
#include "visitors/tast_visitor.h"
#include <cstdint>
#include <exception>
#include <functional>
#include <iostream>
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

    Opt<SymbolValue> lookup(std::string ident) {
      for (auto it = scopes.rbegin(); it != scopes.rend(); ++it) {
        auto scope = *it;
        auto binding = scope.bindings.find(ident);
        if (binding != scope.bindings.end()) {
          return SymbolValue(binding->second);
        }
      }
      return Opt<SymbolValue>{};
    }

    Opt<SymbolValue*> lookup_ref(std::string ident) {
      for (auto it = scopes.rbegin(); it != scopes.rend(); ++it) {
        auto& scope = *it;
        auto binding = scope.bindings.find(ident);
        if (binding != scope.bindings.end()) {
          auto& value = binding->second;
          return {&value};
        }
      }
      return {};
    }

    SymbolValue* lookup_ref_or_throw(std::string ident) {
      auto result = lookup_ref(ident);
      if (!result.has_value()) {
        throw InterpeterException(fmt::format("cannot find identifier \"{}\"", ident));
      }
      else {
        return result.value();
      }
    }

    SymbolValue lookup_or_throw(std::string ident) {
      auto id = lookup(ident);
      if (!id.has_value()) {
        throw InterpeterException(fmt::format("cannot find identifier \"{}\"", ident));
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
        return visit(*body.expr);
      } catch (const ReturnException& e) {
        return e.value;
      }
    }

    SymbolValue visit(const Expr& expr) override {
      auto result = std::visit(overloaded {
        [&](const P<Block>& block) { return visit(*block); },
        [&](const P<Print>& printExpr) { return visit(*printExpr); },
        [&](const P<Ret>& ret) { return visit(*ret); },
        [&](const P<Assign>& assign) { return visit(*assign); },
        [&](const Break& br) { return visit(br); },
        [&](const P<Loop>& loop) { return visit(*loop); },
        [&](const P<If>& ifExpr) { return visit(*ifExpr); },
        [&](const Lit& lit) { return visit(lit); },
        [&](const AST::Ident& ident) { return visit(ident); },
        [&](const P<Binary>& binary) { return visit(*binary); },
        [&](const P<Unary>& unary) { return visit(*unary); },
        [&](const P<Call>& call) { return visit(*call); },
      }, expr.kind);
      // spdlog::debug("node {}: {}", expr.id, result.to_string());
      return result;
    }

    SymbolValue visit(const Print& printExpr) {
      std::visit(overloaded {
        [&](const std::string& s) {
          std::cout << s << std::endl;
        },
        [&](const AST::Ident& ident) {
          auto v = visit(ident);
          std::cout << v.to_string() << std::endl;
        }
      }, printExpr.kind);
      return {UnitValue{}};
    }

    SymbolValue visit(const Assign& assign) override {
      SymbolValue value = visit(*assign.rhs);
      SymbolValue* ref = scopes.lookup_ref_or_throw(assign.lhs.identifier);
      *ref = value;
      return SymbolValue{UnitValue{}};
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
                return SymbolValue(NumberValue(static_cast<int8_t>(i)));
              },
              [&](const I32) {
                return SymbolValue(NumberValue(static_cast<int32_t>(i)));
              },
            }, int_ty);
            return SymbolValue(NumberValue(i));
          }
          else {
            throw InterpeterException("Type is not an integer");
          }
          return SymbolValue(NumberValue(i));
        },
        [&](const bool& b) { return SymbolValue(BoolValue(b)); }
      }, lit.kind);
    }

    SymbolValue visit(const AST::Ident& ident) {
      return scopes.lookup_or_throw(ident.identifier);
    }

    SymbolValue visit(const Binary& binary) override {
      auto lhs = visit(*binary.lhs);
      auto rhs = visit(*binary.rhs);
      return std::visit(overloaded {
        [&](const NumberValue& l, const NumberValue& r) {
          return std::visit(overloaded {
            [&](const auto& l_value, const auto& r_value) {
              return std::visit(overloaded {
                [&](const AST::Bin::Add& add) {
                  return SymbolValue(NumberValue(l_value + r_value));
                },
                [&](const AST::Bin::Sub& sub) {
                  return SymbolValue(NumberValue(l_value - r_value));
                },
                [&](const AST::Bin::Mul& mul) {
                  return SymbolValue(NumberValue(l_value * r_value));
                },
                [&](const AST::Bin::Div& div) {
                  return SymbolValue(NumberValue(l_value / r_value));
                },
                [&](const AST::Bin::Mod& mod) {
                  if constexpr (std::is_integral_v<decltype(l_value)> && std::is_integral_v<decltype(r_value)>) {
                    return SymbolValue(NumberValue(l_value % r_value));
                  } else {
                    throw InterpeterException("Modulo operation is not supported for non-integer types");
                    return SymbolValue(UnitValue{});
                  }
                },
                [&](const AST::Bin::And& and_op) {
                  return SymbolValue(BoolValue(l_value && r_value));
                },
                [&](const AST::Bin::Or& or_op) {
                  return SymbolValue(BoolValue(l_value || r_value));
                },
                [&](const AST::Bin::Eq& eq) {
                  return SymbolValue(BoolValue(l_value == r_value));
                },
                [&](const AST::Bin::Ne& ne) {
                  return SymbolValue(BoolValue(l_value != r_value));
                },
                [&](const AST::Bin::Lt& lt) {
                  return SymbolValue(BoolValue(l_value < r_value));
                },
                [&](const AST::Bin::Le& le) {
                  return SymbolValue(BoolValue(l_value <= r_value));
                },
                [&](const AST::Bin::Gt& gt) {
                  return SymbolValue(BoolValue(l_value > r_value));
                },
                [&](const AST::Bin::Ge& ge) {
                  return SymbolValue(BoolValue(l_value >= r_value));
                }
              }, binary.op);
            }
          }, l, r);
        },
        [&](const BoolValue& l, const BoolValue& r) {
          return std::visit(overloaded {
            [&](const auto& l_value, const auto& r_value) {
              return std::visit(overloaded {
                [&](const AST::Bin::And& and_op) {
                  return SymbolValue(BoolValue(l_value && r_value));
                },
                [&](const AST::Bin::Or& or_op) {
                  return SymbolValue(BoolValue(l_value || r_value));
                },
                [&](const AST::Bin::Eq& eq) {
                  return SymbolValue(BoolValue(l_value == r_value));
                },
                [&](const AST::Bin::Ne& ne) {
                  return SymbolValue(BoolValue(l_value != r_value));
                },
                [&](const auto& op) {
                  throw InterpeterException("Operator is not implemented for bool");
                  return SymbolValue{UnitValue{}};
                }
              }, binary.op);
            }
          }, l, r);
        },
        [&](const auto& l, const auto& r) {
          throw InterpeterException("Type mismatch");
          return SymbolValue{UnitValue{}};
        }
      }, lhs.kind, rhs.kind);
    }

    SymbolValue visit(const Unary& unary) override {
      auto expr = visit(*unary.expr);
      return std::visit(overloaded {
        [&](const NumberValue& n) {
          return std::visit(overloaded {
            [&](const auto& n_value) {
              return std::visit(overloaded {
                [&](const AST::Un::Neg& neg) {
                  return SymbolValue(NumberValue(-n_value));
                },
                [&](const AST::Un::Pos& pos) {
                  return SymbolValue(NumberValue(n_value));
                },
                [&](const AST::Un::Not& not_op) {
                  return SymbolValue(BoolValue(!n_value));
                }
              }, unary.op);
            }
          }, n);
        },
        [&](const BoolValue& b) {
          return std::visit(overloaded {
            [&](const auto& b_value) {
              return std::visit(overloaded {
                [&](const AST::Un::Not& not_op) {
                  return SymbolValue(BoolValue(!b_value));
                },
                [&](const auto& op) {
                  throw InterpeterException("Operator is not implemented for bool");
                  return SymbolValue{UnitValue{}};
                }
              }, unary.op);
            }
          }, b);
        },
        [&](const auto& n) {
          throw InterpeterException("Type mismatch");
          return SymbolValue{UnitValue{}};
        }
      }, expr.kind);
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
