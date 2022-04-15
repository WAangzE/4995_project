#include "simple_binance_fetcher.h"
#include "cpr/cpr.h"

namespace burglar {

void SimpleBinanceFetcher::exec(std::shared_ptr<Context> ctx) {
  std::cout << "size: " << work_queue_->size() << std::endl;
  std::cout << work_queue_->pop() << std::endl;
}

void SimpleBinanceFetcher::start() {
  fetch_thread_ = std::make_unique<std::thread>([&]{
    std::mutex mutex;
    std::unique_lock<std::mutex> sleep_lock(mutex);
    std::condition_variable sleep_cond;

    while (!stop_) {
      cpr::Response r = cpr::Get(cpr::Url(api_));
      work_queue_->push(r.text);
//      std::cout << r.text << std::endl;
      std::this_thread::sleep_for(interval_);
    }
  });
}
}