#include <chrono>
#include <iostream>
#include "algorithms_runner.h"
#include "algorithms.h"


void runAlgorithm(const std::string& algoName, std::vector<Pallet>& pallets, int capacity) {
	if (algoName == "brute_force") {
		unsigned int n = pallets.size();
		unsigned int values[n];
		unsigned int weights[n];
		bool usedItems[n];

		for (unsigned int i = 0; i < n; i++) {
			values[i] = pallets[i].profit;
			weights[i] = pallets[i].weight;
			usedItems[i] = false;
		}

		auto start = std::chrono::high_resolution_clock::now();

		unsigned int maxProfit = Algorithms::brute_force(values, weights, n, capacity, usedItems);

		auto end = std::chrono::high_resolution_clock::now();
		std::chrono::duration<double> duration = end - start;

		std::cout << "\n[Brute Force] Tempo de execução: " << duration.count() << " segundos\n";
		std::cout << "[Brute Force] Lucro total: " << maxProfit << std::endl;
		std::cout << "[Brute Force] Paletes selecionadas (IDs): ";
		for (unsigned int i = 0; i < n; i++) {
			if (usedItems[i])
				std::cout << pallets[i].id << " ";
		}
		std::cout << std::endl;

	} else {
		std::cout << "Algoritmo desconhecido: " << algoName << std::endl;
	}
}
