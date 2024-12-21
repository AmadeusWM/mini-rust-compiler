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
    if (i >= path.size()) {
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
};

struct PrimitiveType {
};

using NamespaceValue = std::variant<Namespace, PrimitiveType, AST::NodeId>;

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
        throw std::runtime_error("Namespace already exists");
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
  *   For example, if there is a namspace `X::main::a::b`, and we want to find `a::b`, we would call
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
    for (size_t i = ns.path.size() - 1; i >= 0; i--) {
      auto [first, second] = ns.split(i);
      if (second.equals(scope)) {
        break;
      }
      auto result = this->get(Namespace::concat(first, ns));
      if (result.has_value()) {
        return result.value();
      }
    }
    return std::nullopt;
  }

  Opt<NamespaceValue> get(const Namespace& ns) const {
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
        throw std::runtime_error("Namespace not found");
      }
      return it->second.get(remaining);
    }
  }

  std::string to_string() const {
    std::string result = "";
    if (value.has_value()) {
      if (std::holds_alternative<Namespace>(value.value())) {
        result += std::string("Namespace");
      }
      else if (std::holds_alternative<PrimitiveType>(value.value())) {
        result += std::string("PrimitiveType");
      }
      else {
        result += std::string("NodeId");
      }
    }
    for (const auto& [key, value] : this->children) {
      result += fmt::format("\t{}:{}", key, value.to_string());
    }
    return result;
  }
};
