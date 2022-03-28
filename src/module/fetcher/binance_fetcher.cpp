#include "module/fetcher/binance_fetcher.h"

namespace smuggler {

BinanceFetcher::BinanceFetcher() { std::cout << "BinanceFetcher()" << std::endl; }

BinanceFetcher::~BinanceFetcher() { std::cout << "~BinanceFetcher() \n"; }

void BinanceFetcher::exec(std::shared_ptr<Context> ctx) { std::cout << "exec BinanceFetcher \n"; }
}  // namespace smuggler