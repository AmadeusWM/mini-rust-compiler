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
  int32_t
> IntValue;

typedef std::variant<
  float, // f32
  double // f64
> FloatValue;

typedef std::variant<
  std::string
> StrValue;

struct UnitValue{};

typedef std::variant<bool> BoolValue;

typedef std::variant<
  IntValue,
  FloatValue,
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
      [](const IntValue& intVal) -> std::string {
        return std::visit([](auto&& arg) -> std::string {
          return std::to_string(arg);
        }, intVal);
      },
      [](const FloatValue& floatVal) -> std::string {
        return std::visit([](auto&& arg) -> std::string {
          return std::to_string(arg);
        }, floatVal);
      },
      [](const StrValue& strVal) -> std::string {
        return std::visit([](auto&& arg) -> std::string {
          return arg;
        }, strVal);
      },
      [](const UnitValue&) -> std::string {
        return "Unit";
      },
      [](const BoolValue&) -> std::string {
        return std::visit([](auto&& arg) -> std::string {
          return arg ? "true" : "false";
        }, BoolValue{true});
      }
    }, kind);
    }
};
}
