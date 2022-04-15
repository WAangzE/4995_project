#include "interface/burglar_service_handler.h"

#include "engine/executor.h"
#include "module/module.h"
#include "utils/reflector.h"

namespace burglar {

SmugglerServiceHandler::SmugglerServiceHandler(boost::property_tree::ptree& conf) : conf_(conf) {}

int SmugglerServiceHandler::serve() {
  auto task_conf = conf_.get_child("interface").get_child("smuggler").get_child("flow");
  exec_ = std::make_shared<Executor<ServiceModule>>(task_conf);
  while (true) {
    exec_->run();
    sleep(5);
  }
  return -1;
}

}  // namespace smuggler