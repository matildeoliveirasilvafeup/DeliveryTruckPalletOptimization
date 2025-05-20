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
    static unsigned int brute_force(unsigned int values[], unsigned int weights[], unsigned int n, unsigned int maxWeight, bool usedItems[]);
    static unsigned int back_tracking(unsigned int values[], unsigned int weights[], unsigned int n, unsigned int maxWeight, bool usedItems[]);
    static unsigned int ilp(unsigned int values[], unsigned int weights[], unsigned int n, unsigned int maxWeight, bool usedItems[]);
    static unsigned int dynamic(unsigned int values[], unsigned int weights[], unsigned int n, unsigned int maxWeight, bool usedItems[]);
private:
    static void back_tracking_rec(unsigned int values[], unsigned int weights[], unsigned int n, unsigned int curIndex, unsigned int maxWeight, unsigned int curValue, bool curItems[], unsigned int& maxValue, bool usedItems[]);
	static std::pair<int, std::vector<int>> solveWithDP(std::vector<Pallet>& pallets, int capacity); //added by Matilde
};

#endif //ALGORITHMS_H
