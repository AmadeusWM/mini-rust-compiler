#pragma once

#include "nodes/core.h"
#include "util.h"
#include <fmt/format.h>
#include <map>
#include <optional>
#include <spdlog/spdlog.h>
#include <stdexcept>
#include <string>
#include <variant>
#include <vector>

struct Namespace{
  std::vector<std::string> path;

  std::pair<Namespace, Namespace> split(size_t i) const {
    if (i > path.size()) {
      throw std::runtime_error("Index out of bounds");
    }
    return {
      Namespace{ .path = std::vector<std::string>(path.begin(), path.begin() + i) },
      Namespace{ .path = std::vector<std::string>(path.begin() + i, path.end()) },
    };
  }
  std::pair<std::string, Namespace> split_first() const {
    if (path.size() == 0) {
      throw std::runtime_error("Cannot split empty namespace");
    }
    spdlog::debug("split_first: {}", path[0]);
    return {
      path[0],
      Namespace{ .path = std::vector<std::string>(path.begin() + 1, path.end()) },
    };
  }
  static Namespace concat(Namespace first, Namespace second) {
    std::vector<std::string> result = first.path;
    result.insert(result.end(), second.path.begin(), second.path.end());
    return Namespace{ .path = result };
  }
  bool equals(Namespace other) const {
    if (path.size() != other.path.size()) {
      return false;
    }
    for (size_t i = 0; i < path.size(); i++) {
      if (path[i] != other.path[i]) {
        return false;
      }
    }
    return true;
  }
  std::string to_string() const {
    return fmt::format("{}", fmt::join(path, "::"));
  }
  Namespace clone() {
    for (const auto segment : path) {
      
    }
  }
};

namespace Primitive{
  struct I8{};
  struct I32{};
  struct F32{};
  struct Str{};
  struct Bool{};
}

typedef std::variant<
  Primitive::I8,
  Primitive::I32,
  Primitive::F32,
  Primitive::Str,
  Primitive::Bool
> PrimitiveKind;

struct PrimitiveType {
  PrimitiveKind kind;
  static Opt<PrimitiveType> from(std::string identifier) {
    if (identifier == "i8") {
      return PrimitiveType{ .kind = Primitive::I8{} };
    } else if (identifier == "i32") {
      return PrimitiveType{ .kind = Primitive::I32{} };
    } else if (identifier == "f32") {
      return PrimitiveType{ .kind = Primitive::F32{} };
    } else if (identifier == "str") {
      return PrimitiveType{ .kind = Primitive::Str{} };
    } else if (identifier == "bool") {
      return PrimitiveType{ .kind = Primitive::Bool{} };
    }
    else {
      return std::nullopt;
    }
  }
};

using NamespaceValue = std::variant<
  // Namespace: used for e.g. `type x = X::A`
  Namespace,
  // PrimitiveTypes are i32, etc.
  PrimitiveType,
  // Used to describe a node in the AST
  AST::NodeId
>;

class NamespaceNode {
private:
  Opt<NamespaceValue> value = std::nullopt;
  std::map<std::string, NamespaceNode> children;
public:
  NamespaceNode() {
  }

  void set(const Namespace& ns, NamespaceValue value) {
    spdlog::debug("Namespace: {}", ns.path.size());
    if (ns.path.size() == 0) {
      if (this->value.has_value()) {
        throw std::runtime_error("Namespace already exists");;
      }
      this->value = value;
      return;
    }
    auto [segment, remaining] = ns.split_first();
    auto it = children.find(segment);
    if (it == children.end()) {
      children[segment] = NamespaceNode();
      children[segment].set(remaining, value);
    }
    else {
      it->second.set(remaining, value);
    }
  }

  /**
  * @brief Find a value for this namespace within the span `root` -> `scope`
  *   For example, if there is a namespace `X::main::a::b`, and we want to find `a::b` from `X::main::a`, we would call
  *   `get(X::main::a, X::main::a::b, X)`
  *   This would return the value of `a::b`
  *   And it would only look up till the namespace `X` is reached
  * @param root Look up from this root
  * @param ns Namespace to find
  * @param scope Stop at this namespace
  */
  Opt<NamespaceValue> get(
    const Namespace& root,
    const Namespace& ns,
    const Namespace& scope = {.path = {}})
  {
    spdlog::debug("Looking up:");
    spdlog::debug("\tRoot: {}", root.to_string());
    spdlog::debug("\tNs: {}", ns.to_string());
    spdlog::debug("\tScope: {}", scope.to_string());

    for (size_t i = root.path.size(); i >= 0; i--) {
      auto [first, second] = root.split(i);
      spdlog::debug("First: {}", first.to_string());
      spdlog::debug("Second: {}", second.to_string());
      auto result = this->get(Namespace::concat(first, ns));
      if (result.has_value()) {
        return result.value();
      }
      if (first.equals(scope)) {
        break;
      }
    }
    throw std::runtime_error(fmt::format("Namespace '{}' not found within '{}' within scope '{}'", ns.to_string(), root.to_string(), scope.to_string()));
  }

  Opt<NamespaceValue> get(const Namespace& ns) const {
    spdlog::debug("Looking up namespace {}", ns.to_string());
    if (ns.path.size() == 0) {
      if (!value.has_value()) {
        return std::nullopt;
      }
      return value.value();
    }
    else {
      auto [segment, remaining] = ns.split_first();
      auto it = children.find(segment);
      if (it == children.end()) {
        return std::nullopt;
      }
      return it->second.get(remaining);
    }
  }

  Opt<Namespace> find_namespace(AST::NodeId id) const {
    spdlog::debug("children: {}", children.size());
    for (const auto& [key, child] : children) {
      spdlog::debug("find_namespace: {}", key);
      if (child.value.has_value() && std::holds_alternative<AST::NodeId>(child.value.value())) {
        if (std::get<AST::NodeId>(child.value.value()) == id) {
          return Namespace{ .path = {key} };
        }
      }
      auto result = child.find_namespace(id);
      if (result.has_value() && !result.value().path.empty()) {
        Namespace ns = Namespace{ .path = {key} };
        return {Namespace::concat(ns, result.value())};
      }
    }
    return std::nullopt;
  }

  std::string to_string() const {
    std::string result = "";
    if (value.has_value()) {
      if (std::holds_alternative<Namespace>(value.value())) {
        result += fmt::format("[Namespace: {}, ", std::get<Namespace>(value.value()).to_string());
      }
      else if (std::holds_alternative<PrimitiveType>(value.value())) {
        result += std::string("[PrimitiveType, ");
      }
      else {
        result += fmt::format("[NodeId: {}, ", std::get<AST::NodeId>(value.value()));
      }
    }
    for (const auto& [key, value] : this->children) {
      result += fmt::format("{}:({})]", key, value.to_string());
    }
    return result;
  }

  void resolve_types(NamespaceNode* root = nullptr) {
    if (root == nullptr) {
      root = this;
    }
    for (auto& child : children) {
      if (std::holds_alternative<Namespace>(child.second.value.value())) {
        auto ns = std::get<Namespace>(child.second.value.value());

        if (ns.path.size() == 1) {
          child.second.value = PrimitiveType::from(ns.path[0]);
        } else {
          throw std::runtime_error("Not a primitive: " + ns.to_string());
          // auto value = root->get(ns);
          // if (!value.has_value()) {
          //   throw std::runtime_error("Namespace not found");
          // }
          // child.second.value = value.value();
        }
      }
      child.second.resolve_types(root);
    }
  }
};
