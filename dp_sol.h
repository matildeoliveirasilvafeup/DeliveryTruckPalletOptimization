#ifndef DP_SOL_H
#define DP_SOL_H

#include <vector>
#include "csvparsing.h"

// Returns the maximum total profit and the selected pallet IDs
std::pair<int, std::vector<int>> solveWithDP(std::vector<Pallet>& pallets, int capacity);

#endif
