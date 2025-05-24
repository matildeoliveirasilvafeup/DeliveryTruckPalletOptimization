//
// Created by Milla on 20/05/2025.
//

#include "algorithms.h"

#include <iostream>
#include <fstream>
#include <set>
#include <sstream>
#include <vector>
#include <algorithm>  // std::sort

unsigned int Algorithms::brute_force(unsigned int values[], unsigned int weights[], unsigned int n, unsigned int maxWeight, bool usedItems[]) {
    bool curCandidate[n];
    for (unsigned i = 0; i < n; i++) curCandidate[i] = false;
    int maxValue = 0;
    while (true) {
        int curValue = 0, curWeight = 0;
        for (unsigned k = 0; k < n; k++) {
            curValue  += curCandidate[k] * values[k];
            curWeight += curCandidate[k] * weights[k];
        }
        if (curWeight <= maxWeight && curValue > maxValue) {
            maxValue = curValue;
            for (unsigned k = 0; k < n; k++) usedItems[k] = curCandidate[k];
        }
        unsigned v = 0;
        while (v < n && curCandidate[v]) v++;
        if (v >= n) break;
        curCandidate[v] = true;
        for (unsigned m = 0; m < v; m++) curCandidate[m] = false;
    }
    return maxValue;
}

unsigned int Algorithms::back_tracking(unsigned int values[], unsigned int weights[], unsigned int n, unsigned int maxWeight, bool usedItems[]) {
    unsigned int maxValue = 0;
    bool curItems[n];
    for (unsigned i = 0; i < n; i++) {
        curItems[i] = false;
        usedItems[i] = false;
    }
    back_tracking_rec(values, weights, n, 0, maxWeight, 0, curItems, maxValue, usedItems);
    return maxValue;
}

void Algorithms::back_tracking_rec(unsigned int values[], unsigned int weights[], unsigned int n,
                                   unsigned int curIndex, unsigned int maxWeight,
                                   unsigned int curValue, bool curItems[],
                                   unsigned int& maxValue, bool usedItems[]) {
    if (curIndex == n) {
        if (curValue > maxValue) {
            maxValue = curValue;
            for (unsigned i = 0; i < n; i++) usedItems[i] = curItems[i];
        }
        return;
    }
    // inclui
    if (weights[curIndex] <= maxWeight) {
        curItems[curIndex] = true;
        back_tracking_rec(values, weights, n, curIndex+1, maxWeight - weights[curIndex],
                          curValue + values[curIndex], curItems, maxValue, usedItems);
        curItems[curIndex] = false;
    }
    // não inclui
    back_tracking_rec(values, weights, n, curIndex+1, maxWeight,
                      curValue, curItems, maxValue, usedItems);
}

unsigned int Algorithms::ilp(unsigned int values[], unsigned int weights[], unsigned int n, unsigned int maxWeight, bool usedItems[]) {
    // input/output files
    std::ofstream input("script_files/input.txt");
    std::ofstream output("script_files/output.txt");

    // 1) número de itens
    input << n << std::endl;
    // 2) capacidade
    input << maxWeight << std::endl;
    // 3) pesos
    for (int i = 0; i < (int)n; i++) input << weights[i] << ' ';
    input << std::endl;
    // 4) valores
    for (int i = 0; i < (int)n; i++) input << values[i] << ' ';
    input << std::endl;
    input.close();

    // executa script Python
    int ret = system("python ilp_solver.py script_files/input.txt script_files/output.txt");
    if (ret != 0) {
        std::cerr << "ilp_solver.py failed" << std::endl;
        return static_cast<unsigned int>(-1);
    }

    // lê output: 1) profit  2) weight  3) lista de índices
    std::ifstream infile("script_files/output.txt");
    int totalValue = 0, totalWeight = 0;
    std::string line;

    std::getline(infile, line);
    totalValue = std::stoi(line);

    std::getline(infile, line);
    totalWeight = std::stoi(line);

    std::getline(infile, line);
    std::istringstream iss(line);

    std::set<int> sel;
    int idx;
    while (iss >> idx) {
        sel.insert(idx);
    }
    infile.close();

    // marca usados
    for (int i = 0; i < (int)n; i++) {
        usedItems[i] = (sel.count(i) > 0);
    }

    return static_cast<unsigned int>(totalValue);
}

unsigned int Algorithms::dynamic(unsigned int values[], unsigned int weights[], unsigned int n, unsigned int maxWeight, bool usedItems[]) {
    unsigned int maxValue[n][maxWeight+1];
    // inicializa
    for (unsigned i = 0; i < n; i++)
        for (unsigned w = 0; w <= maxWeight; w++)
            maxValue[i][w] = 0;

    // preenche tabela
    for (unsigned i = 0; i < n; i++) {
        for (unsigned w = 1; w <= maxWeight; w++) {
            unsigned int dont = (i > 0 ? maxValue[i-1][w] : 0);
            unsigned int take = (w >= weights[i]
                                ? ((i > 0 ? maxValue[i-1][w-weights[i]] : 0) + values[i])
                                : 0);
            maxValue[i][w] = std::max(dont, take);
        }
    }

    // reconstrói solução
    for (unsigned i = 0; i < n; i++) usedItems[i] = false;
    unsigned w = maxWeight;
    for (int i = n-1; i >= 1; i--) {
        if (maxValue[i][w] != maxValue[i-1][w]) {
            usedItems[i] = true;
            w -= weights[i];
        }
    }
    if (w >= weights[0]) usedItems[0] = true;

    return maxValue[n-1][maxWeight];
}

// ------- GREEDY HEURISTIC 0/1 KNAPSACK -------

unsigned int Algorithms::greedy(unsigned int values[], unsigned int weights[], unsigned int n, unsigned int maxWeight, bool usedItems[]) {
    // calcula razão e inicializa flags
    std::vector<std::pair<double,int>> order;
    order.reserve(n);
    for (unsigned i = 0; i < n; i++) {
        double r = double(values[i]) / double(weights[i]);
        order.emplace_back(r, i);
        usedItems[i] = false;
    }
    // ordena decrescentemente por razão
    std::sort(order.begin(), order.end(),
              [](auto &a, auto &b){ return a.first > b.first; });

    unsigned int currentW = 0, totalP = 0;
    for (auto &p : order) {
        int i = p.second;
        if (currentW + weights[i] <= maxWeight) {
            usedItems[i] = true;
            currentW   += weights[i];
            totalP     += values[i];
        }
    }
    return totalP;
}
