#include "simple_price_tailer.h"

#include <random>
#include <vector>

#include "base/context/context.h"

namespace burglar {

void SimplePriceTailer::exec(std::shared_ptr<Context> ctx) {
  static std::random_device rd;
  static std::mt19937 mt(rd());
  static std::uniform_real_distribution<double> dist(0.0, 1.0);

  auto actions_queue = ctx->strategy_actions_;
  enum Action::Op op_decided;
  double unit_decided = 0.0;
  double price_decided = 0.0;

  std::vector<Action> actions;
  std::vector<double> weights;
  while (!actions_queue->empty()) {
    actions.push_back(actions_queue->pop());
    weights.push_back(dist(mt));
  }

  size_t idx = std::max_element(weights.begin(), weights.end()) - weights.begin();
  op_decided = actions[idx].op_;

  for (int i = 0; i < weights.size(); i++) {
    unit_decided += actions[i].unit * weights[i];
    price_decided += actions[i].price * weights[i];
  }

  ctx->decision_.op_ = op_decided;
  ctx->decision_.unit = unit_decided;
  ctx->decision_.price = price_decided;
}

int SimplePriceTailer::init(const boost::property_tree::ptree& conf) {
  conf_ = conf;
  return 0;
}
}  // namespace burglar