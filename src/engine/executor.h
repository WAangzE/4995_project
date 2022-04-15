#pragma once
#include <boost/property_tree/ptree.hpp>

#include "base/context/context.h"
#include "module/module.h"

namespace burglar {
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
}  // namespace burglar

#include "engine/executor.cpp"