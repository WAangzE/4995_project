#include "simple_price_filter.h"

using namespace nlohmann;

namespace burglar {

int SimplePriceFilter::init(const boost::property_tree::ptree& conf) {
  conf_ = conf;

  return 0;
}

void SimplePriceFilter::exec(std::shared_ptr<Context> ctx) {
  json json_content = json::parse(ctx->binance_data_.raw_content_);
  auto& eth_btc = json_content[0];
  auto& b_data = ctx->binance_data_;

  b_data.bid_prices_ = std::stod(std::string(eth_btc["bidPrice"]));
  b_data.low_price_ = std::stod(std::string(eth_btc["lowPrice"]));
  b_data.high_price_ = std::stod(std::string(eth_btc["highPrice"]));
  b_data.last_price_ = std::stod(std::string(eth_btc["lastPrice"]));
  b_data.count_ = eth_btc["count"];

  std::cout << ctx->dump();
}

}  // namespace burglar