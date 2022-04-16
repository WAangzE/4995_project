#pragma once

namespace burglar {

struct Context {
 public:
  Context() {}
  void setBalance(int x) {currentBalance = x;}
  int getBalance() const { return currentBalance;}

 private:
  int currentBalance;
};

}  // namespace burglar