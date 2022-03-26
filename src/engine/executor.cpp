#include "engine/executor.h"

namespace smuggler {

template<typename T>
Executor<T>::Executor(boost::property_tree::ptree& conf) {
    for (auto it = conf.begin(), it!=conf.end();it++) {
        auto module_name = it->second.get_value<std::string>();
        T* module_e = getNewInstance<T>(module_name);
        taskflow_.push_back(module_e); 
    }
    ctx_ = make_shared<Context>(); 
}

template<typename T>
Executor<T>::~Executor() {
    for(auto& it:taskflow_)
        delete it;
}

template<typename T>
void Executor<T>::run() {
    for(auto& md:taskflow_) {
        md->exec(ctx_);
    }
}

}