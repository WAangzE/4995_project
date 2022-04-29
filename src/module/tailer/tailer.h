#pragma once
#include "module/module.h"
#include "third_party/json.hpp"

namespace burglar {

class Tailer : public ServiceModule {
 public:
  Tailer() = default;
  ~Tailer() override = default;

 private:
};

}  // namespace burglar
