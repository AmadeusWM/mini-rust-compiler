#pragma once

#include "namespace_tree.h"
#include "nodes/body.h"
#include "nodes/core.h"
#include "nodes/expr.h"
#include "nodes/stmt.h"
#include "nodes/type.h"
#include "visitors/namespace_tree_builder.h"
#include "visitors/visitor.h"
#include <algorithm>
#include <memory>
#include <variant>

namespace AST{
class LowerAstVisitor : public Visitor {
  NamespaceNode namespace_tree;
  TAST::Crate crate;

  public:
  LowerAstVisitor(NamespaceNode namespace_tree) : namespace_tree(namespace_tree) {}

  void visit(const Crate& crate) override {
    for (const auto& item : crate.items) {
      visit(*item);
    }
  }

  void visit(const Item& item) override {
    std::visit(
      overloaded {
        [&](const P<FnDef>& fn) {
          this->crate.bodies.insert({
            item.id,
            std::make_unique<TAST::Body>( TAST::Body {
              .expr = P<TAST::Expr>(new TAST::Expr {
                .id = fn->id,
                .kind = TAST::ExprKind {this->resolve_block(*fn->body)},
                .ty = {TAST::InferTy{}}
              })
            })
          });
        }
      }, item.kind);
  }

  P<TAST::Block> resolve_block(const Block& block) {
    std::vector<P<TAST::Stmt>> statements{};
    std::for_each(block.statements.begin(), block.statements.end() - 1, [&](const auto& stmt) {
      auto tast_statement = this->resolve_statement(*stmt);
      if (tast_statement.has_value()) {
        statements.push_back(std::move(tast_statement.value()));
      }
    });

    const auto& last = block.statements.back();

    Opt<P<TAST::Expr>> expr = std::nullopt;

    if (std::holds_alternative<P<Expr>>(last->kind)) {
      const auto& value = std::get<P<Expr>>(last->kind);
      expr = this->resolve_expr(*value);
    }

    return std::make_unique<TAST::Block>(TAST::Block {
      .id = block.id,
      .statements = std::move(statements),
      .expr = std::move(expr)
    });
  }

  P<TAST::Expr> resolve_expr(const Expr& expr) {
    return std::make_unique<TAST::Expr>(TAST::Expr{
      .id = expr.id,
      .kind = std::visit(overloaded {
        [this](const Lit& lit) {
          return TAST::ExprKind{resolve_lit(lit)};
        },
        [this](const P<Block>& block) {
          return TAST::ExprKind{resolve_block(*block)};
        },
        [this](const Path& path) {
          return TAST::ExprKind{AST::Path{path}};
        },
        [this](const P<Binary>& binary) {
          return TAST::ExprKind{resolve_binary(*binary)};
        },
        [this](const P<Call>& call) {
          return TAST::ExprKind{resolve_call(*call)};
        }
      }, expr.kind),
      .ty = TAST::Ty {TAST::InferTy{ TAST::TyVar{} }}
    });
  }

  Opt<P<TAST::Stmt>> resolve_statement(const Stmt& stmt) {
    Opt<TAST::StmtKind> kind = std::visit(
      overloaded {
        [this](const P<Expr>& expr) { return Opt<TAST::StmtKind> { TAST::StmtKind { resolve_expr(*expr) } }; },
        [this](const P<Let>& let) { return Opt<TAST::StmtKind> { TAST::StmtKind { resolve_let(*let) } }; },
        [this](const P<Item>& item) { visit(*item); return Opt<TAST::StmtKind>{}; },
        [this](const P<Semi>& semi) { return Opt<TAST::StmtKind>({ resolve_expr(*semi->expr) }); }
      }, stmt.kind);
    if (kind.has_value()) {
      return std::make_unique<TAST::Stmt>(TAST::Stmt {
        .id = stmt.id,
        .kind = std::move(kind.value())
      });
    }
    return std::nullopt;
  }

  P<TAST::Let> resolve_let(const Let& let) {
    return std::make_unique<TAST::Let>(TAST::Let {
      .id = let.id,
      .pat = std::make_unique<TAST::Pat>(std::visit(overloaded {
        [](const Ident& ident) { return TAST::Pat{.kind = TAST::PatKind{ident}}; }
      }, let.pat->kind)),
      .initializer = std::visit(
        overloaded {
          [this](const Decl& decl) { return Opt<P<TAST::Expr>>{}; },
          [this](const P<Expr>& expr) { return Opt<P<TAST::Expr>> { resolve_expr(*expr) }; }
        }, let.kind)
    });
  }

  TAST::Lit resolve_lit(const Lit& lit) {
    return TAST::Lit {
      .id = lit.id,
      .kind = std::visit(overloaded {
        [](const int i) { return TAST::LitKind{i}; },
        [](const std::string& s) { return TAST::LitKind{s}; }
      }, lit.kind)
    };
  }

  P<TAST::Binary> resolve_binary(const Binary& binary) {
    return std::make_unique<TAST::Binary>(TAST::Binary {
      .op = binary.op,
      .lhs = resolve_expr(*binary.lhs),
      .rhs = resolve_expr(*binary.rhs),
    });
  }

  P<TAST::Call> resolve_call(const Call& call) {
    return std::make_unique<TAST::Call>( TAST::Call {
      .id = call.id,
      .callee = call.id,
      .params = std::vector<P<TAST::Expr>>{}
    });
  }
}
