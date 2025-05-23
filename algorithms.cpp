//
// Created by Milla on 20/05/2025.
//

#include "algorithms.h"

#include <iostream>
#include <fstream>
#include <set>
#include <sstream>
#include <vector>

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
    //create input and output files, or clean them if they already exist
    std::ofstream input("script_files/input.txt");
    std::ofstream output("script_files/output.txt");

    //add values to the input file

    //1 - number of items
    input << n << std::endl;
    //2 - capacity
    input << maxWeight << std::endl;
    //3 - weights
    for (int i = 0; i < n; i++) input << weights[i] << ' ';
    input << std::endl;
    //4 - values
    for (int i = 0; i < n; i++) input << values[i] << ' ';
    input << std::endl;

    //run python script

    int ret = system("\".venv\\Scripts\\python.exe\" ilp_solver.py script_files/input.txt script_files/output.txt");
    if (ret != 0) {
        std::cerr << "ilp_solver.py failed" << std::endl;
        return -1;
    }

    //read output

    std::ifstream infile("script_files/output.txt");
    int totalValue, totalWeight;
    std::string line;

    std::getline(infile, line);
    totalValue = stoi(line);

    std::getline(infile, line);
    totalWeight = stoi(line);

    std::getline(infile, line);
    std::istringstream iss(line);
    std::set<int> selectedIndices;
    int index;
    while (iss >> index) {
        selectedIndices.insert(index);
    }

    infile.close();

    for (int i = 0; i < n; i++) {
        if (selectedIndices.contains(i)) usedItems[i] = true;
    }


    input.close();
    output.close();
    return totalValue;
}

unsigned int Algorithms::dynamic(unsigned int values[], unsigned int weights[], unsigned int n, unsigned int maxWeight, bool usedItems[]) {
    unsigned int maxValue[n][maxWeight+1];
    for (int i = 0; i < n; i++) {
        for (int k = 0; k < maxWeight+1; k++) {
            maxValue[i][k] = 0;
        }
    }

    int value1, value2; //value of sack on H1, value of sack on H2
    for (int i = 0; i < n; i++) {
        for (int k = 1; k < maxWeight+1; k++) {
            //h1, dont put item
            if (i > 0) value1 = maxValue[i-1][k];
            else value1 = 0;

            //h2, put item
            if (i > 0) {
                if (k >= weights[i]) value2 = maxValue[i-1][k-weights[i]] + values[i];
                else value2 = maxValue[i-1][k];
            }
            else {
                if (k >= weights[i]) value2 = values[i];
                else value2 = 0;
            }

            if (value1 > value2) maxValue[i][k] = value1;
            else maxValue[i][k] = value2;

        }
    }

    for (int i = 0; i < n; i++) usedItems[i] = false;

    int curWeight = maxWeight;
    for (int i = n-1; i >= 1; i--) {
        if (maxValue[i][curWeight] != maxValue[i-1][curWeight]) {
            usedItems[i] = true;
            curWeight -= weights[i];
            if (curWeight <= 0) break;
        }
    }
    if (curWeight >= weights[0]) {
        usedItems[0] = true;
    }

    return maxValue[n-1][maxWeight];
}