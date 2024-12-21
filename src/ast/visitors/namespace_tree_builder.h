#pragma once

#include "namespace_tree.h"
#include "nodes/item.h"
#include "visitors/visitor.h"
#include <spdlog/spdlog.h>

namespace AST {
class NamespaceTreeBuilder : public AST::Visitor {
  public:
  NamespaceNode namespace_tree;
  private:
  Namespace ns{.path = {}};

  void wrap(std::string segment, std::function<void()> func)
  {
    ns.path.push_back(segment);
    func();
    ns.path.pop_back();
  }

  public:
  NamespaceTreeBuilder() {
  }

  void visit(const Crate& crate) override
  {
    Visitor::visit(crate);
    spdlog::debug("Namespace Tree: \n{}", this->namespace_tree.to_string());
  }

  void visit(const FnDef& fn) override {
    spdlog::debug("visiting fn: {}", fn.ident.identifier);
    wrap(fn.ident.identifier, [&]() {
      namespace_tree.set(this->ns, NamespaceValue(fn.id));
      Visitor::visit(fn);
    });
  }
};
};
