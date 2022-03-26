#pragma once
#include "utils/reflector.h"
#include "base/context/context.h"

namespace smuggler {

class ServiceModule : public ReflectObject {
public:
    ServiceModule();
    virtual ~ServiceModule();
    virtual void exec(std::shared_pointer<Context> ctx);

}

}