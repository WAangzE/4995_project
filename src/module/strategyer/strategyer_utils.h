#pragma once
#include <random>
#include <iostream>

namespace strategyer_utils {
void dummy();

double getAmount(double currentOwn, double currentPrice, double averagePrice);

double getBuyPrice(double currentOwn, double currentPrice, double averagePrice);

double getSellPrice(double currentOwn, double currentPrice, double averagePrice);
}  // namespace strategyer_utils
