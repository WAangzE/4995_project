#include "engine/executor.h"

#include <boost/property_tree/ptree.hpp>
#include <queue>
#include <unordered_map>
#include <unordered_set>

#include "module/module.h"
#include "utils/reflector.h"

namespace burglar {

template <typename T>
Executor<T>::Executor(boost::property_tree::ptree& conf) {
  ctx_ = std::make_shared<Context>(conf);
  int thread_pool_num = conf.get_child("thread_pool_num").get_value<int>();
  thread_pool_ = std::make_shared<ThreadPoolManager>(thread_pool_num);
  auto flow = conf.get_child("flow");
  for (auto it = flow.begin(); it != flow.end(); it++) {
    auto module_name = it->second.get_value<std::string>();
    T* module_e = getNewInstance<T>(module_name);
    module_e->init(conf);
    taskflow_[module_name] = module_e;
  }
  g_ = std::vector<std::vector<std::string>>(4, std::vector<std::string>());
  dag_builder(conf.get_child("dependency"));
}

template <typename T>
void Executor<T>::dag_builder(boost::property_tree::ptree& conf) {
  auto fetcher = conf.get_child("fetcher");
  auto filter = conf.get_child("filter");
  auto strategy = conf.get_child("strategy");
  auto tailer = conf.get_child("tailer");
  for (auto& it : fetcher) {
    g_[0].push_back(it.second.get_value<std::string>());
  }
  for (auto& it : filter) {
    g_[1].push_back(it.second.get_value<std::string>());
  }
  for (auto& it : strategy) {
    g_[2].push_back(it.second.get_value<std::string>());
  }
  for (auto& it : tailer) {
    g_[3].push_back(it.second.get_value<std::string>());
  }
}

template <typename T>
Executor<T>::~Executor() {
  for (auto& it : taskflow_)
    delete it.second;
}

template <typename T>
void Executor<T>::run() {
  std::unordered_set<std::future<void>*> ft;
  for (int i = 0; i < 4; i++) {
    for (auto& module_name : g_[i]) {
      taskflow_[module_name]->exec(ctx_);
    }
//    int node_num = g_[i].size();
//    for (auto& module_name : g_[i]) {
//      auto job = thread_pool_->submit([&]() { taskflow_[module_name]->exec(ctx_); });
//      ft.insert(&job);
//    }
//    for (auto& t : ft) {
//      t->wait();
//      delete t;
//    }
//    ft.clear();
  }
}

}  // namespace burglar
