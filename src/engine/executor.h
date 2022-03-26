#pragma once
#include "base/context/context.h"

namespace smuggler {
//to be develop: use concept
template<typename T>
class Executor{
public:
    Executor(boost::property_tree::ptree& conf);
    ~Executor();
    void run();
private:
    std::vector<T*> taskflow_;
    std::shared_pointer<Context> ctx_;

}
}