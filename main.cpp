#include <iostream>
#include "algorithms_runner.h"
#include "csvparsing.h"

int main() {
	try {
		TruckData truckData = readTruckInfo("TruckAndPallets_01.csv");
		std::cout << "Truck capacity: " << truckData.capacity << std::endl;
		std::cout << "Number of pallets: " << truckData.numPallets << std::endl;

		std::vector<Pallet> pallets = readPallets("Pallets_01.csv");

		for (const auto& pallet : pallets) {
			std::cout << "Pallet ID: " << pallet.id << ", Weight: " << pallet.weight << ", Profit: " << pallet.profit << std::endl;
		}

		// Pede ao utilizador ou define o algoritmo aqui
		std::string algo = "brute_force";
		runAlgorithm(algo, pallets, truckData.capacity);

	} catch (const std::runtime_error& e) {
		std::cerr << "Error: " << e.what() << std::endl;
	}
	return 0;
}
