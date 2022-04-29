#include "context.h"

namespace burglar {
std::string op_str(Action::Op op) {
  switch (op) {
  case Action::Op::sell:
    return "sell";
  case Action::Op::buy:
    return "buy";
  default:
    return "";
  }
}
}  // namespace burglar