#pragma once
#include <memory>
#include <utility>

#include "module/module.h"

namespace burglar {
class BinanceFetcher : public ServiceModule {
 public:
  BinanceFetcher();
  explicit BinanceFetcher(std::string api) : api_(std::move(api)) {}

  ~BinanceFetcher() override;
  void exec(std::shared_ptr<Context> ctx) override;

 protected:
  std::string api_;
};
}  // namespace burglar