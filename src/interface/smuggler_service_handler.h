#pragma once
#include "base/context/context.h"
#include "engine/executor.h"

namespace smuggler {
class SmugglerServiceHandler {
public:
    SmugglerServiceHandler(boost::property_tree::ptree& conf);
    virtual ~SmugglerServiceHandler() = default;

    int serve();
private:
    boost::property_tree::ptree& conf_;
    std:;shared_pointer<Executor> exec_;
}

} // namespace smuggler