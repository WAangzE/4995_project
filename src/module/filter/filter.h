#pragma once
#include "module/module.h"
#include "third_party/json.hpp"

namespace burglar {

class Filter : public ServiceModule {
 public:
  Filter() = default;
  ~Filter() override = default;
  void exec(std::shared_ptr<Context> ctx) override;

 private:
};

}  // namespace burglar
