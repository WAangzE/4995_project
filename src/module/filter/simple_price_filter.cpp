#include "simple_price_filter.h"

using namespace nlohmann;

namespace burglar {

int SimplePriceFilter::init(const boost::property_tree::ptree& conf) {
  conf_ = conf;

  return 0;
}

void SimplePriceFilter::exec(std::shared_ptr<Context> ctx) {
  auto& eth_btc = ctx->binance_data_.json_content_[0];
  auto& b_data = ctx->binance_data_;

  b_data.timestamp_ = std::chrono::system_clock::now();
  b_data.bid_prices_ = std::stod(std::string(eth_btc["bidPrice"]));
  b_data.low_price_ = std::stod(std::string(eth_btc["lowPrice"]));
  b_data.high_price_ = std::stod(std::string(eth_btc["highPrice"]));
  b_data.last_price_ = std::stod(std::string(eth_btc["lastPrice"]));
  b_data.count_ = eth_btc["count"];

  std::cout << b_data.dump();
}

}  // namespace burglar