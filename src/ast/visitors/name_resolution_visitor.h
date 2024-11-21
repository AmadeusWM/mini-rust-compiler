#pragma once

#include "../node.h"
#include "visitors/visitor.h"
#include <exception>
#include <fmt/core.h>
#include <fmt/format.h>
#include <map>
#include <numeric>
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
  struct Fn { };
  struct Module { };

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
}

/*
 * docs: https://rustc-dev-guide.rust-lang.org/name-resolution.html
 * rust source: https://doc.rust-lang.org/nightly/nightly-rustc/rustc_resolve/late/struct.LateResolutionVisitor.html
 */
class NameResolutionVisitor : public Visitor {
  private:
  std::vector<Scope::Scope> scopes{};

  void with_scope(Scope::ScopeKind scope_kind, NodeId id, std::function<void()> body)
  {
    spdlog::debug("entering scope: {}", id);
    Scope::Scope scope = {
      .id = id,
      .kind = scope_kind
    };
    scopes.push_back(scope);
    body();
    Scope::Scope last = scopes.back();
    while (last.id != scope.id) {
      scopes.pop_back();
      last = scopes.back();
    }
    spdlog::debug("leaving scope: {}", id);
    scopes.pop_back();
  }

  /**
  * add all items to the current scope
  */
  void resolve_item(const Item& item)  {
    std::visit(overloaded {
      [this](const P<FnDef>& fn) {
        auto res = lookup_ident(fn->ident.identifier);
        if (res.has_value()) {
          throw NameResolutionException("fn not found");
        }
        insert_binding(fn->ident.identifier,
          Res::Res(Res::Def {
            .kind = Res::Fn {}
          })
        );
      }
    }, item.kind);
  }

  Opt<Res::Res> lookup_ident(std::string iden) {
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

  Res::Res lookup_ident_or_throw(std::string iden) {
    auto res = lookup_ident(iden);
    if (res.has_value()) {
      return res.value();
    }
    throw NameResolutionException(fmt::format("identifier \"{}\" not found", iden));
  }

  void insert_binding(std::string name, Res::Res res)
  {
    spdlog::debug("inserting identifier \"{}\"", name);
    if (scopes.size() == 0) {
      throw NameResolutionException(fmt::format("no scope to insert identifier \"{}\"", name));
    }
    scopes.back().bindings.insert({ name, res });
  }

  public:
  void visit(const Crate& crate) override
  {
    with_scope(Scope::Module{}, crate.id,
      [this, &crate]() {
        for (const auto& item : crate.items) {
          resolve_item(item);
        }
        for (const auto& item : crate.items) {
          Visitor::visit(item);
        }
      });
  }

  void visit(const FnDef& fn) override
  {
    with_scope(Scope::Fn {}, fn.id,
      [this, &fn]() {
        visit(*fn.body);
      }
    );
  }

  void visit(const Block& block) override
  {
    for (const auto& stmt : block.statements) {
      if (std::holds_alternative<P<Item>>(stmt.kind)) {
        const auto& item = std::get<P<Item>>(stmt.kind);
        resolve_item(*item);
      }
    }

    with_scope(Scope::Normal {}, block.id, [this, &block]() {
      for (const auto& stmt : block.statements) {
        visit(stmt);
      }
    });
  }

  void visit(const Expr& expr) override
  {
    std::visit(overloaded {
        [this, &expr](const Lit& lit) {
        },
        [this, &expr](const P<Block>& block) {
          visit(*block);
        },
        [this, &expr](const Ident& ident) {
          auto res = lookup_ident_or_throw(ident.identifier);
        }
    }, expr.kind);
  }

  void visit(const Stmt& stmt) override
  {
    with_scope(Scope::Fn {},
      stmt.id,
      [this, &stmt]() {
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
        }, stmt.kind);
      }
    );
  }

  void visit(const Let& let) override
  {
    scopes.push_back({ .id = let.id, .kind = Scope::Normal {} });
    std::visit(overloaded {
      [this](const Ident ident) {
        insert_binding(ident.identifier, Res::Res(Res::Local { .id = ident.id }));
      }
    }, let.pat);
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
