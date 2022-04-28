#pragma once
#include <iostream>
#include <random>
#include <chrono>
#include <thread>

namespace strategyer_utils {

double getAmount(double currentOwn, double currentPrice, double averagePrice);

double getBuyPrice(double currentOwn, double currentPrice, double averagePrice);

double getSellPrice(double currentOwn, double currentPrice, double averagePrice);

void fake_sleep();

}  // namespace strategyer_utils
