#pragma once
#include <boost/property_tree/ptree.hpp>
#include <unordered_map>

#include "base/context/context.h"
#include "module/module.h"
#include "utils/thread_pool_manager.h"

namespace burglar {
// to be develop: use concept
template <typename T>
class Executor {
 public:
  Executor(boost::property_tree::ptree& conf);
  ~Executor();
  void dag_builder(boost::property_tree::ptree& conf);
  void run();

 private:
  std::unordered_map<std::string, T*> taskflow_;
  std::shared_ptr<Context> ctx_;
  std::shared_ptr<ThreadPoolManager> thread_pool_;
  std::vector<std::vector<std::string>> g_;
  // std::unordered_map<std::string, std::unordered_set<std::string>> g_;
  // std::unordered_map<std::string, int> cur_pre_;
};
}  // namespace burglar

#include "engine/executor.cpp"