#pragma once
#include "module/module.h"

namespace burglar {
class SimplePriceTailer : public ServiceModule {
 public:
  SimplePriceTailer() = default;

  void exec(std::shared_ptr<Context> ctx) override;
  int init(const boost::property_tree::ptree& ptree) override;

 private:
  boost::property_tree::ptree conf_;
};
}  // namespace burglar
