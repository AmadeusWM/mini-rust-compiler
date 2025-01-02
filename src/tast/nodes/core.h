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

typedef std::variant<
  IntValue,
  FloatValue,
  StrValue,
  UnitValue
> SymbolValueKind;

struct SymbolValue {
  SymbolValueKind kind;

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
      }
    }, kind);
    }
};
}
