#pragma once
#include <boost/property_tree/ptree.hpp>
#include <chrono>
#include <sstream>
#include <string>

#include "utils/work_queue.h"

namespace burglar {

struct Action {
  Action() : op_(Op::sell), unit(0.), price(0.) {}

  enum class Op { sell, buy };
  double unit;
  double price;
  Op op_;
};

struct Context {
  Context() = default;
  explicit Context(const boost::property_tree::ptree& conf)
      : conf_(conf), strategy_actions_(std::make_shared<WorkQueue<Action>>()) {}

  struct UserState {
    double balance_{};

    void reset() {
      balance_ = 0.0;
    }
  } user_state_;

  struct BinanceData {
    decltype(std::chrono::system_clock::now()) timestamp_;
    double last_price_{};
    double bid_prices_{};
    double high_price_{};
    double low_price_{};
    uint count_{};
    std::string raw_content_;

    void reset() {
      last_price_ = bid_prices_ = high_price_ = low_price_ = 0.0;
      count_ = 0;
      raw_content_ = "";
    }
  } binance_data_;

  std::shared_ptr<WorkQueue<Action>> strategy_actions_;
  Action decision_;

  [[nodiscard]] std::string dump() const {
    std::stringstream ss;
    ss << "UserData:\n"
       << "  balance: " << user_state_.balance_ << "\n"
       << "BinanceData:\n"
       << "  timestamp: " << binance_data_.timestamp_.time_since_epoch().count() << "\n"
       << "  last_price: " << binance_data_.last_price_ << "\n"
       << "  bid_price: " << binance_data_.bid_prices_ << "\n"
       << "  high_price: " << binance_data_.high_price_ << "\n"
       << "  low_price: " << binance_data_.low_price_ << "\n"
       << "  count: " << binance_data_.count_ << "\n";
    return ss.str();
  }

 private:
  boost::property_tree::ptree conf_;
};

}  // namespace burglar