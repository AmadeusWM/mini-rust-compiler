#include "tast_driver.h"
#include "nodes/body.h"
#include "visitors/interpreter_visitor.h"
#include "visitors/print_visitor.h"
#include "visitors/typecheck_visitor.h"

TASTDriver::TASTDriver(P<TAST::Crate> tast) : tast(std::move(tast)) {

}

void print_duration(std::chrono::nanoseconds duration) {
    if (duration.count() < 1'000) {
        // Nanoseconds
        spdlog::info("Interpreting took {} nanoseconds", duration.count());
    } else if (duration.count() < 1'000'000) {
        // Microseconds
        auto microseconds =
            std::chrono::duration_cast<std::chrono::microseconds>(duration);
        spdlog::info("Interpreting took {} microseconds", microseconds.count());
    } else if (duration.count() < 1'000'000'000) {
        // Milliseconds
        auto milliseconds =
            std::chrono::duration_cast<std::chrono::milliseconds>(duration);
        spdlog::info("Interpreting took {} milliseconds", milliseconds.count());
    } else {
        // Seconds
        auto seconds = std::chrono::duration_cast<std::chrono::seconds>(duration);
        spdlog::info("Interpreting took {} seconds", seconds.count());
    }
}

P<Driver> TASTDriver::execute() {
  print_step("Untyped TAST");
  print();
  TAST::TypecheckVisitor typechecker(*this->tast);
  print_step("Typechecking TAST");
  typechecker.typecheck();
  print_step("Typed TAST");
  print();
  this->interpret();
  return nullptr;
}

void TASTDriver::interpret() {
  print_step("Interpreting Started");
  TAST::InterpreterVisitor interpreter(*this->tast);
  auto start = std::chrono::high_resolution_clock::now();

  interpreter.interpret();

  auto end = std::chrono::high_resolution_clock::now();
  auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);
  print_step("Interpreting Finished");
  print_duration(duration);
}

void TASTDriver::print() {
  TAST::PrintVisitor visitor;
  visitor.visit(*tast);
}

void TASTDriver::typecheck(){
}
