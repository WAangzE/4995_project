#pragma once
#include <chrono>
#include <sstream>
#include <string>

namespace burglar {

struct Context {
  Context() = default;

  struct UserState {
    double balance_;
  } user_state_;

  struct BinanceData {
    decltype(std::chrono::system_clock::now()) timestamp_;
    double last_price_{};
    double bid_prices_{};
    double high_price_{};
    double low_price_{};
    uint count_{};
    std::string raw_content_;
  } binance_data_;

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
};

}  // namespace burglar