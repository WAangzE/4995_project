#include "module.h"

namespace smuggler {

ServiceModule::ServiceModule(){
    std::cout << "ServiceModule() \n";
}

ServiceModule::~ServiceModule(){
    std::cout << "~ServiceModule() \n";
}

void ServiceModule::exec(std::shared_ptr<Context> ctx){
    std::cout << "exec ServiceModule() \n";
}

}