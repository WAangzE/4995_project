#pragma once
#include "base/context/context.h"
#include "engine/executor.h"
#include <boost/property_tree/ptree.hpp>
#include <memory>
#include "module/module.h"

namespace smuggler {
class SmugglerServiceHandler {
public:
    SmugglerServiceHandler(boost::property_tree::ptree& conf);
    virtual ~SmugglerServiceHandler() = default;

    int serve();
private:
    boost::property_tree::ptree& conf_;
    std::shared_ptr<Executor<ServiceModule>> exec_;
};

} // namespace smuggler