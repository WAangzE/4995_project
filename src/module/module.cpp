#pragma once
#include "utils/reflector.h"
#include "base/context/context.h"

namespace smuggler {

ServiceModule::ServiceModule(){
    std::cout << "ServiceModule() \n";
}

ServiceModule::~ServiceModule(){
    std::cout << "~ServiceModule() \n";
}

void ServiceModule::exec(std::shared_pointer<Context> ctx){
    std::cout << "exec ServiceModule() \n";
    return 0;
}

}