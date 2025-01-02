#pragma once

#include "util.h"
#include <variant>
namespace TAST {
  struct  I8 {
  };
  struct  I32 {
  };

  typedef std::variant<
    I8,
    I32
  > IntTy;

  struct F32 {
  };

  typedef std::variant<
    F32
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
      // TODO: what about TyVars?? these should never be used I guess? As the literal types should be resolved already when used anywhere, variables can never have TyVar (unless late initialized!!)
      return std::visit(overloaded {
        // if simply the same type, resolve if same subtype (e.g. i32 === i32)
        [&](const IntTy& lhs, const IntTy& rhs) { return lhs.index() == rhs.index() ? std::optional<Ty>(lhs) : std::nullopt; },
        [&](const FloatTy& lhs, const FloatTy& rhs) { return lhs.index() == rhs.index() ? std::optional<Ty>(lhs) : std::nullopt; },
        [&](const InferTy& lhs, const InferTy& rhs) {
          return std::visit(overloaded {
            [&](const TyVar& var, const TyVar& r) { return std::optional<Ty>(lhs); },
            [&](const TyVar& var, const auto& r) { return std::optional<Ty>(rhs); },
            [&](const auto& l, const TyVar& var) { return std::optional<Ty>(lhs); },
            [&](const auto& l, const auto& r) { return lhs.index() == rhs.index() ? std::optional<Ty>(lhs) : std::nullopt; }
          }, lhs, rhs);
        },
        // if one is a variable, resolve to the accurate type
        [&](const InferTy& lhs, const IntTy& rhs) { return std::holds_alternative<IntVar>(lhs) || std::holds_alternative<TyVar>(lhs) ? std::optional<Ty>(rhs) : std::nullopt; },
        [&](const IntTy& lhs, const InferTy& rhs) { return std::holds_alternative<IntVar>(rhs) || std::holds_alternative<TyVar>(rhs) ? std::optional<Ty>(lhs) : std::nullopt; },
        [&](const InferTy& lhs, const FloatTy& rhs) { return std::holds_alternative<FloatVar>(lhs) ? std::optional<Ty>(rhs) : std::nullopt; },
        [&](const FloatTy& lhs, const InferTy& rhs) { return std::holds_alternative<FloatVar>(rhs) ? std::optional<Ty>(lhs) : std::nullopt; },
        // TyVar cases: simply resolve to the other type
        [&](const auto& lhs, const InferTy& rhs) { return std::optional<Ty>(lhs); },
        [&](const InferTy& lhs, const auto& rhs) { return std::optional<Ty>(rhs); },
        // when all nothing else matches, we check if it is the same type
        [&](const auto& lhs, const auto& rhs) { return kind.index() == other.kind.index() ? std::optional<Ty>(lhs) : std::nullopt; }
      }, kind, other.kind);
    }

    // NOTE: these will be used in the interpreter!

    bool isVar() {
      return std::holds_alternative<InferTy>(kind) && std::holds_alternative<TyVar>(std::get<InferTy>(kind));
    }

    bool isInt() {
      return std::holds_alternative<IntTy>(kind)
        || (std::holds_alternative<InferTy>(kind) && std::holds_alternative<IntVar>(std::get<InferTy>(kind)));
    }

    bool isFloat() {
      return std::holds_alternative<FloatTy>(kind)
        || (std::holds_alternative<InferTy>(kind) && std::holds_alternative<FloatVar>(std::get<InferTy>(kind)));
    }
    std::string to_string() const {
      return std::visit(overloaded {
        [](const Unit&) { return "Unit"; },
        [](const IntTy& intTy) {
          return std::visit(overloaded {
            [](const I8&) { return "I8"; },
            [](const I32&) { return "I32"; }
          }, intTy);
        },
        [](const FloatTy& floatTy) {
          return std::visit(overloaded {
            [](const F32&) { return "F32"; }
          }, floatTy);
        },
        [](const StrTy&) { return "StrTy"; },
        [](const FnDefTy&) { return "FnDefTy"; },
        [](const InferTy& inferTy) {
          return std::visit(overloaded {
            [](const TyVar&) { return "TyVar"; },
            [](const IntVar&) { return "IntVar"; },
            [](const FloatVar&) { return "FloatVar"; }
          }, inferTy);
        }
      }, kind);
    }
  };
}
