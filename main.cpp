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
    std::ofstream clearFile("results.csv", std::ofstream::trunc);
    clearFile << "Dataset,Algorithm,Execution Time (ms),Total Profit,Total Weight,Selected Pallets\n";
    clearFile.close();

    TruckData truck = readTruckInfo("TruckAndPallets_01.csv");

    std::vector<std::string> datasets   = { "Pallets_01.csv", "Pallets_10.csv", "Pallets_100.csv", "Pallets_1000.csv" };
    std::vector<std::string> algorithms = { "brute_force", "dynamic", "greedy", "ilp", "back_tracking"};

    std::cout << "Modo Batch iniciado...\n";
    for (const auto& ds : datasets) {
        auto pallets = readPallets(ds);
        std::cout << "\n[Batch] Dataset: " << ds << "\n";
        for (const auto& alg : algorithms) {
            runAlgorithm(alg, pallets, truck.capacity, ds, "results.csv");
        }
    }
    std::cout << "\nModo Batch concluído. Verifique o ficheiro results.csv\n";
}

// Mostra o menu interativo
void showMenu() {
    std::cout << "\n==== Menu de Otimização de Paletes ====\n";
    std::cout << "1) Escolher dataset\n";
    std::cout << "2) Escolher algoritmo\n";
    std::cout << "3) Executar\n";
    std::cout << "4) Sair\n";
    std::cout << "Opção: ";
}

int main() {
    // Seleção inicial de modo
    std::cout << "Selecione o modo de execução:\n"
              << "  1) Modo Interativo\n"
              << "  2) Modo Batch (executar todos os algoritmos)\n"
              << "Escolha: ";
    int mode;
    std::cin >> mode;
    if (!std::cin || (mode != 1 && mode != 2)) {
        std::cerr << "Seleção inválida. A terminar.\n";
        return 1;
    }

    if (mode == 2) {
        runBatchMode();
        return 0;
    }

    // Modo Interativo
    {
        std::ofstream clearFile("results.csv", std::ofstream::trunc);
        clearFile << "Dataset,Algorithm,Execution Time (ms),Total Profit,Total Weight,Selected Pallets\n";
    }

    TruckData truck = readTruckInfo("TruckAndPallets_01.csv");
    std::cout << "Capacidade do camião: " << truck.capacity
              << ", número de paletes disponíveis: " << truck.numPallets << "\n";

    std::vector<std::string> datasets   = { "Pallets_01.csv", "Pallets_10.csv", "Pallets_100.csv", "Pallets_1000.csv" };
    std::vector<std::string> algorithms = { "brute_force", "dynamic", "greedy", "ilp", "back_tracking" };
    std::vector<std::string> algoLabels  = { "Brute-force", "Programação Dinâmica", "Greedy", "ILP", "Back Tracking" };

    int choiceDataset = -1;
    int choiceAlgo    = -1;

    while (true) {
        showMenu();
        int op;
        std::cin >> op;
        if (!std::cin || op < 1 || op > 4) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Opção inválida. Tente novamente.\n";
            continue;
        }
        if (op == 4) {
            std::cout << "A sair...\n";
            break;
        }

        if (op == 1) {
            std::cout << "\nDatasets disponíveis:\n";
            for (size_t i = 0; i < datasets.size(); ++i)
                std::cout << "  " << (i+1) << ") " << datasets[i] << "\n";
            std::cout << "Escolha o dataset (número): ";
            int d; std::cin >> d;
            if (d >= 1 && d <= (int)datasets.size()) {
                choiceDataset = d - 1;
                std::cout << "Dataset selecionado: " << datasets[choiceDataset] << "\n";
            } else {
                std::cout << "Índice inválido.\n";
            }

        } else if (op == 2) {
            std::cout << "\nAlgoritmos disponíveis:\n";
            for (size_t i = 0; i < algoLabels.size(); ++i)
                std::cout << "  " << (i+1) << ") " << algoLabels[i] << "\n";
            std::cout << "Escolha o algoritmo (número): ";
            int a; std::cin >> a;
            if (a >= 1 && a <= (int)algorithms.size()) {
                choiceAlgo = a - 1;
                std::cout << "Algoritmo selecionado: " << algoLabels[choiceAlgo] << "\n";
            } else {
                std::cout << "Índice inválido.\n";
            }

        } else if (op == 3) {
            if (choiceDataset < 0) {
                std::cout << "Por favor, escolha primeiro um dataset (opção 1).\n";
                continue;
            }
            if (choiceAlgo < 0) {
                std::cout << "Por favor, escolha primeiro um algoritmo (opção 2).\n";
                continue;
            }
            auto pallets = readPallets(datasets[choiceDataset]);
            std::cout << "\nExecutando " << algoLabels[choiceAlgo]
                      << " no dataset " << datasets[choiceDataset] << "...\n";
            runAlgorithm(
                algorithms[choiceAlgo],
                pallets,
                truck.capacity,
                datasets[choiceDataset],
                "results.csv"
            );
        }
    }
    return 0;
}