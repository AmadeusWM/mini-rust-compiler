#pragma once

#include "../node.h"
#include "visitors/visitor.h"
#include <map>

namespace AST {

namespace Scope {
  struct Normal {};
  struct Fn {};
  struct Module {};

  typedef std::variant<
    Normal,
    Fn,
    Module
  >
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
  std::vector<Scope> scopes;

  public:
  void visit(const Crate& crate) override
  {
    for (const auto& item : crate.items) {
      Visitor::visit(item);
    }
  }

  void visit(const FnDef& crate) override
  {
  }
};
}
