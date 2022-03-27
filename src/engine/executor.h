#pragma once
#include "base/context/context.h"
#include <boost/property_tree/ptree.hpp>

namespace smuggler {
// to be develop: use concept
template <typename T>
class Executor {
 public:
  Executor(boost::property_tree::ptree& conf);
  ~Executor();
  void run();

 private:
  std::vector<T*> taskflow_;
  std::shared_ptr<Context> ctx_;
};
template <typename T>
Executor<T>::Executor(boost::property_tree::ptree& conf) {}
}  // namespace smuggler