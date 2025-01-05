#pragma once
#include "ast_node.h"
#include "nodes/core.h"
#include "nodes/expr.h"
#include "spdlog/spdlog.h"
#include "util.h"
#include "visitor.h"
#include <fmt/core.h>
#include <fmt/format.h>
#include <string>
#include <variant>

namespace AST {
class PrintVisitor : public AST::Visitor {
  private:
  int indent = 0;
  void print(std::string str, Opt<NodeId> id = std::nullopt)
  {
    std::string ind = "";
    for (int i = 0; i < indent; i++) {
      ind += "  ";
    }
    if (id.has_value()) {
      spdlog::info("{}|-{} ({})", ind, str, id.value());
    }
    else {
      spdlog::info("{}|-{}", ind, str);
    }
  }
  void wrap(std::function<void()> func)
  {
    indent += 1;
    func();
    indent -= 1;
  }

  public:
  void visit(const Crate& crate) override
  {
    print("Crate", crate.id);
    wrap([&] {
      for (const auto& child : crate.items) {
        visit(*child);
      }
    });
  };

  void visit(const Item& item) override
  {
    print("Item", item.id);
    wrap([&] {
      std::visit(overloaded {
        [this](const P<FnDef>& fn) {
          print("FnDef: " + fn->ident.identifier, fn->id);
          visit(*fn->signature);

          wrap([this, &fn]() { visit(*(fn.get()->body)); });
        },
        [this](const P<Mod>& mod) {
          visit(*mod);
        }
      }, item.kind);
    });
  }

  void visit(const Mod& mod) override
  {
    print("Mod: " + mod.ident.identifier, mod.id);
    wrap([&] {
      for (const auto& child : mod.items) {
        visit(*child);
      }
    });
  }

  void visit(const FnSig& sig) override {
    print("Signature", sig.id);
    wrap([&] {
      for (const auto& param : sig.inputs) {
        visit(*param);
      }
    });
  }

  void visit(const Param& param) override {
    if (param.mut) {
      print("Param mut", param.id);
    } else {
      print("Param", param.id);
    }
    wrap([&] {
      visit(*param.pat);
    });
  }

  void visit(const FnDef& fn) override
  {
    print("FnDef", fn.id);
    wrap([&] {
      visit(*fn.signature);
      visit(*fn.body);
    });
  }

  void visit(const Block& node) override
  {
    print("Block", node.id);
    wrap([&]() {
      for (const auto& child : node.statements) {
        visit(*child);
      }
    });
  }

  void visit(const Expr& expr) override
  {
    print("Expr", expr.id);
    wrap([&]() {
      std::visit(overloaded {
        [this](const P<Ret>& ret) {
          print("Return", ret->id);
          visit(*ret->expr);
        },
        [this](const P<Print>& print_expr) {
          print("Return", print_expr->id);
          wrap([&] {
            std::visit(overloaded {
              [&](const std::string& s) { print("String" + s); },
              [&](const AST::Ident& ident) { print("Ident"); }
            }, print_expr->kind);
          });
        },
        [this](const P<Assign>& assign) {
          print("Assign", assign->id);
          print(fmt::format("LHS: {}", assign->lhs.identifier));
          visit(*assign->rhs);
        },
        [this](const Break& br) {
          print("Break", br.id);
        },
        [this](const P<If>& ifExpr) {
          print("If", ifExpr->id);
          wrap([&]{
            print("Condition");
            visit(*ifExpr->cond);
            print("Then");
            visit(*ifExpr->then_block);
            if (ifExpr->else_block.has_value()) {
              print("Else");
              visit(*ifExpr->else_block.value());
            }
          });
        },
        [this](const P<Loop>& loop) {
          print("Loop", loop->id);
          wrap([&]{
            visit(*loop->block);
          });
        },
        [this](const P<While>& whileExpr) {
          print("While", whileExpr->id);
          wrap([&]{
            Visitor::visit(*whileExpr);
          });
        },
        [this](const Lit& lit) {
          std::visit(
            overloaded {
                [&](const int64_t i) { print("Lit Int: " + std::to_string(i), lit.id); },
                [&](const std::string& s) { print("Lit String: " + s, lit.id); },
                [&](const bool& b) { print("Lit Bool: " + std::to_string(b), lit.id); },
                [&](const double& d) { print("Lit Float: " + std::to_string(d), lit.id); },
                [&](const std::monostate& m) { print("Lit Unit: ()", lit.id); }
            }, lit.kind);
        },
        [this](const P<Block>& block) {
          visit(*block);
        },
        [this](const Path& path) {
          visit(path);
        },
        [this](const P<Binary>& binary) {
          visit(*binary->lhs);
          print(fmt::format("BinOp: {}",
            std::visit(overloaded {
              [](const Bin::Add) { return "Add"; },
              [](const Bin::Sub) { return "Sub"; },
              [](const Bin::Mul) { return "Mul"; },
              [](const Bin::Div) { return "Div"; },
              [](const Bin::Mod) { return "Mod"; },
              [](const Bin::And) { return "And"; },
              [](const Bin::Or) { return "Or"; },
              [](const Bin::Eq) { return "Eq"; },
              [](const Bin::Ne) { return "Ne"; },
              [](const Bin::Lt) { return "Lt"; },
              [](const Bin::Le) { return "Le"; },
              [](const Bin::Gt) { return "Gt"; },
              [](const Bin::Ge) { return "Ge"; }
            }, binary->op))
          );
          visit(*binary->rhs);
        },
        [this](const P<Unary>& unary) {
          print(std::visit(overloaded {
            [&](const Un::Neg) { return "Neg"; },
            [&](const Un::Not) { return "Not"; },
            [&](const Un::Pos) { return "Pos"; }
          }, unary->op), unary->id);
          visit(*unary->expr);
        },
        [this](const P<Call>& call) {
          print("Call", call->id);
          wrap([this, &call]() {
            visit(call->path);
            for (const auto& param : call->params) {
              visit(*param);
            }
          });
        }
      }, expr.kind);
    });
  }

  void visit(const Stmt& stmt) override
  {
    print("Stmt", stmt.id);
    wrap([&]() {
      Visitor::visit(stmt);
    });
  }

  void visit(const Let& let) override
  {
    if (let.mut) {
      print("Let mut", let.id);
    } else {
      print("Let", let.id);
    }
    wrap([this, &let]() {
      visit(*let.pat);
      std::visit(
          overloaded {
              [this](const Decl& decl) { print("Decl"); },
              [this](const P<Expr>& expr) {
                visit(*expr);
              } },
          let.kind);
    });
  }

  void visit(const Path& path) override
  {
    std::string path_str = "Path: ";
    for (const auto& seg : path.segments) {
      path_str = path_str + seg.ident.identifier;
    }
    print(path_str);
  }

  void visit(const Pat& pat) {
    std::visit(overloaded {
      [&](const Ident& ident) {
        print(fmt::format("Ident: {}", ident.identifier));
      }
    }, pat.kind);
  }
};
} // namespace AST
