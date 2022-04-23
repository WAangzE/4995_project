#include "cpr/cpr.h"
#include "gtest/gtest.h"
#include "module/fetcher/simple_binance_fetcher.h"
#include "utils/work_queue.h"

TEST(SimpleFetcher, basic) {
  try {
    burglar::SimpleBinanceFetcher fetcher("https://www.binance.com/api/v3/ticker/24hr");
    auto ctx = std::make_shared<burglar::Context>();
    fetcher.exec(ctx);
    std::cout << ctx->binance_data_.raw_content_ << std::endl;
  } catch (std::exception& e) {
    std::cout << e.what() << std::endl;
  }
}