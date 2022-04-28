#pragma once
#include <boost/property_tree/ptree.hpp>
#include <chrono>
#include <sstream>
#include <string>

#include "utils/work_queue.h"
#include "third_party/json.hpp"

namespace burglar {

struct Action {
  Action() : op_(Op::sell), unit(0.), price(0.) {}

  enum class Op { sell, buy };
  double unit;
  double price;
  Op op_;
};

struct Context {
  Context() : strategy_actions_(std::make_shared<WorkQueue<Action>>()) {}
  explicit Context(const boost::property_tree::ptree& conf)
      : conf_(conf), strategy_actions_(std::make_shared<WorkQueue<Action>>()) {}

  struct UserState {
    double balance_{};

    void reset() { balance_ = 0.0; }

    [[nodiscard]] std::string dump() const {
      std::stringstream ss;
      ss << "UserData:\n"
         << "  balance: " << balance_ << "\n";
      return ss.str();
    }
  } user_state_;

  struct BinanceData {
    decltype(std::chrono::system_clock::now()) timestamp_;
    double last_price_{};
    double bid_prices_{};
    double high_price_{};
    double low_price_{};
    uint count_{};
    nlohmann::json json_content_{};

    void reset() {
      last_price_ = bid_prices_ = high_price_ = low_price_ = 0.0;
      count_ = 0;
      json_content_ = {};
    }

    [[nodiscard]] std::string dump() const {
      std::stringstream ss;
      ss << "BinanceData:\n"
         << "  timestamp: " << timestamp_.time_since_epoch().count() << "\n"
         << "  last_price: " << last_price_ << "\n"
         << "  bid_price: " << bid_prices_ << "\n"
         << "  high_price: " << high_price_ << "\n"
         << "  low_price: " << low_price_ << "\n"
         << "  count: " << count_ << "\n";
      return ss.str();
    }
  } binance_data_;

  std::shared_ptr<WorkQueue<Action>> strategy_actions_;
  Action decision_;

  [[nodiscard]] std::string dump() const {
    std::stringstream ss;
    ss << user_state_.dump() << binance_data_.dump();
    return ss.str();
  }

 private:
  boost::property_tree::ptree conf_;
};

}  // namespace burglar