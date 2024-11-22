#pragma once

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
  };
}
