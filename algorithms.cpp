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