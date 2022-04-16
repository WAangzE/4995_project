#include "gtest/gtest.h"
#include "module/strategyer/iceberg_buy_strategyer.h"
#include "cpr/cpr.h"

TEST(SimpleStrategyer, basic) {
  try {
    burglar::IcebergBuyStrategyer strategyer{};
    auto ctx = std::make_shared<burglar::Context>();
    ctx->setBalance(100);
    strategyer.exec(ctx);
  } catch (std::exception& e) {
    std::cout << e.what() << std::endl;
  }
}