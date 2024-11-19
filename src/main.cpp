// #include "lexer/lexer.h"
#include "ast/lexer/scanner.h"
#include "ast/ast_driver.h"
#include <cstdio>
#include <iostream>
#include <fstream>
#include <spdlog/common.h>
#include "spdlog/spdlog.h"

int main(int argc, char *argv[]) {
  spdlog::set_level(spdlog::level::debug);

  std::ifstream file(argv[1]);

  Scanner scanner(&file);
  P<Driver> driver = P<Driver>(new ASTDriver(&scanner));

  try {
    while (driver != nullptr) {
      spdlog::info("Executing driver: {}", driver->name());
      driver = driver->execute();
    }
  } catch (const std::exception &e) {
    spdlog::error("{}", e.what());
    return 1;
  }
  return 0;
}
