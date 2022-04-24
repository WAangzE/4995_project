#include "module/module.h"

namespace burglar {

ServiceModule::ServiceModule() { std::cout << "ServiceModule()" << std::endl; }

ServiceModule::~ServiceModule() { std::cout << "~ServiceModule() \n"; }

}  // namespace burglar