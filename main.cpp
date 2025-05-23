#include <iostream>
#include <fstream>   // For clearing the CSV file
#include <vector>
#include "algorithms_runner.h"
#include "csvparsing.h"

int main() {
	try {
		// Clear the content of the CSV file before starting and writes the header
		std::ofstream clearFile("results.csv", std::ofstream::out | std::ofstream::trunc);
		clearFile << "Dataset,Algorithm,Execution Time (ms),Total Profit,Total Weight,Selected Pallets\n";
		clearFile.close();


		// Read truck data (capacity and number of pallets)
		TruckData truckData = readTruckInfo("TruckAndPallets_01.csv");
		std::cout << "Truck capacity: " << truckData.capacity << std::endl;
		std::cout << "Number of pallets: " << truckData.numPallets << std::endl;

		// List of datasets to evaluate
		std::vector<std::string> datasets = {
			"Pallets_01.csv",
			"Pallets_02.csv",
			"Pallets_03.csv"
			// Add more dataset files here if needed
		};

		// List of algorithms to run
		std::vector<std::string> algorithms = {
			"brute_force",
			"dynamic",
			"ilp"
		};

		// Loop over each dataset and run all algorithms
		for (const auto& dataset : datasets) {
			// Read pallets from the current dataset file
			std::vector<Pallet> pallets = readPallets(dataset);

			std::cout << "Running algorithms for dataset: " << dataset << std::endl;

			for (const auto& algorithm : algorithms) {
				// Run the algorithm and save the results to CSV
				runAlgorithm(algorithm, pallets, truckData.capacity, dataset, "results.csv");
			}
		}

		std::cout << "All algorithms executed successfully on all datasets!" << std::endl;

	} catch (const std::runtime_error& e) {
		std::cerr << "Error: " << e.what() << std::endl;
	}

	return 0;
}
