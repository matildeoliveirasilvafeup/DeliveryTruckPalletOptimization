#ifndef ALGORITHM_RUNNER_H
#define ALGORITHM_RUNNER_H

#include <string>
#include <vector>
#include "csvparsing.h"


void runAlgorithm(const std::string& nome_algoritmo, std::vector<Pallet>& pallets, int capacity, const std::string& dataset, const std::string& csvFilename);

#endif
