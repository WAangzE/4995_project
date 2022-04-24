#include "gtest/gtest.h"
#include "module/filter/simple_price_filter.h"
#include "module/fetcher/simple_binance_fetcher.h"

using namespace burglar;
using namespace nlohmann;

//TEST(Filter, basic) {
//  SimpleBinanceFetcher fetcher;
//  auto ctx = std::make_shared<Context>();
//  fetcher.exec(ctx);
////  std::cout << ctx->binance_data_.raw_content_ << std::endl;
//
//  SimplePriceFilter filter;
//  filter.exec(ctx);
//
////  json j = json::parse(ctx->binance_data_.raw_content_);
////  std::cout << j[0]["count"];
//
//}