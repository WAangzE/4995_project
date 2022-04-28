#include <gflags/gflags.h>

#include <boost/property_tree/json_parser.hpp>
#include <boost/property_tree/ptree.hpp>
#include <chrono>
#include <iostream>
#include <sstream>

#include "gtest/gtest.h"
#include "interface/burglar_service_handler.h"
#include "register.h"

using namespace burglar;

std::string config_json = R"({
"name": "smuggler_00001",
"interface": {
    "burglar": {
        "flow": [
            "SimpleBinanceFetcher",
            "SimplePriceFilter",
            "IcebergBuyStrategyer",
            "BillionaireStrategyer",
            "SimplePriceTailer"
        ],
        "dependency": {
            "fetcher":["SimpleBinanceFetcher"],
            "filter":["SimplePriceFilter"],
            "strategy":["IcebergBuyStrategyer","BillionaireStrategyer"],
            "tailer":["SimplePriceTailer"]
        },
        "thread_pool_num": 20,
    }
}
})";

TEST(LatencyBreakdown, fetcher) {
  boost::property_tree::ptree conf;
  std::stringstream ss;
  ss << config_json;
  boost::property_tree::read_json(ss, conf);

  try {
    auto handler = std::make_shared<BurglarServiceHandler>(conf);
    handler->serve();
  } catch (std::exception& ex) {
    std::cout << "exception thrown! reason: " << ex.what() << "\n";
    return;
  } catch (...) {
    std::cout << "exception thrown! reason: unknown. \n";
  }
}