#include <chrono>
#include <iostream>
#include <fstream>
#include "algorithms_runner.h"
#include "algorithms.h"

// Utility function to save results to a CSV file
void saveResultToCSV(const std::string& filename,
                     const std::string& dataset,
                     const std::string& algorithm,
                     double time_sec,
                     unsigned int total_profit,
                     unsigned int total_weight,
                     const std::vector<int>& selected_items) {

    std::ofstream file(filename, std::ios::app);
    if (!file.is_open()) {
        std::cerr << "Error: Unable to open CSV file for writing." << std::endl;
        return;
    }
    file << dataset << "," << algorithm << "," << (time_sec * 1000)
         << "," << total_profit << "," << total_weight << ",";
    for (size_t i = 0; i < selected_items.size(); ++i) {
        file << selected_items[i];
        if (i + 1 < selected_items.size()) file << " ";
    }
    file << "\n";
    file.close();
}

void runAlgorithm(const std::string& nome_algoritmo,
                  std::vector<Pallet>& pallets,
                  int capacity,
                  const std::string& dataset,
                  const std::string& csvFilename) {

    unsigned int n = pallets.size();
    unsigned int values[n];
    unsigned int weights[n];
    bool usedItems[n];
    for (unsigned i = 0; i < n; i++) {
        values[i]  = pallets[i].profit;
        weights[i] = pallets[i].weight;
        usedItems[i] = false;
    }

    unsigned int maxProfit = 0;
    std::chrono::duration<double> duration;

    if (nome_algoritmo == "brute_force") {
        auto start = std::chrono::high_resolution_clock::now();
        maxProfit = Algorithms::brute_force(values, weights, n, capacity, usedItems);
        auto end   = std::chrono::high_resolution_clock::now();
        duration   = end - start;
        std::cout << "\n[Brute Force] Execution time: " << duration.count() << " seconds\n";

    } else if (nome_algoritmo == "dynamic") {
        auto start = std::chrono::high_resolution_clock::now();
        maxProfit = Algorithms::dynamic(values, weights, n, capacity, usedItems);
        auto end   = std::chrono::high_resolution_clock::now();
        duration   = end - start;
        std::cout << "\n[Dynamic Programming] Execution time: " << duration.count() << " seconds\n";

    } else if (nome_algoritmo == "greedy") {
        auto start = std::chrono::high_resolution_clock::now();
        maxProfit = Algorithms::greedy(values, weights, n, capacity, usedItems);
        auto end   = std::chrono::high_resolution_clock::now();
        duration   = end - start;
        std::cout << "\n[Greedy] Execution time: " << duration.count() << " seconds\n";

    } else if (nome_algoritmo == "ilp") {
        auto start = std::chrono::high_resolution_clock::now();
        maxProfit = Algorithms::ilp(values, weights, n, capacity, usedItems);
        auto end   = std::chrono::high_resolution_clock::now();
        duration   = end - start;
        std::cout << "\n[ILP] Execution time: " << duration.count() << " seconds\n";

    } else if (nome_algoritmo == "back_tracking") {
        auto start = std::chrono::high_resolution_clock::now();
        maxProfit = Algorithms::back_tracking(values, weights, n, capacity, usedItems);
        auto end   = std::chrono::high_resolution_clock::now();
        duration   = end - start;
        std::cout << "\n[Back Tracking] Execution time: " << duration.count() << " seconds\n";

    } else {
        std::cerr << "Unknown algorithm: " << nome_algoritmo << std::endl;
        return;
    }

    std::cout << "[Total Profit]: " << maxProfit << std::endl;

    std::vector<int> selected;
    unsigned int totalWeight = 0;
    for (unsigned i = 0; i < n; i++) {
        if (usedItems[i]) {
            selected.push_back(pallets[i].id);
            totalWeight += weights[i];
        }
    }
    std::cout << "Selected Pallet IDs: ";
    for (int id : selected) std::cout << id << " ";
    std::cout << std::endl;

    // Mapeia nome_algoritmo -> etiqueta
    std::string algorithmLabel;
    if      (nome_algoritmo == "brute_force") algorithmLabel = "Brute-force";
    else if (nome_algoritmo == "dynamic")     algorithmLabel = "Dynamic Programming";
    else if (nome_algoritmo == "greedy")      algorithmLabel = "Greedy";
    else if (nome_algoritmo == "ilp")         algorithmLabel = "ILP";
    else if (nome_algoritmo == "back_tracking") algorithmLabel = "Back Tracking";
    saveResultToCSV(csvFilename, dataset, algorithmLabel, duration.count(), maxProfit, totalWeight, selected);
}
