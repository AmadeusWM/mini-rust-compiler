#pragma once

#include "nodes/body.h"
#include "nodes/core.h"
#include "nodes/expr.h"
#include "nodes/item.h"
#include "nodes/stmt.h"
#include "util.h"
#include "visitors/visitor.h"
#include <memory>
#include <variant>
#include <vector>

/**
* TODO:
* 1. first lower the AST to 2 maps: expressions and statements
* 2. then lower the AST to bodies, every body consists of
* see:  https://doc.rust-lang.org/beta/nightly-rustc/rustc_ast_lowering/fn.lower_to_hir.html,
*       https://doc.rust-lang.org/nightly/nightly-rustc/src/rustc_ast_lowering/item.rs.html#26-31
*/
namespace AST {
class LowerAstVisitor : public Visitor {
private:
  TAST::Crate crate{
    .bodies = {}
  };
  TAST::NS current_ns{};

  void ns(Ident ident, std::function<void()> func)
  {
    current_ns.segments.push_back(ident);
    func();
    current_ns.segments.pop_back();
  }

  /**
  * will insert a body for the current namespace
  */
  void insert_body(TAST::Body body)
  {
    crate.bodies.insert({current_ns, std::make_unique<TAST::Body>(std::move(body))});
  }
public:
  P<TAST::Crate> lower_crate(const Crate& crate) {
    this->visit(crate);
    return P<TAST::Crate>(new TAST::Crate(std::move(this->crate)));
  }

  void visit(const Crate& crate) {
    for (const auto& item : crate.items) {
      visit(*item);
    }
  }

  void visit(const Item& item) {
    std::visit(overloaded {
      [this](const P<FnDef>& fn) {
      },
    }, item.kind);
  }

  void visit(const FnDef& fn) {
    ns(fn.ident, [this, &fn](){
      insert_body(
        {
          .params = {},
          .expr = P<TAST::Expr>(new TAST::Expr{
            .id = fn.id,
            .kind = lower_body(*fn.body)
            }
          )
        }
      );
    });
  }

  P<TAST::Block> lower_body(const Block& block) {
    P<TAST::Block> lowered_block = P<TAST::Block>(new TAST::Block{
      .id = block.id,
      .statements = {},
      .expr = std::nullopt
    });

    if (block.statements.empty()) {
      return lowered_block;
    }

    int length = block.statements.size();
    const P<AST::Stmt>& last = block.statements.back();

    if (std::holds_alternative<P<Expr>>(last->kind)) {
      const auto& expr = std::get<P<Expr>>(last->kind);
      lowered_block->expr = Opt<P<TAST::Expr>>(lower_expr(*expr));
      length--;
    }

    for (int i = 0; i < length; i++){
      const auto& stmt = block.statements[i];
      std::visit(overloaded {
        [this, &lowered_block](const P<Item>& item) {
          visit(*item);
        },
        [this, &lowered_block, &stmt](const P<Expr>& expr) {
          lowered_block->statements.push_back(P<TAST::Stmt>(new TAST::Stmt{
            .id = stmt->id,
            .kind = lower_expr(*expr)
          }));
        },
        [this, &lowered_block, &stmt](const P<Let>& let) {
          lowered_block->statements.push_back(P<TAST::Stmt>(new TAST::Stmt{
            .id = stmt->id,
            .kind = lower_let(*let)
          }));
        }
      }, stmt->kind);
    }
    return lowered_block;
  }

  P<TAST::Let> lower_let(const Let& let) {
    return P<TAST::Let>(new TAST::Let {
      .id = let.id,
      .pat = lower_pat(let.pat),
      .kind = std::visit(overloaded {
        [this, &let](const Decl& decl) {
          return TAST::LocalKind{TAST::Decl{}};
        },
        [this, &let](const P<Expr>& expr){
          return TAST::LocalKind{lower_expr(*expr)};
        }
      }, let.kind)
    });
  }

  P<TAST::Expr> lower_expr(const Expr& expr) {
    return std::visit(overloaded {
      [this, &expr](const Lit& lit) {
        return P<TAST::Expr>(new TAST::Expr {
          .id = expr.id,
          .kind = lower_lit(lit)
        });
      },
      [this, &expr](const Path& path) {
        return P<TAST::Expr>(new TAST::Expr {
          .id = expr.id,
          .kind = lower_path(path)
        });
      },
      [this, &expr](const P<Block>& block){
        return P<TAST::Expr>(new TAST::Expr {
          .id = expr.id,
          .kind = lower_body(*block)
        });
      }
    }, expr.kind);
  }

  TAST::Lit lower_lit(const Lit& lit) {
    auto kind = std::visit(overloaded {
      [](const int& i) {
        return TAST::LitKind(i);
      },
      [](const std::string& s) {
        return TAST::LitKind(s);
      },
    }, lit.kind);
    return TAST::Lit{.kind = kind};
  }

  TAST::Pat lower_pat(const AST::Pat& pat) {
    return TAST::Pat(std::visit(overloaded {
      [this](const Ident& ident) {
        return TAST::Ident(lower_ident(ident));
      }
    }, pat));
  }

  TAST::Path lower_path(const AST::Path& path){
    TAST::Path tast_path{
      .segments = {}
    };
    for (const auto& segment : path.segments) {
      tast_path.segments.push_back(TAST::PathSegment {
        .id = segment.id,
        .ident = lower_ident(segment.ident),
      });
    }
    return tast_path;
  }

  TAST::Ident lower_ident(const Ident& ident) {
    return TAST::Ident{.identifier = ident.identifier};
  }
};
}
