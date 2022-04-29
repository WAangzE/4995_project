#pragma once
#include "module/module.h"
#include "third_party/json.hpp"

namespace burglar {

class SimplePriceFilter : public ServiceModule {
 public:
  SimplePriceFilter() = default;
  ~SimplePriceFilter() override = default;

  int init(const boost::property_tree::ptree& conf) override;
  void exec(std::shared_ptr<Context> ctx) override;

 private:
};

}  // namespace burglar
