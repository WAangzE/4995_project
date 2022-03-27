#pragma once
#include "base/context/context.h"
#include "engine/executor.h"
#include <boost/property_tree/ptree.hpp>
#include <memory>

namespace smuggler {
class SmugglerServiceHandler {
public:
    SmugglerServiceHandler(boost::property_tree::ptree& conf);
    virtual ~SmugglerServiceHandler() = default;

    int serve();
private:
    boost::property_tree::ptree& conf_;
    std::shared_ptr<Executor<double>> exec_;
};

} // namespace smuggler