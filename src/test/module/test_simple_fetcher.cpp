#include "gtest/gtest.h"
#include "module/fetcher/simple_binance_fetcher.h"

TEST(SimpleFetcher, basic) {
  try {
    burglar::SimpleBinanceFetcher fetcher("https://www.binance.com/api/v3/ticker/24hr");
    auto ctx = std::make_shared<burglar::Context>();
    fetcher.exec(ctx);
  } catch (std::exception &e) {
    std::cout << e.what() << std::endl;
  }
}