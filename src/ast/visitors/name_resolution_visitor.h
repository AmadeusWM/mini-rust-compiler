#pragma once

#include "../ast_node.h"
#include "namespace_tree.h"
#include "nodes/core.h"
#include "util.h"
#include "visitors/visitor.h"
#include <fmt/core.h>
#include <fmt/format.h>
#include <map>
#include <optional>
#include <spdlog/common.h>
#include <spdlog/spdlog.h>
#include <stdexcept>
#include <variant>
#include <vector>

namespace AST {
class NameResolutionException : public std::runtime_error {
public:
    NameResolutionException(const std::string& message)
        : std::runtime_error("(Name Resolution Error) " + message) {}
};


/**
* resolutions
*/
namespace Res {
  struct Fn {
  };

  typedef std::variant<
    Fn
    // Mod
    // Enum
    // Struct
  > DefKind;

  struct Def {
    NodeId id;
    DefKind kind;
  };

  /**
   * Function parameters, or local variables
   */
  struct Local {
    NodeId id;
  };

  typedef std::variant<
    Def,
    Local
  > Res;
}

namespace Scope {

  struct Normal { };
  struct Fn {
    std::string segment;
  };
  struct Module {
    std::string segment;
  };

  typedef std::variant<
      Normal,
      Fn,
      Module>
      ScopeKind;

  typedef uint64_t ScopeId;
  struct Scope {
    ScopeId id;
    ScopeKind kind;
    std::map<std::string, Res::Res> bindings;
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

    Namespace get_scope_namespace(ScopeKind kind) {
      int i = scopes.size() - 1;
      for (; i >= 0; i--) {
        if (scopes[i].kind.index() == kind.index()) {
          break;
        }
      }
      std::vector<std::string> path;
      for (int j = 0; j < i; j++) {
        std::visit(overloaded {
          [&](const Module& mod) {
            path.push_back(mod.segment);
          },
          [&](const Fn& fn) {
            path.push_back(fn.segment);
          },
          [&](const auto&) {
            // Do nothing for other scope kinds
          }
        }, scopes[j].kind);
      }
      return Namespace{ .path = path };
    }

    Namespace get_namespace(){
      std::vector<std::string> path;
      for (const auto& scope : scopes){
        std::visit(overloaded {
          [&](const Module& mod) {
            path.push_back(mod.segment);
          },
          [&](const Fn& fn) {
            path.push_back(fn.segment);
          },
          [&](const auto&) {
            // Do nothing for other scope kinds
          }
        }, scope.kind);
      }
      return Namespace{ .path = path };
    }

    Opt<Res::Res> lookup(std::string iden) {
      spdlog::debug("looking up identifier \"{}\"", iden);
      for (auto it = scopes.rbegin(); it != scopes.rend(); ++it) {
        auto scope = *it;
        auto binding = scope.bindings.find(iden);
        if (binding != scope.bindings.end()) {
          return Opt<Res::Res>(binding->second);
        }
      }
      return Opt<Res::Res>{};
    }

    void insert_binding(std::string name, Res::Res res) {
      if (scopes.size() == 0) {
        throw NameResolutionException(fmt::format("no scope to insert identifier \"{}\"", name));
      }
      scopes.back().bindings.insert({ name, res });
    }
  };
}

/*
 * docs: https://rustc-dev-guide.rust-lang.org/name-resolution.html
 * rust source: https://doc.rust-lang.org/nightly/nightly-rustc/rustc_resolve/late/struct.LateResolutionVisitor.html
 */
class NameResolutionVisitor : public Visitor {
  public:
  NamespaceNode namespace_tree;
  private:
  Scope::Scopes scopes{};

  void with_scope(Scope::ScopeKind scope_kind, NodeId id, std::function<void()> body)
  {
    spdlog::debug("entering scope: {}", id);
    Scope::Scope scope = {
      .id = id,
      .kind = scope_kind
    };
    scopes.push(scope);
    body();
    spdlog::debug("exiting scope: {}", id);
    scopes.pop(scope);
  }

  Opt<Res::Res> lookup_ident(std::string iden) {
    return scopes.lookup(iden);
  }

  Res::Res lookup_ident_or_throw(std::string iden) {
    auto res = lookup_ident(iden);
    if (res.has_value()) {
      return res.value();
    }
    throw NameResolutionException(fmt::format("identifier \"{}\" not found", iden));
  }

