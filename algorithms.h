//
// Created by Milla on 20/05/2025.
//

#ifndef ALGORITHMS_H
#define ALGORITHMS_H

#include <utility>
#include <vector>
#include "csvparsing.h"

class Algorithms {
public:
    ///
    /// @brief Brute-Force algorithm to maximize pallet profit (O(2^n))
    static unsigned int brute_force(unsigned int values[], unsigned int weights[], unsigned int n, unsigned int maxWeight, bool usedItems[]);

    ///
    /// @brief Backtracking algorithm to maximize pallet profit (O(2^n))
    static unsigned int back_tracking(unsigned int values[], unsigned int weights[], unsigned int n, unsigned int maxWeight, bool usedItems[]);

    ///
    /// @brief Integer Linear Programming algorithm to maximize pallet profit
    static unsigned int ilp(unsigned int values[], unsigned int weights[], unsigned int n, unsigned int maxWeight, bool usedItems[]);

    ///
    /// @brief Dynamic Programming algorithm to maximize pallet profit (O(n·W))
    static unsigned int dynamic(unsigned int values[], unsigned int weights[], unsigned int n, unsigned int maxWeight, bool usedItems[]);

    ///
    /// @brief Greedy heuristic for 0/1 Knapsack (O(n log n))
    /// @details Orders pallets by profit/weight ratio and packs while capacity allows
    static unsigned int greedy(unsigned int values[], unsigned int weights[], unsigned int n, unsigned int maxWeight, bool usedItems[]);

private:
    static void back_tracking_rec(unsigned int values[], unsigned int weights[], unsigned int n,
                                  unsigned int curIndex, unsigned int maxWeight,
                                  unsigned int curValue, bool curItems[],
                                  unsigned int& maxValue, bool usedItems[]);
};

#endif // ALGORITHMS_H
