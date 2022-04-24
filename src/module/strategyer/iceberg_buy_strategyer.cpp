#include "module/strategyer/iceberg_buy_strategyer.h"

#include "cpr/cpr.h"
#include "strategyer_utils.h"

const int MINIMUM_NUM_PRICE = 2;

namespace burglar {

void IcebergBuyStrategyer::exec(std::shared_ptr<Context> ctx) {
  double currentPrice = ctx->binance_data_.last_price_;
  double currentOwn = 100.0;
  updateWithNewPrice(currentPrice);
  if (numOfPrice < MINIMUM_NUM_PRICE) {
    std::cout << "no enough records...\n";
    return;
  }

  std::cout << std::setprecision(4) << std::fixed;
  Action::Op op;
  double unit;
  double price;

  if (currentPrice > averagePrice) {
    op = Action::Op::buy;
    unit = strategyer_utils::getAmount(currentOwn, currentPrice, averagePrice);
    price = strategyer_utils::getBuyPrice(currentOwn, currentPrice, averagePrice);
    std::cout << "Buy " << unit << " Units with Price " << price << "\n";
  } else {
    op = Action::Op::sell;
    unit = strategyer_utils::getAmount(currentOwn, currentPrice, averagePrice);
    price = strategyer_utils::getSellPrice(currentOwn, currentPrice, averagePrice);
    std::cout << "Sell " << unit << " Units with Price " << price << "\n";
  }

  Action action;
  action.op_ = op;
  action.unit = unit;
  action.price = price;

  ctx->strategy_actions_->push(action);
}

int IcebergBuyStrategyer::init(const boost::property_tree::ptree& p) {
  return 0;
}

}  // namespace burglar