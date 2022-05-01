# Burglar
## Introduction
Our project - burglar is a flexible and easy-to-use quantitative trading software framework. It's currently designed to deal with all cypto currency market. With this framework, users can easily configure which market or exchange they wish to use, what product they wish to trade and which strategies they are going to use all in a single simple json file.

The framework is designed to be highly modular. The framework is divided into 4 stages, namely Fetcher, Filter, Strategyer and Tailer. Their function is shown below: 
- Fetcher: This module is used to fetch information from the market, like the price of target crypto currency, the price change within 24 hours. After retrieve the information, it will fill up the fields in a context struct of our framework, which is used to transfer information between different modules.
- Filter: After get all the fields of information from the fetcher module, the filter part will do some data cleaning. Using certain rules to get the correct \& required fields.
- Strategyer: With the filtered information, we perform the quantized algorithm in this module and output the quoted price and volume of trade. We may apply different strategies on the product, so for this module, we can execute several strategy modules in parallel.
- Tailer: This module is the finishing module of the framework, it will output our final trading action and connect into the market to perform the action. Also, since we may use different strategies and get different results, this module will merge their result using a MapReduce-like method.

These modules are a highly abstraction of the executing procedure and different implementation of 4 stages can be easily assembled together. We also allow users to easily implement their own module and plugin to our framework.

Another highlight of our framework is its parallelism. To utilize this high performance feature. Users will only need to specify the dependencies inside the json file and the framework will automatically execute these modules in parallel.

## Installation

Our framework is based on C++ 20 and built with CMAKE. To install the current release, you will first need to install a few dependencies as follows:
```shell
sudo apt update
sudo apt install cmake libgflags-dev libgtest-dev libboost-all-dev
```
Basically these dependencies are for the boost and gflags library.

## Quick Start
We add a build script for the project under the source directory, run:
```shell
./build.sh
```

Then enter the build directory and run the output object:
```shell
./burglar
```

We use a single json file to allow users easily change their configurations. The file is inside `conf/`. An example is shown below:
```json
    {
        "name": "burglar_00001",
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
                    "strategy":["IcebergBuyStrategyer",
                                "BillionaireStrategyer"],
                    "tailer":["SimplePriceTailer"]
                },
                "thread_pool_num": 20
            }
        }
    }
```

Name is a field to distinguish different configurations. Flow is the corresponding target modules users select. In this case, users use `SimpleBinanceFetcher` to retrieve price from market, `SimplePriceFilter` to filter the retrieved data and then perform `IcebergBuyStrategyer` and `BillionaireStrategyer` to calculate a reasonable buying action and finally use `SimplePriceTailer` to merge the result of two strategies and write the output.

So for users, as more modules to be developed, they can change their combination in the flow field, use different fetchers, filters and strategies to flexibly produce a different trading model.

Dependency is field where we execute the parallelism. For each stage, you can define multiple modules and the framework will wrap each modules in to a job and submit to a thread pool, allowing them to executed concurrently. After modules of the same stage finish, next stage will begin to execute. 

`thread_pool_num` is the number for the concurrent threads, we suggest remain this unchanged.


## Build Your Own Modules

Except for using our existing modules, our framework allows a good modularity by letting users easily build their own module and insert into our framework. For example, if you wish to design your own strategy, implement a target class inside `src/module/strategyer/` and inherit the base class as follows:
```C++
class BillionaireStrategyer : public BasicStrategyer {
public:
  ...
  void exec(std::shared_ptr<Context> ctx) override;
  int init(const boost::property_tree::ptree& p) override;
}
```

At the very top of the `BasicStrategyer` is our reflector object, which will transfer the string you write in json into a real module class. After implementing the class you need to register it in the `src/register.h` like follows:
```C++
#include "module/strategyer/billionaire_strategyer.h"
REFLECT(BillionaireStrategyer);
```
Then you are free to configure your own module strategy inside the json file and make them part of your execution model. With this design, we give great flexibility to users implement their own service.

## Test Your Module

We utilize Google Test Framework to do functional test for your own modules, the test directory is under `test/module/`. You will be able to implement your own test part here. For instance, to test the `IcebergStrategyer`
```C++
TEST(IcebergStrategyer, basic) {
  try {
    burglar::IcebergBuyStrategyer strategyer{};
    auto ctx = std::make_shared<burglar::Context>();
    // fill up some of the context fields
    EXPECT_EQ(0, strategyer.getNumOfPrice());
    EXPECT_EQ(0, strategyer.getAveragePrice());
    // keep executing the module to see the result
    for (int i = 0; i < numOfPrice; i++) {
      double newPrice{};
      if (i < numOfPrice / 2) {
        newPrice = averagePrice + i * 0.01;
      } else {
        newPrice = averagePrice - i * 0.01;
      }
      strategyer.updateWithNewPrice(newPrice);
      ctx->binance_data_.last_price_ = newPrice;
      strategyer.exec(ctx);
    }

  } catch (std::exception& e) {
    std::cout << e.what() << std::endl;
  }
}
```
In the example, we first build a context and fill up some fields inside the context. Then we pass the context to the strategyer to keep performing `exec()` functions to test if the result is desired.

## Feedback

Any suggestion or feedback on this framework is welcomed, please feel free to submit issue.
