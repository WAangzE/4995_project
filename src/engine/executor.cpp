#include "engine/executor.h"

#include <boost/property_tree/ptree.hpp>

namespace smuggler {



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

}  // namespace smuggler