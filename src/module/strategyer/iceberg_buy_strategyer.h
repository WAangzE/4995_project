#include <chrono>
#include <utility>

#include "module/strategyer/basic_strategyer.h"
#include "utils/work_queue.h"

namespace burglar {
class IcebergBuyStrategyer : public BasicStrategyer {
 public:
  void exec(std::shared_ptr<Context> ctx) override;


};
}  // namespace burglar