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
    add_primitives();
    // namespace_tree.resolve_types();
    spdlog::debug("Namespace Tree: \n{}", this->namespace_tree.to_string());
  }

  void add_primitives(){
    namespace_tree.set(Namespace{{"i8"}}, PrimitiveType{Primitive::I8{}});
    namespace_tree.set(Namespace{{"i32"}}, PrimitiveType{Primitive::I32{}});
    namespace_tree.set(Namespace{{"f32"}}, PrimitiveType{Primitive::F32{}});
  }

  void visit(const Item& item) override {
    std::visit(overloaded {
      [&](const P<FnDef>& fn) {
        wrap(fn->ident.identifier, [&]() {
          namespace_tree.set(this->ns, NamespaceValue(item.id));
          Visitor::visit(*fn);
        });
      }
    }, item.kind);
  }
};
};
