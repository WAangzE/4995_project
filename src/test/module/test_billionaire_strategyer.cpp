#include "cpr/cpr.h"
#include "gtest/gtest.h"
#include "module/strategyer/billionaire_strategyer.h"

TEST(BillionaireStrategyer, basic) {
  try {
    const int initBalance = 100;
    const int numOfPrice = 10;
    const double averagePrice = 0.12;
    burglar::BillionaireStrategyer strategyer{};
    auto ctx = std::make_shared<burglar::Context>();
    ctx->user_state_.balance_ = initBalance;
    EXPECT_EQ(0, strategyer.getNumOfPrice());
    EXPECT_EQ(0, strategyer.getAveragePrice());

    strategyer.setNumOfPrice(numOfPrice);
    strategyer.setAveragePrice(averagePrice);
    EXPECT_EQ(numOfPrice, strategyer.getNumOfPrice());
    EXPECT_EQ(averagePrice, strategyer.getAveragePrice());
    auto& hisPrice = strategyer.getHistoryPrice();
    hisPrice = {0.12, 0.12, 0.12, 0.12, 0.12, 0.12, 0.12, 0.12, 0.12, 0.12};

    for (int i = 0; i < numOfPrice; i++) {
      double newPrice{};
      if (i < numOfPrice / 2) {
        newPrice = averagePrice + i * 0.01;
      } else {
        newPrice = averagePrice - i * 0.01;
      }
      strategyer.updateWithNewPrice(newPrice);
      ctx->binance_data_.last_price_ = newPrice;
      strategyer.exec(ctx);
    }

  } catch (std::exception& e) {
    std::cout << e.what() << std::endl;
  }
}

TEST(BillionaireStrategyer, noEnoughRecord) {
  try {
    const int initBalance = 100;
    const int numOfPrice = 10;
    burglar::BillionaireStrategyer strategyer{};
    auto ctx = std::make_shared<burglar::Context>();
    ctx->user_state_.balance_ = initBalance;
    EXPECT_EQ(0, strategyer.getNumOfPrice());
    EXPECT_EQ(0, strategyer.getAveragePrice());

    auto& hisPrice = strategyer.getHistoryPrice();
    for (int i = 0; i < numOfPrice; i++) {
      double newPrice = 0.12;
      strategyer.updateWithNewPrice(newPrice);
      ctx->binance_data_.last_price_ = newPrice;
      strategyer.exec(ctx);
    }

  } catch (std::exception& e) {
    std::cout << e.what() << std::endl;
  }
}

TEST(BillionaireStrategyer, Unconsistent) {
  try {
    const int initBalance = 100;
    const int numOfPrice = 10;
    const int balanceBar = 0.7;
    const double tune = 0.02;
    burglar::BillionaireStrategyer strategyer{};
    auto ctx = std::make_shared<burglar::Context>();
    ctx->user_state_.balance_ = initBalance;
    EXPECT_EQ(0, strategyer.getNumOfPrice());
    EXPECT_EQ(0, strategyer.getAveragePrice());

    auto& hisPrice = strategyer.getHistoryPrice();
    for (int i = 0; i < numOfPrice; i++) {
      double newPrice = 0.12;
      if (ctx->user_state_.balance_ > balanceBar * initBalance)
        newPrice *= 1 + tune;
      else
        newPrice *= 1 - tune;
      strategyer.updateWithNewPrice(newPrice);
      ctx->binance_data_.last_price_ = newPrice;
      strategyer.exec(ctx);
    }

  } catch (std::exception& e) {
    std::cout << e.what() << std::endl;
  }
}