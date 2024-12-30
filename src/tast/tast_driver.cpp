#include "tast_driver.h"
#include "nodes/body.h"
#include "visitors/print_visitor.h"
#include "visitors/typecheck_visitor.h"

TASTDriver::TASTDriver(P<TAST::Crate> tast) : tast(std::move(tast)) {

}

P<Driver> TASTDriver::execute() {
  print();
  TAST::TypecheckVisitor typechecker(*this->tast);
  spdlog::debug("Typechecking step");
  typechecker.typecheck();
  spdlog::debug("Typechecking finished");
  print();
  return nullptr;
}

void TASTDriver::print() {
  TAST::PrintVisitor visitor;
  visitor.visit(*tast);
}

void TASTDriver::typecheck(){
}
