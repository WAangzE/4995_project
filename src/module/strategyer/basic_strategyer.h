#pragma once
#include <memory>
#include <utility>

#include "module/module.h"

namespace burglar {
class BasicStrategyer : public ServiceModule {
 public:
  BasicStrategyer();
  ~BasicStrategyer();
  void exec(std::shared_ptr<Context> ctx) override;
  int init(const boost::property_tree::ptree& p) override;

 protected:
  std::string api_;
};
}  // namespace burglar