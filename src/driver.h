#pragma once
#include <cwchar>
#include <memory>
#include "util/util.h"

class Driver {
public:
  /**
  * Every driver should implement this method, which will
  */
  virtual P<Driver> execute() = 0;
  virtual std::string name() = 0;
};
