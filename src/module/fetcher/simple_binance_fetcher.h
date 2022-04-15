#include <chrono>
#include <utility>

#include "binance_fetcher.h"
#include "work_queue.h"

namespace burglar {
class SimpleBinanceFetcher : public BinanceFetcher {
 public:
  SimpleBinanceFetcher() = delete;
  explicit SimpleBinanceFetcher(std::string api)
      : BinanceFetcher(std::move(api)), interval_(std::chrono::seconds(5)), stop_(false) {
    work_queue_ = std::make_unique<WorkQueue<std::string>>();
    start();
  }

  void exec(std::shared_ptr<Context> ctx) override;

  ~SimpleBinanceFetcher() override {
    stop_ = true;
    fetch_thread_->join();
  }

 private:
  std::unique_ptr<WorkQueue<std::string>> work_queue_;
  std::chrono::seconds interval_;
  std::unique_ptr<std::thread> fetch_thread_;
  bool stop_;

  void start();
};
}  // namespace burglar
