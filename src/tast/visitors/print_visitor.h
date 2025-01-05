#pragma once

#include "nodes/core.h"
#include "util.h"
#include "visitors/tast_visitor.h"
#include <variant>
namespace TAST {
class PrintVisitor : public WalkVisitor {
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

  void print(std::string str, Ty ty, Opt<NodeId> id = std::nullopt) {
    print(str + " -> " + ty.to_string(), id);
  }

  void wrap(std::function<void()> func)
  {
    indent += 1;
    func();
    indent -= 1;
  }
public:
  void visit(const Crate& crate) {
    print("Crate");
    wrap([&] {
      for (const auto& [key, body] : crate.bodies) {
        visit(*body);
      }
    });
  }
  void visit(const Body& body) {
    print("Body");
    wrap([&] {
      std::string key_str = body.ns.to_string();
      print("Ns: " + key_str);
      print("Id: " + std::to_string(body.id));
      for (const auto& param : body.params) {
        visit(*param);
      }
      visit(*body.expr);
    });
  }

  void visit(const Param& param) {
    if (param.mut) {
      print(fmt::format("Param mut: {}", param.ty.to_string()), param.id);
    } else {
      print(fmt::format("Param: {}", param.ty.to_string()), param.id);
    }
    wrap([&] {
      visit(*param.pat);
    });
  }

  void visit(const Block& block) {
    print("Block", block.id);
    wrap([&] {
      WalkVisitor::visit(block);
    });
  }
  void visit(const Stmt& stmt) {
    print("Stmt", stmt.id);
    wrap([&] {
      WalkVisitor::visit(stmt);
    });
  }
  void visit(const Let& let) {
    if (let.mut) {
      print(fmt::format("Let mut: {}", let.ty.to_string()), let.id);
    } else {
      print(fmt::format("Let: {}", let.ty.to_string()), let.id);
    }
    wrap([&] {
      visit(*let.pat);
      WalkVisitor::visit(let);
    });
  }
  void visit(const Expr& expr) {
    print("Expr", expr.ty, expr.id);
    wrap([&] {
      std::visit(overloaded {
        [this](const P<Block>& block) { visit(*block); },
        [this](const P<Print>& printExpr) { visit(*printExpr); },
        [this](const P<Ret>& ret) { visit(*ret); },
        [this](const P<Loop>& loop) { visit(*loop); },
        [this](const P<If>& ifExpr) { visit(*ifExpr); },
        [this](const P<Assign>& assign) { visit(*assign); },
        [this](const Lit& lit) { visit(lit); },
        [this](const Break& breakExpr) { visit(breakExpr); },
        [this](const AST::Ident& ident) { print(fmt::format("Ident: {}", ident.identifier)); },
        [this](const P<Binary>& binary) {
          visit(*binary->lhs);
          print(fmt::format("BinOp: {}",
            std::visit(overloaded {
              [](const AST::Bin::Add) { return "Add"; },
              [](const AST::Bin::Sub) { return "Sub"; },
              [](const AST::Bin::Mul) { return "Mul"; },
              [](const AST::Bin::Div) { return "Div"; },
              [](const AST::Bin::Mod) { return "Mod"; },
              [](const AST::Bin::And) { return "And"; },
              [](const AST::Bin::Or) { return "Or"; },
              [](const AST::Bin::Eq) { return "Eq"; },
              [](const AST::Bin::Ne) { return "Ne"; },
              [](const AST::Bin::Lt) { return "Lt"; },
              [](const AST::Bin::Le) { return "Le"; },
              [](const AST::Bin::Gt) { return "Gt"; },
              [](const AST::Bin::Ge) { return "Ge"; }
            }, binary->op))
          );
          visit(*binary->rhs);
        },
        [this](const P<Unary>& unary) {
          print(std::visit(overloaded {
            [&](const AST::Un::Neg) { return "Neg"; },
            [&](const AST::Un::Not) { return "Not"; },
            [&](const AST::Un::Pos) { return "Pos"; }
          }, unary->op), unary->id);
          visit(*unary->expr);
        },
        [this](const P<Call>& call) { visit(*call); }
      }, expr.kind);
    });
  }

  void visit(const Print& printExpr) {
    print("Print", printExpr.id);
    wrap([&] {
      std::visit(overloaded {
        [&](const std::string& s) { print("String" + s); },
        [&](const AST::Ident& ident) { print("Ident"); }
      }, printExpr.kind);
    });
  }

  void visit(const Assign& assign) {
    print("Assign", assign.id);
    wrap([&] {
      visit(assign.lhs);
      visit(*assign.rhs);
    });
  }

  void visit(const If& ifExpr) {
    print("If", ifExpr.id);
    wrap([&] {
      visit(*ifExpr.cond);
      visit(*ifExpr.then_block);
      if (ifExpr.else_block.has_value()) {
        visit(*ifExpr.else_block.value());
      }
    });
  }

  void visit(const Loop& loopExpr) {
    print("Loop", loopExpr.id);
    wrap([&] {
      visit(*loopExpr.block);
    });
  }

  void visit(const Break& breakExpr) {
    print("Break", breakExpr.id);
  }

  void visit(const Ret& ret) {
    print("Ret", ret.id);
    wrap([&] {
      visit(*ret.expr);
    });
  }

  void visit(const Lit& lit) {
    std::visit(overloaded {
      [&](const std::monostate& m) {
        print(fmt::format("Lit: () ({})", lit.ty.to_string()), lit.id);
      },
      [&](const auto& v) {
        print(fmt::format("Lit: {} ({})", v, lit.ty.to_string()), lit.id);
      }
    }, lit.kind);
  }

  void visit(const Call& call) {
    print("Call", call.id);
    wrap([&] {
      print(fmt::format("Callee: {}", call.callee));
      for (const auto& arg : call.params) {
        visit(*arg);
      }
    });
  }

  void visit(const Pat& pat) {
    std::visit(overloaded {
      [&](const AST::Ident& ident) {
        visit(ident);
      }
    }, pat.kind);
  }
  void visit(const AST::Ident& ident) {
    print(fmt::format("Ident: {}", ident.identifier));
  }
};
}
