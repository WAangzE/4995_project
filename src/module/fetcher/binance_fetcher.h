#pragma once
#include "module/module.h"
#include <memory>

namespace smuggler {
class BinanceFetcher : public ServiceModule {
public:
    BinanceFetcher();
    virtual ~BinanceFetcher();
    virtual void exec(std::shared_ptr<Context> ctx);
};
}