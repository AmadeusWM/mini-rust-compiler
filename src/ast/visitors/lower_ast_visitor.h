#pragma once

#include "ast_driver.h"
#include "namespace_tree.h"
#include "nodes/body.h"
#include "nodes/core.h"
#include "nodes/expr.h"
#include "nodes/item.h"
#include "nodes/stmt.h"
#include "nodes/type.h"
#include "visitors/visitor.h"
#include <algorithm>
#include <memory>
#include <spdlog/spdlog.h>
#include <variant>

namespace AST {

class LowerAstVisitor : public Visitor {
  private:
  NamespaceNode namespace_tree;
  Namespace mod_ns{.path = {}};

  void with_module(std::string segment, std::function<void()> func)
  {
    mod_ns.path.push_back(segment);
    func();
    mod_ns.path.pop_back();
  }

  ASTDriver& driver; // we need the driver to create new nodes

  public:
  P<TAST::Crate> crate = P<TAST::Crate>{new TAST::Crate{}};

  LowerAstVisitor(NamespaceNode namespace_tree, ASTDriver& driver) : namespace_tree(namespace_tree), driver(driver) {}

  void visit(const Crate& crate) override {
    for (const auto& item : crate.items) {
      visit(*item);
    }
  }

  void visit(const Item& item) override {
    std::visit(
      overloaded {
        [&](const P<FnDef>& fn) {
          this->crate->bodies.insert({
            item.id,
            std::make_unique<TAST::Body>( TAST::Body {
              .id = item.id,
              .params = resolve_params(fn->signature->inputs),
              .expr = P<TAST::Expr>(new TAST::Expr {
                .id = fn->id,
                .kind = TAST::ExprKind {this->resolve_block(*fn->body)},
                .ty = {TAST::InferTy{}}
              }),
              .ty = this->resolve_ty(*fn->signature->output),
              .ns = this->namespace_tree.find_namespace(item.id).value()
            })
          });
        }
      }, item.kind);
  }

  Vec<P<TAST::Param>> resolve_params(const Vec<P<Param>>& params) {
    Vec<P<TAST::Param>> tast_params{};
    std::transform(params.begin(), params.end(), std::back_inserter(tast_params), [&](const auto& param) {
      return std::make_unique<TAST::Param>(TAST::Param {
        .id = param->id,
        .pat = resolve_pat(*param->pat),
        .ty = this->resolve_ty(*param->ty),
        .mut = param->mut
      });
    });
    return tast_params;
  }

