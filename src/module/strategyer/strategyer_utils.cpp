#include "strategyer_utils.h"

namespace strategyer_utils {

double getAmount(double currentOwn, double currentPrice, double averagePrice) {
  using namespace std;
  random_device r;
  default_random_engine e1(r());
  constexpr int randomMax = 100;
  uniform_int_distribution<int> uniform_dist(1, randomMax);
  constexpr double weighted = 0.028;

  double entropy = (double) uniform_dist(e1) / (double) randomMax;
  return weighted * currentOwn * entropy;
}

double getBuyPrice(double currentOwn, double currentPrice, double averagePrice) {
  using namespace std;
  random_device r;
  default_random_engine e1(r());
  constexpr int randomMax = 100;
  uniform_int_distribution<int> uniform_dist(1, randomMax);
  constexpr double weighted = 0.01;

  double entropy = (double) uniform_dist(e1) / (double) randomMax;
  return (1 + weighted * (entropy - 0.5)) * currentPrice;
}

double getSellPrice(double currentOwn, double currentPrice, double averagePrice) {
  using namespace std;
  random_device r;
  default_random_engine e1(r());
  constexpr int randomMax = 100;
  uniform_int_distribution<int> uniform_dist(1, randomMax);
  constexpr double weighted = 0.01;

  double entropy = (double) uniform_dist(e1) / (double) randomMax;
  return (1 + weighted * (entropy - 0.5)) * currentPrice;
}

void fake_sleep() {
  static std::default_random_engine generator;
  static std::uniform_int_distribution<int> distribution(30,50);
  std::this_thread::sleep_for(std::chrono::milliseconds(distribution(generator)));
}

}  // namespace strategyer_utils