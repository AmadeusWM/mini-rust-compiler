#pragma once

#include <iostream>
#include <string>
#include <variant>
#include <vector>

struct ProgramNode;
struct FunctionDefinitionNode;

typedef std::variant<
  ProgramNode,
  FunctionDefinitionNode
> Node;

struct ProgramNode {
  std::vector<Node> children;
};

struct FunctionDefinitionNode {
  std::string name;
};

static void test_nodes() {
  FunctionDefinitionNode function{"abc"};
  ProgramNode program{
    std::vector{Node(function)}
  };

  Node node = program;
}

class NodeVisitor {
public:
  virtual void visit(const ProgramNode& node) = 0;
  virtual void visit(const FunctionDefinitionNode& node) = 0;
  void visit (const Node& node) {
    if (std::holds_alternative<ProgramNode>(node)) {
      visit(std::get<ProgramNode>(node));
    }
    else if (std::holds_alternative<FunctionDefinitionNode>(node)) {
      visit(std::get<FunctionDefinitionNode>(node));
    }
  }
};

class DefaultVisitor : public NodeVisitor {
  void visit(const ProgramNode& node) override {}
  void visit(const FunctionDefinitionNode& node) override {}
};

class PrintVisitor : public NodeVisitor {
public:
  void visit(const ProgramNode& node) override {
    for (const Node& child : node.children) {
      NodeVisitor::visit(child);
    }
  }

  void visit(const FunctionDefinitionNode& node) override {
    std::cout << "FunctionDefinitionNode: " << node.name << std::endl;
  }
};
