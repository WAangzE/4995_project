#pragma once
#include <memory>

#include "base/context/context.h"
#include "utils/reflector.h"

namespace smuggler {

class ServiceModule : public ReflectObject {
 public:
  ServiceModule();
  virtual ~ServiceModule();
  virtual void exec(std::shared_ptr<Context> ctx);
};

}  // namespace smuggler