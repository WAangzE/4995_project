#pragma once
#include <chrono>
#include <iostream>
#include <random>
#include <thread>

namespace strategyer_utils {
void dummy();

double getAmount(double currentOwn, double currentPrice, double averagePrice);

double getBuyPrice(double currentOwn, double currentPrice, double averagePrice);

double getSellPrice(double currentOwn, double currentPrice, double averagePrice);

void fake_sleep();

}  // namespace strategyer_utils
