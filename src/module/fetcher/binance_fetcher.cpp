#include "module/binance_fetcher.h"

namespace smuggler {
REFLECT(Allen);

BinanceFetcher::BinanceFetcher()
{
	std::cout << "BinanceFetcher() \n";
}


BinanceFetcher::~BinanceFetcher()
{
	std::cout << "~BinanceFetcher() \n";
}

void BinanceFetcher::exec(std::shared_pointer<Context> ctx)
{
	std::cout << "exec BinanceFetcher \n";
}
}