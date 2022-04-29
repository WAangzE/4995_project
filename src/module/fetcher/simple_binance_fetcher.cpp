#include "module/fetcher/simple_binance_fetcher.h"

#include "cpr/cpr.h"
#include "third_party/json.hpp"

using namespace nlohmann;

namespace burglar {

int SimpleBinanceFetcher::init(const boost::property_tree::ptree& conf) {
  if (!initialized_) {
    conf_ = conf;
    api_ = "https://www.binance.com/api/v3/ticker/24hr";
    interval_ = std::chrono::seconds(2);
    work_queue_ = std::make_unique<WorkQueue<std::string>>();
    start();

    initialized_ = true;
    return 0;
  }
  return -1;
}

void SimpleBinanceFetcher::exec(std::shared_ptr<Context> ctx) {
  ctx->binance_data_.json_content_ = json::parse(work_queue_->pop());
  std::cout << ctx->binance_data_.json_content_[0] << std::endl;
}

void SimpleBinanceFetcher::start() {
  fetch_thread_ = std::make_unique<std::thread>([&] {
    while (!stop_) {
      cpr::Response r = cpr::Get(cpr::Url(api_));
      work_queue_->push(r.text);
      std::this_thread::sleep_for(interval_);
    }
  });
}
}  // namespace burglar