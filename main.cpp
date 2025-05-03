#include <iostream>
#include "csvparsing.h"

// TIP To <b>Run</b> code, press <shortcut actionId="Run"/> or click the <icon src="AllIcons.Actions.Execute"/> icon in the gutter.
int main() {
	try {
		// Read truck information from the file
		TruckData truckData = readTruckInfo("TruckAndPallets_01.csv");
		std::cout << "Truck capacity: " << truckData.capacity << std::endl;
		std::cout << "Number of pallets: " << truckData.numPallets << std::endl;

		// Read pallets from the file
		std::vector<Pallet> pallets = readPallets("Pallets_01.csv");
		for (const auto& pallet : pallets) {
			std::cout << "Pallet ID: " << pallet.id
						 << ", Weight: " << pallet.weight
						 << ", Profit: " << pallet.profit << std::endl;
		}
	} catch (const std::runtime_error& e) {
		std::cerr << "Error: " << e.what() << std::endl;
	}
	 return 0;
}
