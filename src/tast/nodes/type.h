#pragma once

#include "util.h"
#include <variant>
namespace TAST {
  struct  I8 {
  };

  typedef std::variant<
    I8
  > IntTy;

  struct F8 {
  };

  typedef std::variant<
    F8
  > FloatTy;

  struct StrTy{};
  struct FnDefTy{};

  struct TyVar{};
  struct IntVar{};
  struct FloatVar{};

  typedef std::variant<
    TyVar,
    IntVar,
    FloatVar
  > InferTy;

  struct Unit{};

  typedef std::variant<
    Unit,
    IntTy,
    FloatTy,
    StrTy,
    FnDefTy,
    InferTy
  > TyKind;

  struct Ty {
    TyKind kind;

    Opt<Ty> resolve(const Ty& other) const {
      return std::visit(overloaded {
        // if simply the same type, resolve if same subtype (e.g. i32 === i32)
        [&](const IntTy& lhs, const IntTy& rhs) { return lhs.index() == rhs.index() ? std::optional<Ty>(lhs) : std::nullopt; },
        [&](const FloatTy& lhs, const FloatTy& rhs) { return lhs.index() == rhs.index() ? std::optional<Ty>(lhs) : std::nullopt; },
        [&](const InferTy& lhs, const InferTy& rhs) { return lhs.index() == rhs.index() ? std::optional<Ty>(lhs) : std::nullopt; },
        // if one is a variable, resolve to the accurate type
        [&](const InferTy& lhs, const IntTy& rhs) { return std::holds_alternative<IntVar>(lhs) ? std::optional<Ty>(rhs) : std::nullopt; },
        [&](const IntTy& lhs, const InferTy& rhs) { return std::holds_alternative<IntVar>(rhs) ? std::optional<Ty>(lhs) : std::nullopt; },
        [&](const InferTy& lhs, const FloatTy& rhs) { return std::holds_alternative<FloatVar>(lhs) ? std::optional<Ty>(rhs) : std::nullopt; },
        [&](const FloatTy& lhs, const InferTy& rhs) { return std::holds_alternative<FloatVar>(rhs) ? std::optional<Ty>(lhs) : std::nullopt; },
        // when all nothing else matches, we check if it is the same type
        [&](const auto& lhs, const auto& rhs) { return kind.index() == other.kind.index() ? std::optional<Ty>(lhs) : std::nullopt; }
      }, kind, other.kind);
    }

    // NOTE: these will be used in the interpreter!

    bool isInt() {
      return std::holds_alternative<IntTy>(kind)
        || (std::holds_alternative<InferTy>(kind) && std::holds_alternative<IntVar>(std::get<InferTy>(kind)));
    }

    bool isFloat() {
      return std::holds_alternative<FloatTy>(kind)
        || (std::holds_alternative<InferTy>(kind) && std::holds_alternative<FloatVar>(std::get<InferTy>(kind)));
    }
  };
}
