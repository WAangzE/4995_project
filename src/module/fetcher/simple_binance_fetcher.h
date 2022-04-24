#include <chrono>
#include <utility>

#include "module/fetcher/binance_fetcher.h"
#include "utils/work_queue.h"

namespace burglar {
class SimpleBinanceFetcher : public BinanceFetcher {
 public:
  SimpleBinanceFetcher() = default;

  int init(const boost::property_tree::ptree&) override;
  void exec(std::shared_ptr<Context> ctx) override;

  ~SimpleBinanceFetcher() override {
    stop_ = true;
    fetch_thread_->join();
  }

 private:
  std::unique_ptr<WorkQueue<std::string>> work_queue_;
  std::chrono::seconds interval_{};
  std::unique_ptr<std::thread> fetch_thread_;
  bool stop_ = false;

  void start();
};
}  // namespace burglar
