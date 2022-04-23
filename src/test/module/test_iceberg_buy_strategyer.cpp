#include "gtest/gtest.h"
#include "module/strategyer/iceberg_buy_strategyer.h"
#include "cpr/cpr.h"

TEST(SimpleStrategyer, basic) {
  try {
    const int initBalance = 100;
    const int numOfPrice = 10;
    const int averagePrice = 0.12;
    burglar::IcebergBuyStrategyer strategyer{};
    auto ctx = std::make_shared<burglar::Context>();
    ctx->setBalance(initBalance);
    EXPECT_EQ(0,strategyer.getNumOfPrice());
    EXPECT_EQ(0,strategyer.getAveragePrice());
    
    strategyer.setNumOfPrice(numOfPrice);
    strategyer.setAveragePrice(averagePrice);
    EXPECT_EQ(numOfPrice,strategyer.getNumOfPrice());
    EXPECT_EQ(averagePrice,strategyer.getAveragePrice());
    auto& hisPrice = strategyer.getHistoryPrice();
    hisPrice = {0.12,0.12,0.12,0.12,0.12,0.12,0.12,0.12,0.12,0.12};

    for (int i = 0; i< numOfPrice; i++){
      if(i<5) {
        strategyer.updateWithNewPrice(averagePrice + i*0.01);
      } else {
        strategyer.updateWithNewPrice(averagePrice - i*0.01);
      }
      strategyer.exec(ctx);
    }
    
  } catch (std::exception& e) {
    std::cout << e.what() << std::endl;
  }
}