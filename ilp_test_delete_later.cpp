//
// Created by Milla on 20/05/2025.
//

#include <format>

#include "algorithms.h"
#include <iostream>
#include <unistd.h>
#include <vector>
#include <linux/limits.h>


int main() {
    unsigned int values[5] = {1, 2, 6, 3, 4};
    unsigned int weights[5] = {6, 6, 5, 1, 1};
    Algorithms::ilp(values, weights, 5, 5, {});

    return 0;

}
