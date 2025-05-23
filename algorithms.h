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
    static unsigned int brute_force(unsigned int values[], unsigned int weights[], unsigned int n, unsigned int maxWeight, bool usedItems[]);

    ///
    /// @param values unsigned int[] - an array with the value of each pallet
    /// @param weights unsigned int[] - an array with the weight of each pallet
    /// @param n unsigned int - number of pallets
    /// @param maxWeight unsigned int - maximum weight the delivery truck can carry
    /// @param usedItems bool[] - an array indicating whether a pallet is used in the solution (true) or not (false)
    /// @return unsigned int - the total value achieved with the combination of pallets the algorithm chose
    static unsigned int back_tracking(unsigned int values[], unsigned int weights[], unsigned int n, unsigned int maxWeight, bool usedItems[]);

    ///
    /// @param values unsigned int[] - an array with the value of each pallet
    /// @param weights unsigned int[] - an array with the weight of each pallet
    /// @param n unsigned int - number of pallets
    /// @param maxWeight unsigned int - maximum weight the delivery truck can carry
    /// @param usedItems bool[] - an array indicating whether a pallet is used in the solution (true) or not (false)
    /// @return unsigned int - the total value achieved with the combination of pallets the algorithm chose
    static unsigned int ilp(unsigned int values[], unsigned int weights[], unsigned int n, unsigned int maxWeight, bool usedItems[]);

    ///
    /// @param values unsigned int[] - an array with the value of each pallet
    /// @param weights unsigned int[] - an array with the weight of each pallet
    /// @param n unsigned int - number of pallets
    /// @param maxWeight unsigned int - maximum weight the delivery truck can carry
    /// @param usedItems bool[] - an array indicating whether a pallet is used in the solution (true) or not (false)
    /// @return unsigned int - the total value achieved with the combination of pallets the algorithm chose
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
    static void back_tracking_rec(unsigned int values[], unsigned int weights[], unsigned int n, unsigned int curIndex, unsigned int maxWeight, unsigned int curValue, bool curItems[], unsigned int& maxValue, bool usedItems[]);
};

#endif //ALGORITHMS_H
