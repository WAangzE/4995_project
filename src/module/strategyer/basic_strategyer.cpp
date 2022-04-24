#include "module/strategyer/basic_strategyer.h"

namespace burglar {

BasicStrategyer::BasicStrategyer() { std::cout << "BasicStrategyer()" << std::endl; }

BasicStrategyer::~BasicStrategyer() { std::cout << "~BasicStrategyer() \n"; }

void BasicStrategyer::exec(std::shared_ptr<Context> ctx) { std::cout << "exec BasicStrategyer \n"; }

int BasicStrategyer::init(const boost::property_tree::ptree& p) {return 0;}
}  // namespace burglar