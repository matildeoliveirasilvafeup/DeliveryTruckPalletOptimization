//
// Created by Milla on 20/05/2025.
//
#include <utility>
#include <vector>
#include "csvparsing.h"

#ifndef ALGORITHMS_H
#define ALGORITHMS_H
class Algorithms {
public:
    ///
    /// @param values unsigned int[] - an array with the value of each pallet
    /// @param weights unsigned int[] - an array with the weight of each pallet
    /// @param n unsigned int - number of pallets
    /// @param maxWeight unsigned int - maximum weight the delivery truck can carry
    /// @param usedItems bool[] - an array indicating whether a pallet is used in the solution (true) or not (false)
    /// @return unsigned int - the total value achieved with the combination of pallets the algorithm chose
    /// @brief Brute-Force algorithm to maximize pallet profit
    /// @details Finds out the best combination of pallets to maximize profit, in a brute-force manner (testing every combination possible)
    /// @note O(2^n)
    static unsigned int brute_force(unsigned int values[], unsigned int weights[], unsigned int n, unsigned int maxWeight, bool usedItems[]);

    ///
    /// @param values unsigned int[] - an array with the value of each pallet
    /// @param weights unsigned int[] - an array with the weight of each pallet
    /// @param n unsigned int - number of pallets
    /// @param maxWeight unsigned int - maximum weight the delivery truck can carry
    /// @param usedItems bool[] - an array indicating whether a pallet is used in the solution (true) or not (false)
    /// @return unsigned int - the total value achieved with the combination of pallets the algorithm chose
    /// @brief Backtracking algorith to maximize pallet profit
    /// @details Finds out the best combination of pallets to maximize profit, using a backtracking approach with a decision tree
    /// @note O(2^n)
    static unsigned int back_tracking(unsigned int values[], unsigned int weights[], unsigned int n, unsigned int maxWeight, bool usedItems[]);

    ///
    /// @param values unsigned int[] - an array with the value of each pallet
    /// @param weights unsigned int[] - an array with the weight of each pallet
    /// @param n unsigned int - number of pallets
    /// @param maxWeight unsigned int - maximum weight the delivery truck can carry
    /// @param usedItems bool[] - an array indicating whether a pallet is used in the solution (true) or not (false)
    /// @return unsigned int - the total value achieved with the combination of pallets the algorithm chose
    /// @brief Integer Linear Programming algorithm to maximize pallet profit
    /// @details Finds out the best combination of pallets to maximize profit, sending the input to an ILP python script and reading its output
    /// @note O(2^n) worst case, but practically much faster due to optimization techniques
    static unsigned int ilp(unsigned int values[], unsigned int weights[], unsigned int n, unsigned int maxWeight, bool usedItems[]);

    ///
    /// @param values unsigned int[] - an array with the value of each pallet
    /// @param weights unsigned int[] - an array with the weight of each pallet
    /// @param n unsigned int - number of pallets
    /// @param maxWeight unsigned int - maximum weight the delivery truck can carry
    /// @param usedItems bool[] - an array indicating whether a pallet is used in the solution (true) or not (false)
    /// @return unsigned int - the total value achieved with the combination of pallets the algorithm chose
    /// @brief Dynamic Programming algorithm to maximize pallet profit
    /// @details Finds out the best combination of pallets to maximize profit, using a table to avoid recomputing subproblems
    /// @note O(nW)
    static unsigned int dynamic(unsigned int values[], unsigned int weights[], unsigned int n, unsigned int maxWeight, bool usedItems[]);
private:
    ///
    /// @param values unsigned int[] - an array with the value of each pallet
    /// @param weights unsigned int[] - an array with the weight of each pallet
    /// @param n unsigned int - number of pallets
    /// @param curIndex unsigned int - the current index that's being explored in the decision tree
    /// @param maxWeight unsigned int - maximum weight the delivery truck can carry
    /// @param curValue unsigned int - the total value of the pallets in the current decision state
    /// @param curItems bool[] - an array indicating which pallets are being considered in the current decision state
    /// @param maxValue unsigned int - the overall maximum value that the algorithm found in the decision states it has explored
    /// @param usedItems bool[] - an array indicating whether a pallet is used in the solution (true) or not (false)
    /// @brief Recursive helper function for the backtracking algorithm
    /// @details Evaluates two decisions at any given decision state - to include the pallet at the current index, or not
    /// @note O(2^n)
    static void back_tracking_rec(unsigned int values[], unsigned int weights[], unsigned int n, unsigned int curIndex, unsigned int maxWeight, unsigned int curValue, bool curItems[], unsigned int& maxValue, bool usedItems[]);
};

#endif //ALGORITHMS_H
