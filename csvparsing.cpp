#include "csvparsing.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <stdexcept>

using namespace std;

TruckData readTruckInfo(const string& filepath) {
	ifstream file(filepath);
	if (!file.is_open()) {
		throw runtime_error("Error: Couldn't open file: " + filepath);
	}

	TruckData truckInfo;
	string line;

	// Skip header
	getline(file, line);

	// Read the truck's capacity and number of pallets
	getline(file, line);
	stringstream ss(line);
	string value;

	getline(ss, value, ',');
	truckInfo.capacity = stoi(value);

	getline(ss, value, ',');
	truckInfo.numPallets = stoi(value);

	file.close();
	return truckInfo;
}

vector<Pallet> readPallets(const string& filepath) {
	ifstream file(filepath);
	if (!file.is_open()) {
		throw runtime_error("Error: Couldn't open file: " + filepath);
	}

	vector<Pallet> pallets;
	string line;

	// Skip header
	getline(file, line);

	while (getline(file, line)) {
		stringstream ss(line);
		Pallet pallet;
		string value;

		getline(ss, value, ',');
		pallet.id = stoi(value);

		getline(ss, value, ',');
		pallet.weight = stoi(value);

		getline(ss, value, ',');
		pallet.profit = stoi(value);

		pallets.push_back(pallet);
	}

	file.close();
	return pallets;
}
