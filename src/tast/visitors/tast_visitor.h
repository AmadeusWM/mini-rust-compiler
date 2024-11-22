#pragma once

#include "nodes/body.h"
#include <spdlog/spdlog.h>

namespace TAST {

template <class T> class Visitor {
T virtual visit(const Crate& crate) {
  spdlog::debug("visiting crate");
}
};

class DefaultVisitor : public Visitor<void> {
  void visit(const Crate& crate) override {
    spdlog::debug("visiting crate");
  }
};
}
