#pragma once
#include <cwchar>
#include <memory>
#include <spdlog/spdlog.h>
#include "util/util.h"

class Driver {
public:
  /**
  * Every driver should implement this method, which will
  */
  virtual P<Driver> execute() = 0;
  virtual std::string name() = 0;

  void print_step(std::string step_name) {
    const int max_length = 40;
    int total_length = step_name.length() + 2;
    int padding = (max_length - total_length) / 2;
    if (padding < 0) padding = 0;
    std::string border(padding, '=');
    spdlog::info("{} {} {}", border, step_name, border);
  }
};