  NamespaceValue lookup_namespace(Namespace ns) {
    const Namespace scope_barrier = scopes.get_scope_namespace(Scope::Module{});
    const Namespace root_path = scopes.get_namespace();
    auto value = namespace_tree.get(root_path, ns, scope_barrier);
    if (value.has_value()) {
      std::string result = "";
      if (std::holds_alternative<Namespace>(value.value())) {
        result += std::string("Namespace");
      }
      else if (std::holds_alternative<PrimitiveType>(value.value())) {
        result += std::string("PrimitiveType");
      }
      else {
        result += std::string("NodeId: ") + std::to_string(std::get<NodeId>(value.value()));
      }
      spdlog::debug("found: {}", result);
      return value.value();
    }
    else {
      throw NameResolutionException(fmt::format("node not found: {}", ns.to_string()));
    }
  }

  void insert_binding(std::string name, Res::Res res)
  {
    scopes.insert_binding(name, res);
  }

  public:
  NameResolutionVisitor(NamespaceNode root)
    : namespace_tree(root) {
  }

  void visit(const Crate& crate) override
  {
    for (const auto& item : crate.items) {
      Visitor::visit(*item);
    }
  }

  void visit(const FnDef& fn) override
  {
    with_scope(Scope::Fn { .segment = fn.ident.identifier }, fn.id,
      [&]() {
        visit(*fn.signature);
        visit(*fn.body);
      }
    );
  }

  void visit(const FnSig& sig) override
  {
    for (const auto& param : sig.inputs) {
      std::visit(overloaded{
        [&](const Ident& ident) {
          insert_binding(ident.identifier, Res::Local { .id = param->id });
        }
      }, param->pat->kind);
    }
  }

  void visit(const Block& block) override
  {
    with_scope(Scope::Normal {}, block.id, [this, &block]() {
      for (const auto& stmt : block.statements) {
        visit(*stmt);
      }
    });
  }

  void visit(const Expr& expr) override
  {
    std::visit(overloaded {
        [&](const Lit& lit) {
        },
        [&](const Break& br) {
        },
        [&](const P<Ret>& ret) {
          visit(*ret);
        },
        [&](const P<Assign>& assign) {
          visit(*assign);
        },
        [&](const P<If>& ifExpr) {
          Visitor::visit(*ifExpr);
        },
        [&](const P<While>& whileExpr) {
          Visitor::visit(*whileExpr);
        },
        [&](const P<Loop>& loop) {
          Visitor::visit(*loop);
        },
        [&](const P<Block>& block) {
          visit(*block);
        },
        [&](const Path& path) {
          if (path.segments.size() > 1) {
            throw NameResolutionException(fmt::format("Cannot look up a local identifier consisting of multiple segments: {}", path.to_string()));
          }
          auto res = lookup_ident_or_throw(path.segments.back().ident.identifier);
        },
        [&](const P<Binary>& binary) {
          visit(*binary->lhs);
          visit(*binary->rhs);
        },
        [&](const P<Unary>& unary) {
          visit(*unary->expr);
        },
        [&](const P<Call>& call) {
          visit(*call);
        }
    }, expr.kind);
  }

  void visit(const Assign& assign) override
  {
    auto res = lookup_ident_or_throw(assign.lhs.identifier);
    visit(*assign.rhs);
  }

  void visit(const Call& call) override {
    lookup_namespace(Namespace {call.path.to_vec()});
  }

  void visit(const Stmt& stmt) override
  {
    std::visit(overloaded {
      [this, &stmt](const P<Expr>& expr) {
        visit(*expr);
      },
      [this, &stmt](const P<Let>& let) {
        visit(*let);
      },
      [this, &stmt](const P<Item>& item) {
        Visitor::visit(*item);
      },
      [this, &stmt](const P<Semi>& semi) {
        Visitor::visit(*semi->expr);
      },
    }, stmt.kind);
  }

  void visit(const Ret& ret) override
  {
    visit(*ret.expr);
  }

  void visit(const Let& let) override
  {
    scopes.push({ .id = let.id, .kind = Scope::Normal {} });
    if (std::holds_alternative<Path>(let.ty->kind)) {
        lookup_namespace(Namespace {std::get<Path>(let.ty->kind).to_vec()});
    }
    std::visit(overloaded {
      [this, &let](const Ident& ident) {
        insert_binding(ident.identifier, Res::Res(Res::Local { .id = let.id }));
      }
    }, let.pat->kind);
    std::visit(overloaded {
      [this](const Decl& decl) {
      },
      [this](const P<Expr>& expr) {
        visit(*expr);
      }
    }, let.kind);
  }
};
}
