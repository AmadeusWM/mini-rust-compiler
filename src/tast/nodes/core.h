#pragma once

#include "nodes/core.h"
#include <cstdint>
#include <string>
#include <variant>
#include <vector>

namespace TAST {
typedef uint64_t NodeId;

 
typedef std::variant<
    AST::Ident>
    PatKind;

struct Pat {
  PatKind kind;
};

typedef std::variant<
  int8_t,
  int16_t,
  int32_t,
  int64_t,
  float,
  double
> NumberValue;

typedef std::variant<
  std::string
> StrValue;

struct UnitValue{};

typedef std::variant<bool> BoolValue;

typedef std::variant<
  NumberValue,
  StrValue,
  BoolValue,
  UnitValue
> SymbolValueKind;

struct SymbolValue {
  SymbolValueKind kind;

  bool as_bool() {
    if (auto boolPtr = std::get_if<BoolValue>(&kind)) {
        return std::get<bool>(*boolPtr);
    } else {
        throw std::bad_variant_access();
    }
  }

  std::string to_string() {
    return std::visit(overloaded{
      [](const NumberValue& numVal) -> std::string {
        return std::visit([](auto&& arg) -> std::string {
          return std::to_string(arg);
        }, numVal);
      },
      [](const StrValue& strVal) -> std::string {
        return std::visit([](auto&& arg) -> std::string {
          return arg;
        }, strVal);
      },
      [](const UnitValue&) -> std::string {
        return "()";
      },
      [](const BoolValue& b) -> std::string {
        auto b_value = std::get<bool>(b);
        return b_value ? "true" : "false";
      }
    }, kind);
    }
};
}
