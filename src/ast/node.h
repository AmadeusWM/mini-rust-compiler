#pragma once

#include <iostream>
#include <memory>
#include <string>
#include <variant>
#include <vector>

struct ProgramNode;
struct FunctionDefinitionNode;
struct BlockNode;
struct StatementNode;
struct AssignmentNode;

template <typename T> using P = std::unique_ptr<T>;

typedef std::variant<
  ProgramNode,
  FunctionDefinitionNode,
  BlockNode,
  StatementNode,
  AssignmentNode
> Node;

struct ProgramNode {
  std::vector<FunctionDefinitionNode> children;
};

struct FunctionDefinitionNode {
  std::string identifier;
  P<BlockNode> block;
};

struct BlockNode {
  std::vector<StatementNode> children;
};

struct StatementNode {
  P<Node> node;
};

struct AssignmentNode {
  std::string identifier;
  int value;
};


class Visitor {
public:
  virtual void visit(const ProgramNode& node) {
    for (const auto& child : node.children) {
      visit(child);
    }
  };
  virtual void visit(const FunctionDefinitionNode& node) {
    visit(*node.block);
  }
  virtual void visit(const BlockNode& node) {
    for (const auto& child : node.children) {
      visit(child);
    }
  }
  virtual void visit(const StatementNode& node) {
    visit(*node.node);
  }
  virtual void visit(const AssignmentNode& node) {
    // do nothing
  };

  void visit (const Node& node) {
    if (std::holds_alternative<ProgramNode>(node)) {
      visit(std::get<ProgramNode>(node));
    }
    else if (std::holds_alternative<FunctionDefinitionNode>(node)) {
      visit(std::get<FunctionDefinitionNode>(node));
    }
    else if (std::holds_alternative<BlockNode>(node)) {
      visit(std::get<BlockNode>(node));
    }
    else if (std::holds_alternative<StatementNode>(node)) {
      visit(std::get<StatementNode>(node));
    }
    else if (std::holds_alternative<AssignmentNode>(node)) {
      visit(std::get<AssignmentNode>(node));
    }
  }
};

class PrintVisitor : public Visitor {
public:
  void visit(const AssignmentNode& node) override {
    std::cout << "AssignmentNode: " << node.identifier << " = " << node.value << std::endl;
  }
  void visit(const Node& node) {
    Visitor::visit(node);
  }
};
