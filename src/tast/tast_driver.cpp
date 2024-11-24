#include "tast_driver.h"
#include "nodes/body.h"
#include "visitors/print_visitor.h"

TASTDriver::TASTDriver(P<TAST::Crate> tast) : tast(std::move(tast)) {

}

P<Driver> TASTDriver::execute() {
  print();
  return nullptr;
}

void TASTDriver::print() {
  TAST::PrintVisitor visitor;
  visitor.visit(*tast);
}

void TASTDriver::typecheck(){
}
