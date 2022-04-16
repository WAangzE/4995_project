#include "module/strategyer/basic_strategyer.h"

namespace burglar {

BasicStrategyer::BasicStrategyer() { std::cout << "BasicStrategyer()" << std::endl; }

BasicStrategyer::~BasicStrategyer() { std::cout << "~BasicStrategyer() \n"; }

void BasicStrategyer::exec(std::shared_ptr<Context> ctx) { std::cout << "exec BasicStrategyer \n"; }
}  // namespace burglar