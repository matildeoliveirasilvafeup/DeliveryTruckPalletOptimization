// main.cpp
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <limits>
#include "algorithms_runner.h"
#include "csvparsing.h"

// Modo batch: corre todos os algoritmos em todos os datasets
void runBatchMode() {
    std::ofstream clearFile("results_and_graphs/results.csv", std::ofstream::trunc);
    clearFile << "Dataset,Algorithm,Execution Time (ms),Total Profit,Total Weight,Selected Pallets\n";
    clearFile.close();

    std::vector<std::string> trucks   = {
        "TruckAndPallets_01.csv",
        "TruckAndPallets_02.csv",
        "TruckAndPallets_03.csv",
        "TrucksAndPallets_04.csv"
    };
    std::vector<std::string> datasets = {
        "Pallets_01.csv",
        "Pallets_10.csv",
        "Pallets_100.csv",
        "Pallets_1000.csv"
    };

    std::cout << "Modo Batch iniciado...\n";
    for (size_t i = 0; i < datasets.size(); ++i) {
        auto truck   = readTruckInfo(trucks[i]);
        auto pallets = readPallets(datasets[i]);
        int n        = pallets.size();

        // só executa força‐bruta e backtracking se n <= 20
        std::vector<std::string> algs = {"dynamic", "greedy", "ilp"};
        if (n <= 20) {
            algs.insert(algs.begin(), {"brute_force", "back_tracking"});
        }

        std::cout << "\n[Batch] Dataset: " << datasets[i]
                  << " (n=" << n << ")\n";
        for (auto &alg : algs) {
            runAlgorithm(alg, pallets, truck.capacity,
                         datasets[i], "results_and_graphs/results.csv");
        }
    }
    std::cout << "\nModo Batch concluído. Verifique results_and_graphs/results.csv\n";
}


// Mostra o menu interativo
// Mostra o menu interativo
void showMenu() {
    std::cout << "\n==== Pallet Optimization Menu ====\n";
    std::cout << "1) Choose dataset\n";
    std::cout << "2) Choose algorithm\n";
    std::cout << "3) Run\n";
    std::cout << "4) Exit\n";
    std::cout << "Option: ";
}

int main() {
    // Seleção inicial de modo
    std::cout << "Select execution mode:\n"
              << "  1) Interactive Mode\n"
              << "  2) Batch Mode (run all algorithms)\n"
              << "Choice: ";
    int mode;
    std::cin >> mode;
    if (!std::cin || (mode != 1 && mode != 2)) {
        std::cerr << "Invalid selection. Exiting.\n";
        return 1;
    }

    if (mode == 2) {
        runBatchMode();
        return 0;
    }

    // Modo Interativo
    {
        std::ofstream clearFile("results_and_graphs/results.csv", std::ofstream::trunc);
        clearFile << "Dataset,Algorithm,Execution Time (ms),Total Profit,Total Weight,Selected Pallets\n";
    }

    TruckData truck = readTruckInfo("TruckAndPallets_01.csv");
    std::cout << "Truck capacity: " << truck.capacity
              << ", number of available pallets: " << truck.numPallets << "\n";

    std::vector<std::string> datasets   = { "Pallets_01.csv", "Pallets_10.csv", "Pallets_100.csv", "Pallets_1000.csv" };
    std::vector<std::string> algorithms = { "brute_force", "dynamic", "greedy", "ilp", "back_tracking" };
    std::vector<std::string> algoLabels  = { "Brute-force", "Dynamic Programming", "Greedy", "ILP", "Back Tracking" };

    int choiceDataset = -1;
    int choiceAlgo    = -1;

    while (true) {
        showMenu();
        int op;
        std::cin >> op;
        if (!std::cin || op < 1 || op > 4) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid option. Try again.\n";
            continue;
        }
        if (op == 4) {
            std::cout << "Exiting...\n";
            break;
        }

        if (op == 1) {
            std::cout << "\nAvailable datasets:\n";
            for (size_t i = 0; i < datasets.size(); ++i)
                std::cout << "  " << (i+1) << ") " << datasets[i] << "\n";
            std::cout << "Choose dataset (number): ";
            int d; std::cin >> d;
            if (d >= 1 && d <= (int)datasets.size()) {
                choiceDataset = d - 1;
                std::cout << "Selected dataset: " << datasets[choiceDataset] << "\n";
            } else {
                std::cout << "Invalid index.\n";
            }

        } else if (op == 2) {
            std::cout << "\nAvailable algorithms:\n";
            for (size_t i = 0; i < algoLabels.size(); ++i)
                std::cout << "  " << (i+1) << ") " << algoLabels[i] << "\n";
            std::cout << "Choose algorithm (number): ";
            int a; std::cin >> a;
            if (a >= 1 && a <= (int)algorithms.size()) {
                choiceAlgo = a - 1;
                std::cout << "Selected algorithm: " << algoLabels[choiceAlgo] << "\n";
            } else {
                std::cout << "Invalid index.\n";
            }

        } else if (op == 3) {
            if (choiceDataset < 0) {
                std::cout << "Please choose a dataset first (option 1).\n";
                continue;
            }
            if (choiceAlgo < 0) {
                std::cout << "Please choose an algorithm first (option 2).\n";
                continue;
            }
            auto pallets = readPallets(datasets[choiceDataset]);
            std::cout << "\nRunning " << algoLabels[choiceAlgo]
                      << " on dataset " << datasets[choiceDataset] << "...\n";
            runAlgorithm(
                algorithms[choiceAlgo],
                pallets,
                truck.capacity,
                datasets[choiceDataset],
                "results_and_graphs/results.csv"
            );
        }
    }
    return 0;
}