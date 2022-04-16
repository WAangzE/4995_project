#include "module/strategyer/iceberg_buy_strategyer.h"

#include "cpr/cpr.h"

namespace burglar {

void IcebergBuyStrategyer::exec(std::shared_ptr<Context> ctx) {
    //strategy
    std::cout<< "currentBalance is " << ctx->getBalance() << std::endl;
}


}  // namespace burglar