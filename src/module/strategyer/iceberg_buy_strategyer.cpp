#include "module/strategyer/iceberg_buy_strategyer.h"

#include "cpr/cpr.h"
#include "strategyer_utils.h"

const int MINIMUM_NUM_PRICE = 5;

namespace burglar {
    


void IcebergBuyStrategyer::exec(std::shared_ptr<Context> ctx) {
    //strategy
    // std::cout<< "currentBalance is " << ctx->getBalance() << std::endl;
    if (numOfPrice < MINIMUM_NUM_PRICE) {
        std::cout<< "no enough records...\n";
        return;
    }
    double currentPrice = 1.5;
    double currentOwn = 100.0;
    std::cout << std::setprecision(4) << std::fixed;
    if (currentPrice>averagePrice) {
        std:: cout << "Buy " <<strategyer_utils::getAmount(currentOwn, currentPrice, averagePrice) << " Units with Price " <<strategyer_utils::getBuyPrice(currentOwn, currentPrice, averagePrice) << "\n";
    } else {
        std:: cout << "Sell " <<strategyer_utils::getAmount(currentOwn, currentPrice, averagePrice) << " Units with Price " <<strategyer_utils::getSellPrice(currentOwn, currentPrice, averagePrice) << "\n";
    }
    
}


}  // namespace burglar