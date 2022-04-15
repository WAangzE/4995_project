#pragma once
#include <boost/property_tree/ptree.hpp>
#include <memory>

#include "base/context/context.h"
#include "engine/executor.h"
#include "module/module.h"

namespace burglar {
class SmugglerServiceHandler {
 public:
  SmugglerServiceHandler(boost::property_tree::ptree& conf);
  virtual ~SmugglerServiceHandler() = default;

  int serve();

 private:
  boost::property_tree::ptree& conf_;
  std::shared_ptr<Executor<ServiceModule>> exec_;
};

}  // namespace burglar