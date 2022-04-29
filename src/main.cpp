#include <gflags/gflags.h>

#include <boost/property_tree/json_parser.hpp>
#include <boost/property_tree/ptree.hpp>
#include <iostream>

#include "interface/burglar_service_handler.h"
#include "register.h"

using namespace burglar;

DEFINE_string(conf_file, "../conf/service.json", "config file");

int main(int argc, char** argv) {
  gflags::ParseCommandLineFlags(&argc, &argv, true);

  boost::property_tree::ptree conf;
  boost::property_tree::read_json(FLAGS_conf_file, conf);

  try {
    auto handler = std::make_shared<BurglarServiceHandler>(conf);
    handler->serve();
  } catch (std::exception& ex) {
    std::cout << "exception thrown! reason: " << ex.what() << "\n";
    return -1;
  } catch (...) {
    std::cout << "exception thrown! reason: unknown. \n";
  }

  //    INFO("================= main() exit =================");
  _exit(0);
}