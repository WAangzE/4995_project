#pragma once
#include <iostream>
#include <random>

namespace strategyer_utils {

double getAmount(double currentOwn, double currentPrice, double averagePrice);

double getBuyPrice(double currentOwn, double currentPrice, double averagePrice);

double getSellPrice(double currentOwn, double currentPrice, double averagePrice);
}  // namespace strategyer_utils
