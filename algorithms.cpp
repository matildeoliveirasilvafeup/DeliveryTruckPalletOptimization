//
// Created by Milla on 20/05/2025.
//

#include "algorithms.h"

unsigned int Algorithms::brute_force(unsigned int values[], unsigned int weights[], unsigned int n, unsigned int maxWeight, bool usedItems[]) {
    bool curCandidate[n];
    for (int i = 0; i < n; i++) {
        curCandidate[i] = false;
    }
    int maxValue = 0;
    while (true) {
        int curValue = 0;
        int curWeight = 0;
        for (int k = 0; k < n; k++) {
            curValue += (unsigned int) curCandidate[k] * values[k];
            curWeight += (unsigned int) curCandidate[k] * weights[k];
        }
        if (curWeight <= maxWeight) {
            if (curValue > maxValue) {
                maxValue = curValue;
                for (int k = 0; k < n; k++) {
                    usedItems[k] = curCandidate[k];
                };
            }
        }

        int v = 0;
        while (curCandidate[v]) {
            v++;
            if (v >= n) break;
        }
        if (v == n) break;
        curCandidate[v] = true;
        for (int m = 0; m < v; m++) curCandidate[m] = false;
    }
    return maxValue;
}

unsigned int Algorithms::back_tracking(unsigned int values[], unsigned int weights[], unsigned int n, unsigned int maxWeight, bool usedItems[]) {
    unsigned int maxValue = 0;
    unsigned int curIndex = 0; //identifies the current lv on the tree
    bool curItem[n];
    for (int i = 0; i < n; i++) {
        curItem[i] = false;
        usedItems[i] = false;
    }
    back_tracking_rec(values, weights, n, curIndex, maxWeight, 0, curItem, maxValue, usedItems);

    return maxValue;
}

void Algorithms::back_tracking_rec(unsigned int values[], unsigned int weights[], unsigned int n, unsigned int curIndex, unsigned int maxWeight, unsigned int curValue, bool curItems[], unsigned int& maxValue, bool usedItems[]) {
    //leaf node
    if (curIndex == n) {
        if (curValue > maxValue) {
            maxValue = curValue;
            for (int i = 0; i < n; i++) usedItems[i] = curItems[i];
        }
    }
    else {
        //option 1 - include node
        if (weights[curIndex] <= maxWeight) {
            curItems[curIndex] = true;
            back_tracking_rec(values, weights, n, curIndex+1, maxWeight - weights[curIndex], curValue + values[curIndex], curItems, maxValue, usedItems);
            curItems[curIndex] = false;
        }
        //option 2 - don't include
        back_tracking_rec(values, weights, n, curIndex + 1, maxWeight, curValue, curItems, maxValue, usedItems);
    }
}

unsigned int Algorithms::ilp(unsigned int values[], unsigned int weights[], unsigned int n, unsigned int maxWeight, bool usedItems[]) {
    return -1;
}