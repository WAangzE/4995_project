#pragma once
#include "module/module.h"

namespace smuggler {
class BinanceFetcher : public ServiceModule {
public:
    BinanceFetcher();
    virtual ~BinanceFetcher();
    virtual void exec(std::shared_pointer<Context> ctx);
}
}