  P<TAST::Block> resolve_block(const Block& block) {
    std::vector<P<TAST::Stmt>> statements{};
    if (block.statements.empty()) {
      return std::make_unique<TAST::Block>(TAST::Block {
        .id = block.id,
        .statements = {},
        .expr = std::nullopt
      });
    }
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
    } else {
      auto tast_statement = this->resolve_statement(*last);
      if (tast_statement.has_value()) {
        statements.push_back(std::move(tast_statement.value()));
      }
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
        [this](const P<Assign>& assign) {
          return TAST::ExprKind{resolve_assign(*assign)};
        },
        [this](const P<Print>& printExpr) {
          return TAST::ExprKind{resolve_print(*printExpr)};
        },
        [this](const P<Ret>& ret) {
          return TAST::ExprKind{resolve_ret(*ret)};
        },
        [this](const Break& br) {
          return TAST::ExprKind{TAST::Break{br.id}};
        },
        [this](const P<If>& ifExpr) {
          return TAST::ExprKind{resolve_if(*ifExpr)};
        },
        [this](const P<Loop>& loopExpr) {
          return TAST::ExprKind{resolve_loop(*loopExpr)};
        },
        [this](const P<While>& whileExpr) {
          return TAST::ExprKind{resolve_while(*whileExpr)};
        },
        [this](const P<Block>& block) {
          return TAST::ExprKind{resolve_block(*block)};
        },
        [this](const Path& path) {
          return TAST::ExprKind{AST::Ident{path.segments[0].ident}};
        },
        [this](const P<Binary>& binary) {
          return TAST::ExprKind{resolve_binary(*binary)};
        },
        [this](const P<Unary>& unary) {
          return TAST::ExprKind{resolve_unary(*unary)};
        },
        [this](const P<Call>& call) {
          return TAST::ExprKind{resolve_call(*call)};
        }
      }, expr.kind),
      .ty = TAST::Ty {TAST::InferTy{ TAST::TyVar{} }}
    });
  }

  P<TAST::Print> resolve_print(const Print& printExpr) {
    return std::make_unique<TAST::Print>(TAST::Print {
      .id = printExpr.id,
      .kind = printExpr.kind,
    });
  }

  P<TAST::Unary> resolve_unary(const Unary& unary) {
    return std::make_unique<TAST::Unary>(TAST::Unary {
      .id = unary.id,
      .op = unary.op,
      .expr = resolve_expr(*unary.expr),
      .ty = TAST::Ty {TAST::InferTy{ TAST::TyVar{} }}
    });
  }

  P<TAST::Assign> resolve_assign(const Assign& assign) {
    return std::make_unique<TAST::Assign>(TAST::Assign {
      .id = assign.id,
      .lhs = assign.lhs,
      .rhs = resolve_expr(*assign.rhs)
    });
  }

  P<TAST::If> resolve_if(const If& ifExpr) {
    return std::make_unique<TAST::If>(TAST::If {
      .id = ifExpr.id,
      .cond = resolve_expr(*ifExpr.cond),
      .then_block = resolve_block(*ifExpr.then_block),
      .else_block = (ifExpr.else_block.has_value() ? std::optional{resolve_expr(*ifExpr.else_block.value())} : std::nullopt)
    });
  }

  P<TAST::Loop> resolve_loop(const Loop& loopExpr) {
    return std::make_unique<TAST::Loop>(TAST::Loop {
      .id = loopExpr.id,
      .block = resolve_block(*loopExpr.block)
    });
  }

  P<TAST::Loop> resolve_while(const While& whileExpr) {
    auto block = resolve_block(*whileExpr.block);
    block->statements.insert(
      block->statements.begin(),
      create_if_cond_break(resolve_expr(*whileExpr.cond))
    );
    return std::make_unique<TAST::Loop>(TAST::Loop {
      .id = whileExpr.id,
      .block = std::move(block)
    });
  }

  P<TAST::Stmt> create_if_cond_break(P<TAST::Expr> cond) {
    P<TAST::Stmt> s = create_break_stmt();
    auto statements = std::vector<P<TAST::Stmt>>{};
    statements.push_back(std::move(s));
    return std::make_unique<TAST::Stmt>(TAST::Stmt {
      .id = driver.create_node(),
      .kind = TAST::StmtKind {
        std::make_unique<TAST::Expr>(TAST::Expr {
          .id = driver.create_node(),
          .kind = TAST::ExprKind {
            std::make_unique<TAST::If>(TAST::If {
              .id = driver.create_node(),
              .cond = create_not(std::move(cond)),
              .then_block = std::make_unique<TAST::Block>(TAST::Block {
                .id = driver.create_node(),
                .statements = std::move(statements),
                .expr = std::nullopt
              }),
              .else_block = std::nullopt
            })
          },
          .ty = TAST::Ty {TAST::InferTy{ TAST::TyVar{} }}
        })
      }
    });
  }

  P<TAST::Expr> create_not(P<TAST::Expr> cond) {
    return std::make_unique<TAST::Expr>(TAST::Expr {
      .id = driver.create_node(),
      .kind = TAST::ExprKind {
        std::make_unique<TAST::Unary>(TAST::Unary {
          .id = driver.create_node(),
          .op = Un::Not{},
          .expr = std::move(cond),
          .ty = TAST::Ty {TAST::InferTy{ TAST::TyVar{} }}
        })
      },
      .ty = TAST::Ty {TAST::InferTy{ TAST::TyVar{} }}
    });
  }

  P<TAST::Stmt> create_break_stmt() {
    return std::make_unique<TAST::Stmt>(TAST::Stmt {
      .id = driver.create_node(),
      .kind = TAST::StmtKind {
        std::make_unique<TAST::Expr>(TAST::Expr {
          .id = driver.create_node(),
          .kind = TAST::ExprKind {
            TAST::Break {
              .id = driver.create_node()
            }
          },
          .ty = TAST::Ty {TAST::InferTy{ TAST::TyVar{} }}
        })
      }
    });
  }

  P<TAST::Ret> resolve_ret(const Ret& ret) {
    return std::make_unique<TAST::Ret>(TAST::Ret {
      .id = ret.id,
      .expr = resolve_expr(*ret.expr)
    });
  }

  Opt<P<TAST::Stmt>> resolve_statement(const Stmt& stmt) {
    Opt<TAST::StmtKind> kind = std::visit(overloaded {
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
      .pat = resolve_pat(*let.pat),
      .ty = resolve_ty(*let.ty),
      .initializer = std::visit(
        overloaded {
          [this](const Decl& decl) { return Opt<P<TAST::Expr>>{}; },
          [this](const P<Expr>& expr) { return Opt<P<TAST::Expr>> { resolve_expr(*expr) }; }
        }, let.kind),
      .mut = let.mut
    });
  }

  P<TAST::Pat> resolve_pat(const AST::Pat pat) {
    return std::make_unique<TAST::Pat>(std::visit(overloaded {
      [](const Ident& ident) { return TAST::Pat{.kind = TAST::PatKind{ident}}; }
    }, pat.kind));
  }

  TAST::Ty resolve_ty(const Ty& ty) {
    return std::visit(overloaded {
      [&](const Path& path) {
        auto value = namespace_tree.get(Namespace{path.to_vec()});
        if (value.has_value() && std::holds_alternative<PrimitiveType>(value.value())) {
          auto primitive = std::get<PrimitiveType>(value.value());
          return std::visit(overloaded {
            [&](const Primitive::I8& i8){ return TAST::Ty{ TAST::IntTy{TAST::I8{}}}; },
            [&](const Primitive::I32& i32){ return TAST::Ty{ TAST::IntTy{TAST::I32{}}}; },
            [&](const Primitive::F32& f32){ return TAST::Ty{ TAST::FloatTy{TAST::F32{}}}; },
            [&](const Primitive::Str& str){ return TAST::Ty{ TAST::StrTy{}}; },
            [&](const Primitive::Bool& b) { return TAST::Ty{ TAST::BoolTy{}}; },
          }, primitive.kind);
        }
        else {
          throw std::runtime_error("Could not resolve path to primitive:" + path.to_string());
        }
      },
      [&](const Infer& infer) { return TAST::Ty{TAST::InferTy{}}; },
      [&](const Unit& unit) { return TAST::Ty{TAST::Unit{}}; }
    }, ty.kind);
  }

  TAST::Lit resolve_lit(const Lit& lit) {
    return TAST::Lit {
      .id = lit.id,
      .ty = TAST::Ty{TAST::InferTy{}}, // initialize with infer type, will be inferred during typechecking
      .kind = lit.kind
    };
  }

  P<TAST::Binary> resolve_binary(const Binary& binary) {
    return std::make_unique<TAST::Binary>(TAST::Binary {
      .id = binary.id,
      .op = binary.op,
      .lhs = resolve_expr(*binary.lhs),
      .rhs = resolve_expr(*binary.rhs),
      .ty = TAST::Ty{TAST::InferTy{}}
    });
  }

  P<TAST::Call> resolve_call(const Call& call) {
    Namespace call_ns = Namespace{call.path.to_vec()};
    auto callee = namespace_tree.get(mod_ns, call_ns);
    return std::make_unique<TAST::Call>( TAST::Call {
      .id = call.id,
      .callee = std::get<NodeId>(callee.value()),
      .params = [&] {
        Vec<P<TAST::Expr>> transformed_params;
        std::transform(call.params.begin(), call.params.end(), std::back_inserter(transformed_params), [&](const auto& param) {
          return resolve_expr(*param);
        });
        return transformed_params;
      }()
    });
  }
};
}
