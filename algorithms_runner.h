#ifndef ALGORITHM_RUNNER_H
#define ALGORITHM_RUNNER_H

#include <string>
#include <vector>
#include "csvparsing.h"


void runAlgorithm(const std::string& algoName, std::vector<Pallet>& pallets, int capacity);

#endif
