#include "module/strategyer/billionaire_strategyer.h"

#include "cpr/cpr.h"
#include "strategyer_utils.h"

const int MINIMUM_NUM_PRICE = 2;

namespace burglar {

void BillionaireStrategyer::exec(std::shared_ptr<Context> ctx) {
  double currentPrice = ctx->binance_data_.last_price_;
  double currentOwn = 100.0;
  updateWithNewPrice(currentPrice);
  if (numOfPrice < MINIMUM_NUM_PRICE) {
    std::cout << "no enough records...\n";
    return;
  }
  
  std::cout << std::setprecision(4) << std::fixed;
  if (currentPrice > averagePrice) {
    std::cout << "Buy " << strategyer_utils::getAmount(currentOwn, currentPrice, averagePrice)
              << " Units with Price " << strategyer_utils::getBuyPrice(currentOwn, currentPrice, averagePrice)
              << "\n";
  } else {
    std::cout << "Sell " << strategyer_utils::getAmount(currentOwn, currentPrice, averagePrice)
              << " Units with Price "
              << strategyer_utils::getSellPrice(currentOwn, currentPrice, averagePrice) << "\n";
  }
  //tuple (string,double,double) (op, unit, price)
}

int BillionaireStrategyer::init(const boost::property_tree::ptree& p) {
  return 0;
}

}  // namespace burglar