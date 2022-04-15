#include "engine/executor.h"

#include <module/module.h>
#include <utils/reflector.h>

#include <boost/property_tree/ptree.hpp>

namespace burglar {

template <typename T>
Executor<T>::Executor(boost::property_tree::ptree& conf) {
  ctx_ = std::make_shared<Context>();
  for (auto it = conf.begin(); it != conf.end(); it++) {
    auto module_name = it->second.get_value<std::string>();
    T* module_e = getNewInstance<T>(module_name);
    taskflow_.push_back(module_e);
  }
}

template <typename T>
Executor<T>::~Executor() {
  for (auto& it : taskflow_)
    delete it;
}

template <typename T>
void Executor<T>::run() {
  for (auto& md : taskflow_) {
    md->exec(ctx_);
  }
}

}  // namespace burglar
