#pragma once

#include "../node.h"
#include "visitors/visitor.h"
#include <map>

namespace AST {

namespace Scope {
  struct Normal { };
  struct Fn { };
  struct Module { };

  typedef std::variant<
      Normal,
      Fn,
      Module>
      ScopeKind;

  struct Scope {

    ScopeKind kind;
    std::map<std::string, NodeId> bindings;
  };
}

/*
 * docs: https://rustc-dev-guide.rust-lang.org/name-resolution.html
 * rust source: https://doc.rust-lang.org/nightly/nightly-rustc/rustc_resolve/late/struct.LateResolutionVisitor.html
 */
class NameResolutionVisitor : public Visitor {
  private:
  std::vector<Scope::Scope> scopes;

  void start_scope(Scope::Scope scope, std::function<void()> body)
  {
    scopes.push_back(scope);
    body();
    scopes.pop_back();
  }

  public:
  void visit(const Crate& crate) override
  {
    for (const auto& item : crate.items) {
      Visitor::visit(item);
    }
  }

  void visit(const FnDef& fn) override
  {
    start_scope(Scope::Scope { Scope::Fn {} },
        [this, &fn]() {
          visit(*fn.body);
        });
  }

  void visit(const Block& block) override
  {
    start_scope(Scope::Scope { Scope::Normal {} }, [this, &block]() {
      for (const auto& stmt : block.statements) {
        visit(stmt);
      }
    });
  }

  void visit(const Expr& expr) override
  {
    std::visit(overloaded {
                   [this, &expr](const Lit& lit) {
                     visit(expr);
                   },
                   [this, &expr](const P<Block>& block) {
                     visit(*block);
                   },
               },
        expr.kind);
  }

  void visit(const Stmt& stmt) override
  {
    start_scope(Scope::Scope { Scope::Fn {} },
      [this, &stmt]() {
        std::visit(overloaded {
          [this, &stmt](const P<Expr>& expr) {
            visit(*expr);
          },
          [this, &stmt](const P<Let>& let) {
            visit(*let);
          },
        }, stmt.kind);
      }
    );
  }

  void visit(const Let& let)
  {
    std::visit(overloaded {
      [this](const Decl& decl) { },
      [this](const P<Expr>& expr) {
        visit(*expr);
      }
    }, let.kind);
  }
};
}
