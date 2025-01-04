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
        std::cout << "Interpreting took " << duration.count() << " nanoseconds"
                  << std::endl;
    } else if (duration.count() < 1'000'000) {
        // Microseconds
        auto microseconds =
            std::chrono::duration_cast<std::chrono::microseconds>(duration);
        std::cout << "Interpreting took " << microseconds.count() << " microseconds"
                  << std::endl;
    } else if (duration.count() < 1'000'000'000) {
        // Milliseconds
        auto milliseconds =
            std::chrono::duration_cast<std::chrono::milliseconds>(duration);
        std::cout << "Interpreting took " << milliseconds.count() << " milliseconds"
                  << std::endl;
    } else {
        // Seconds
        auto seconds = std::chrono::duration_cast<std::chrono::seconds>(duration);
        std::cout << std::fixed << std::setprecision(2) // For fractions of seconds
                  << "Interpreting took " << seconds.count() << " seconds" << std::endl;
    }
}

P<Driver> TASTDriver::execute() {
  print();
  TAST::TypecheckVisitor typechecker(*this->tast);
  typechecker.typecheck();
  print();
  TAST::InterpreterVisitor interpreter(*this->tast);
  auto start = std::chrono::high_resolution_clock::now();

  interpreter.interpret();

  auto end = std::chrono::high_resolution_clock::now();
  auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);
  print_duration(duration);
  return nullptr;
}

void TASTDriver::print() {
  TAST::PrintVisitor visitor;
  visitor.visit(*tast);
}

void TASTDriver::typecheck(){
}
