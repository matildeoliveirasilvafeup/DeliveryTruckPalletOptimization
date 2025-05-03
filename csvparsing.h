#ifndef CSV_READER_H
#define CSV_READER_H

#include <string>
#include <vector>

struct Pallet {
	int id;
	int weight;
	int profit;
};

struct TruckData {
	int capacity;
	int numPallets;
};

TruckData readTruckInfo(const std::string& filepath);
std::vector<Pallet> readPallets(const std::string& filepath);

#endif  // CSVPARSING_H
