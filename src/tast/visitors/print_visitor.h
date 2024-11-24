#pragma once

#include "nodes/type.h"
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
  void wrap(std::function<void()> func)
  {
    indent += 1;
    func();
    indent -= 1;
  }
  std::string type(Ty ty) {
    return std::visit(overloaded {
      [](const Unit&) { return "Unit"; },
      [](const IntTy& intTy) {
        return std::visit(overloaded {
          [](const I8&) { return "I8"; }
        }, intTy);
      },
      [](const FloatTy& floatTy) {
        return std::visit(overloaded {
          [](const F8&) { return "F8"; }
        }, floatTy);
      },
      [](const StrTy&) { return "StrTy"; },
      [](const FnDefTy&) { return "FnDefTy"; },
      [](const InferTy& inferTy) {
        return std::visit(overloaded {
          [](const TyVar&) { return "TyVar"; },
          [](const IntVar&) { return "IntVar"; },
          [](const FloatVar&) { return "FloatVar"; }
        }, inferTy);
      }
    }, ty.kind);
  }
public:
  void visit(const Crate& crate) {
    print("Crate");
    wrap([&] {
      for (const auto& [key, body] : crate.bodies) {
        std::string key_str = "";
        for (const auto& ident : key.segments) {
          key_str += ident.identifier + "::";
        }
        print("NS: " + key_str);
        WalkVisitor::visit(*body);
      }
    });
  }
  void visit(const Body& body) {
    print("Body");
    wrap([&] {
      WalkVisitor::visit(body);
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
    print("Let");
    wrap([&] {
      WalkVisitor::visit(let);
    });
  }
  void visit(const Path& path) {
    print("Path");
    wrap([&] {
      WalkVisitor::visit(path);
    });
  }
  void visit(const PathSegment& segment) {
    print("Segment: " + segment.ident.identifier);
    wrap([&] {
      WalkVisitor::visit(segment);
    });
  }
  void visit(const Expr& expr) {
    print("Expr:" + type(expr.ty));
    wrap([&] {
      WalkVisitor::visit(expr);
    });
  }
  void visit(const Lit& lit) {
    std::visit(overloaded {
      [&](const auto& v) {
        print("Lit: " + fmt::format("{}", v));
      }
    }, lit.kind);
    wrap([&] {
      WalkVisitor::visit(lit);
    });
  }
};
}