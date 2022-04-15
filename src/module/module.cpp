#include "module/module.h"

namespace burglar {

ServiceModule::ServiceModule() { std::cout << "ServiceModule()" << std::endl; }

ServiceModule::~ServiceModule() { std::cout << "~ServiceModule() \n"; }

void ServiceModule::exec(std::shared_ptr<Context> ctx) { std::cout << "exec ServiceModule() \n"; }

}  // namespace burglar