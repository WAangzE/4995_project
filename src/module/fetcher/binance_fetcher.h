#pragma once
#include <memory>

#include "module/module.h"

namespace smuggler {
class BinanceFetcher : public ServiceModule {
 public:
  BinanceFetcher();
  virtual ~BinanceFetcher();
  virtual void exec(std::shared_ptr<Context> ctx);
};
}  // namespace smuggler