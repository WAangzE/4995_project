#pragma once
#include <memory>

#include "base/context/context.h"
#include "utils/reflector.h"

namespace burglar {

class ServiceModule : public ReflectObject {
 public:
  ServiceModule();
  virtual ~ServiceModule();
  virtual void exec(std::shared_ptr<Context> ctx) = 0;
  virtual int init(const boost::property_tree::ptree&) = 0;

 protected:
  boost::property_tree::ptree conf_;
  bool initialized_ = false;
};

}  // namespace burglar