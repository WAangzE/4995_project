#include <chrono>
#include <iomanip>
#include <utility>

#include "module/strategyer/basic_strategyer.h"
#include "utils/work_queue.h"

namespace burglar {
class IcebergBuyStrategyer : public BasicStrategyer {
 public:
  IcebergBuyStrategyer()
      : numOfPrice(0),
        averagePrice(0){
            // start
        };
  void exec(std::shared_ptr<Context> ctx) override;
  int getNumOfPrice() const { return numOfPrice; }
  void setNumOfPrice(int num) { numOfPrice = num; }
  double getAveragePrice() const { return averagePrice; }
  void setAveragePrice(double average) { averagePrice = average; }
  std::vector<double>& getHistoryPrice() { return historyPrice; }
  void updateWithNewPrice(double newPrice) {
    averagePrice = (numOfPrice * averagePrice + newPrice) / (numOfPrice + 1);
    numOfPrice++;
    historyPrice.push_back(newPrice);
  }

 private:
  std::vector<double> historyPrice;
  int numOfPrice;
  double averagePrice;
};
}  // namespace burglar