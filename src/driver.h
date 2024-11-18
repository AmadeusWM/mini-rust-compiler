#pragma once


class Driver {
  /**
  * Every driver should implement this method, which will
  */
  virtual std::unique_ptr<Driver> execute() = 0;
}
