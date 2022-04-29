#include "module/strategyer/basic_strategyer.h"

namespace burglar {

BasicStrategyer::BasicStrategyer() {}

BasicStrategyer::~BasicStrategyer() {}

void BasicStrategyer::exec(std::shared_ptr<Context> ctx) {}

int BasicStrategyer::init(const boost::property_tree::ptree& p) { return 0; }
}  // namespace burglar