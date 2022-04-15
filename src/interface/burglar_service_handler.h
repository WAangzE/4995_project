#pragma once
#include <boost/property_tree/ptree.hpp>
#include <memory>

#include "base/context/context.h"
#include "engine/executor.h"
#include "module/module.h"

namespace burglar {
class BurglarServiceHandler {
 public:
  BurglarServiceHandler(boost::property_tree::ptree& conf);
  virtual ~BurglarServiceHandler() = default;

  int serve();

 private:
  boost::property_tree::ptree& conf_;
  std::shared_ptr<Executor<ServiceModule>> exec_;
};

}  // namespace burglar