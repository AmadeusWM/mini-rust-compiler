#pragma once

#include "util.h"
#include "visitors/tast_visitor.h"
#include <variant>
namespace TAST {
class PrintVisitor : public WalkVisitor {
private:
  int indent = 0;

  void print(std::string str)
  {
    std::string ind = "";
    for (int i = 0; i < indent; i++) {
      ind += "  ";
    }
    spdlog::debug("{}|-{}", ind, str);
  }

  void print(std::string str, Ty ty) {
    print(str + " -> " + ty.to_string());
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
        std::string key_str = body->ns.to_string();
        print("NS: " + key_str);
        print("ID: " + std::to_string(key));
        visit(*body);
      }
    });
  }
  void visit(const Body& body) {
    print("Body");
    wrap([&] {
      for (const auto& param : body.params) {
        visit(*param);
      }
      visit(*body.expr);
    });
  }

  void visit(const Param& param) {
    print(fmt::format("Param: {}", param.ty.to_string()));
    wrap([&] {
      visit(*param.pat);
    });
  }

  void visit(const Block& block) {
    print("Block");
    wrap([&] {
      WalkVisitor::visit(block);
    });
  }
  void visit(const Stmt& stmt) {
    print("Stmt");
    wrap([&] {
      WalkVisitor::visit(stmt);
    });
  }
  void visit(const Let& let) {
    print(fmt::format("Let: {}", let.ty.to_string()));
    wrap([&] {
      visit(*let.pat);
      WalkVisitor::visit(let);
    });
  }
  void visit(const Expr& expr) {
    print("Expr", expr.ty);
    wrap([&] {
      std::visit(overloaded {
        [this](const P<Block>& block) { visit(*block); },
        [this](const P<Ret>& ret) { visit(*ret); },
        [this](const Lit& lit) { visit(lit); },
        [this](const Break& breakExpr) { visit(breakExpr); },
        [this](const AST::Ident& ident) { print(fmt::format("Ident: {}", ident.identifier)); },
        [this](const P<Binary>& binary) {
          visit(*binary->lhs);
          print(fmt::format("BinOp: {}",
            std::visit(overloaded {
              [](const AST::Bin::Add) { return "Add"; },
              [](const AST::Bin::Sub) { return "Sub"; }
            }, binary->op))
          );
          visit(*binary->rhs);
        },
        [this](const P<Call>& call) { visit(*call); }
      }, expr.kind);
    });
  }

  void visit(const If& ifExpr) {
    print("If");
    wrap([&] {
      visit(*ifExpr.cond);
      visit(*ifExpr.then_block);
      if (ifExpr.else_block.has_value()) {
        visit(*ifExpr.else_block.value());
      }
    });
  }

  void visit(const Loop& loopExpr) {
    print("Loop");
    wrap([&] {
      visit(*loopExpr.block);
    });
  }

  void visit(const Break& breakExpr) {
    print("Break");
  }

  void visit(const Ret& ret) {
    print("Ret");
    wrap([&] {
      visit(*ret.expr);
    });
  }

  void visit(const Lit& lit) {
    std::visit(overloaded {
      [&](const auto& v) {
        print(fmt::format("Lit: {} ({})", v, lit.ty.to_string()));
      }
    }, lit.kind);
  }

  void visit(const Call& call) {
    print("Call");
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
        print(fmt::format("Ident: {}", ident.identifier));
      }
    }, pat.kind);
  }
};
}
