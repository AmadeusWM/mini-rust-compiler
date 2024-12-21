#pragma once

#include "namespace_tree.h"
#include "nodes/body.h"
#include "nodes/core.h"
#include "nodes/expr.h"
#include "nodes/item.h"
#include "nodes/stmt.h"
#include "nodes/type.h"
#include "util.h"
#include "visitors/visitor.h"
#include <memory>
#include <spdlog/spdlog.h>
#include <variant>
#include <vector>

/**
* TODO:
* - Prefix Call paths with the current Namespace (so we can immediately query the correct body)
*/
// I AM TRYING TO DO TO MUCH => SPLIT UP INTO: resolve_bodies, resolve_types, lower_ast(resolved_bodies, resolved_types)
namespace AST {
class LowerAstVisitor : public Visitor {
private:
  TAST::Crate crate{
    .bodies = {}
  };
  Namespace current_ns = {
    .path = {}
  };

  void ns(Ident ident, std::function<void()> func)
  {
    current_ns.path.push_back(ident.identifier);
    func();
    current_ns.path.pop_back();
  }

  /**
  * will insert a body for the current namespace
  */
  void insert_body(TAST::Body body)
  {
    // crate.bodies.insert({current_ns, std::make_unique<TAST::Body>(std::move(body))});
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
        visit(*fn);
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
            .kind = lower_block(*fn.body)
            }
          )
        }
      );
    });
  }

  Vec<P<TAST::Param>> lower_params(const Vec<Param>& params) {
    Vec<P<TAST::Param>> lowered_params;
    for (const auto& param : params) {
      lowered_params.push_back(P<TAST::Param>(new TAST::Param{
        .id = param.id,
        .pat = lower_pat(*param.pat),
        .ty = lower_ty(*param.ty)
      }));
    }
    return lowered_params;
  }

  P<TAST::Ty> lower_ty(const Ty& ty) {
    // std::visit(overloaded {
    //   [&](const Infer& infer) { return TAST::InferTy(TAST::TyVar{}); },
    //   [&](const Path& path) {

    //   }
    // }, ty.kind);
  }

  P<TAST::Block> lower_block(const Block& block) {
    P<TAST::Block> lowered_block = P<TAST::Block>(new TAST::Block{
      .id = block.id,
      .statements = {},
      .expr = std::nullopt
    });

    // if the block is empty, we can return early
    if (block.statements.empty()) {
      return lowered_block;
    }

    int length = block.statements.size();
    const P<AST::Stmt>& last = block.statements.back();

    // when the last statement is an expression, we can move it to the expr field
    if (std::holds_alternative<P<Expr>>(last->kind)) {
      spdlog::warn("last statement is an expression");
      const auto& expr = std::get<P<Expr>>(last->kind);
      lowered_block->expr = Opt<P<TAST::Expr>>(lower_expr(*expr));
      length--;
    }

    // iterate over all statements and lower them
    // * items are handled by the visitor
    // * other statements are added to the lowered block
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
        },
        [this, &lowered_block, &stmt](const P<Semi>& semi) {
          lowered_block->statements.push_back(P<TAST::Stmt>(new TAST::Stmt{
            .id = stmt->id,
            .kind = P<TAST::Semi>(new TAST::Semi { lower_expr(*semi->expr) })
          }));
        },
      }, stmt->kind);
    }
    return lowered_block;
  }

  P<TAST::Let> lower_let(const Let& let) {
    return P<TAST::Let>(new TAST::Let {
      .id = let.id,
      .pat = lower_pat(*let.pat),
      .initializer = std::visit(overloaded {
        [this, &let](const Decl& decl) {
          return Opt<P<TAST::Expr>>();
        },
        [this, &let](const P<Expr>& expr){
          return Opt<P<TAST::Expr>>(lower_expr(*expr));
        }
      }, let.kind)
    });
  }

  P<TAST::Expr> lower_expr(const Expr& expr) {
    return std::visit(overloaded {
      [this, &expr](const Lit& lit) {
        auto tast_lit = lower_lit(lit);
        return P<TAST::Expr>(new TAST::Expr {
          .id = expr.id,
          .kind = tast_lit,
          .ty = lit_type(tast_lit)
        });
      },
      [this, &expr](const Path& path) {
        return P<TAST::Expr>(new TAST::Expr {
          .id = expr.id,
          .kind = lower_path(path),
          .ty = {TAST::InferTy{}}
        });
      },
      [this, &expr](const P<Binary>& binary) {
        return P<TAST::Expr>(new TAST::Expr {
          .id = expr.id,
          .kind = P<TAST::Binary>(new TAST::Binary {
            .op = binary->op,
            .lhs = lower_expr(*binary->lhs),
            .rhs = lower_expr(*binary->rhs)
          }),
          .ty = {TAST::InferTy{}}
        });
      },
      [this, &expr](const P<Block>& block){
        auto lowered_block = lower_block(*block);
        TAST::Ty ty = lowered_block->expr.has_value()
          ? lowered_block->expr->get()->ty
          : TAST::Ty{.kind = TAST::Unit{}};
        return P<TAST::Expr>(new TAST::Expr {
          .id = expr.id,
          .kind = std::move(lowered_block),
          .ty = ty
        });
      },
      [&](const P<Call>& call) {

      }
    }, expr.kind);
  }

  TAST::Ty lit_type(const TAST::Lit& lit) {
    return TAST::Ty{
      .kind = {std::visit(overloaded {
        [this](const int& i) {
          return TAST::TyKind(TAST::InferTy(TAST::IntVar{}));
        },
        [this](const std::string& s) {
          return TAST::TyKind(TAST::StrTy{});
        },
      }, lit.kind)}
    };
  }

  TAST::Lit lower_lit(const Lit& lit) {
    return {
      .id = lit.id,
      .kind = std::visit(overloaded {
        [](const int& i) {
          return TAST::LitKind(i);
        },
        [](const std::string& s) {
          return TAST::LitKind(s);
        },
      }, lit.kind)
    };
  }

  P<TAST::Pat> lower_pat(const AST::Pat& pat) {
    return P<TAST::Pat>(new TAST::Pat{
      .kind = std::visit(overloaded {
        [this](const Ident& ident) {
          return TAST::Ident(lower_ident(ident));
        }
      }, pat.kind)
    });
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
