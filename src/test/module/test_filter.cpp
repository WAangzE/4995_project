#include "gtest/gtest.h"
#include "module/fetcher/simple_binance_fetcher.h"
#include "module/filter/filter.h"
#include "third_party/json.hpp"

using namespace burglar;
using namespace nlohmann;

TEST(Filter, basic) {
  SimpleBinanceFetcher fetcher("https://www.binance.com/api/v3/ticker/24hr");
  auto ctx = std::make_shared<Context>();
  fetcher.exec(ctx);
  //  std::cout << ctx->binance_data_.raw_content_ << std::endl;

  Filter filter;
  filter.exec(ctx);

  //  json j = json::parse(ctx->binance_data_.raw_content_);
  //  std::cout << j[0]["count"];
}