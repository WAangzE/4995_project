#include "interface/burglar_service_handler.h"

#include <chrono>

#include "engine/executor.h"
#include "module/module.h"

namespace burglar {

BurglarServiceHandler::BurglarServiceHandler(boost::property_tree::ptree& conf) : conf_(conf) {}

int BurglarServiceHandler::serve() {
  auto task_conf = conf_.get_child("interface").get_child("burglar");
  exec_ = std::make_shared<Executor<ServiceModule>>(task_conf);

  uint round = 0;
  while (true) {
    round++;
    std::cout << "------ burglar starts round " << round << std::endl;
    auto start = std::chrono::system_clock::now();
    exec_->run();
    auto elapsed = std::chrono::system_clock::now() - start;
    std::cout << "a complete run takes "
              << std::chrono::duration_cast<std::chrono::milliseconds>(elapsed).count() << " ms\n" << std::endl;
    sleep(5);
  }
  return -1;
}

}  // namespace burglar