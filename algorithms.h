//
// Created by Milla on 20/05/2025.
//

#ifndef ALGORITHMS_H
#define ALGORITHMS_H
class Algorithms {
public:
    static unsigned int brute_force(unsigned int values[], unsigned int weights[], unsigned int n, unsigned int maxWeight, bool usedItems[]);
    static unsigned int back_tracking(unsigned int values[], unsigned int weights[], unsigned int n, unsigned int maxWeight, bool usedItems[]);
    static unsigned int ilp(unsigned int values[], unsigned int weights[], unsigned int n, unsigned int maxWeight, bool usedItems[]);
private:
    static void back_tracking_rec(unsigned int values[], unsigned int weights[], unsigned int n, unsigned int curIndex, unsigned int maxWeight, unsigned int curValue, bool curItems[], unsigned int& maxValue, bool usedItems[]);
};
#endif //ALGORITHMS_H
