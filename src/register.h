#include "module/fetcher/simple_binance_fetcher.h"
#include "module/filter/simple_price_filter.h"
#include "module/strategyer/billionaire_strategyer.h"
#include "module/strategyer/iceberg_buy_strategyer.h"
#include "module/tailer/simple_price_tailer.h"

namespace burglar {
REFLECT(SimpleBinanceFetcher);
REFLECT(SimplePriceFilter);
REFLECT(IcebergBuyStrategyer);
REFLECT(BillionaireStrategyer);
REFLECT(SimplePriceTailer);
}  // namespace burglar