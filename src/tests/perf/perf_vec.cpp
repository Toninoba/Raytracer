//
// Created by tobi on 19.11.26.
//


/*
 *  Perf tests for testing performance of the vector class
 *
 */

#include <chrono>
#include <iostream>
#include <random>

#include "../../lib/Vec.h"

int main() {

    std::mt19937 gen(42);

    std::uniform_real_distribution<float> dis(0.0, 5.0);

    int operations = 10000000;

    const auto start = std::chrono::high_resolution_clock::now();

    std::vector<Vec<float, 4>> results(operations);

    for (int i = 0; i < operations; i++) {

        const float x = dis(gen);
        const float y = dis(gen);
        const float z = dis(gen);

        const float x2 = dis(gen);
        const float y2 = dis(gen);
        const float z2 = dis(gen);


        Vec<float, 4> a(x, y, z, 1.0);
        Vec<float, 4> b(x2, y2, z2, 1.0);

        results[i] = a + b;
    }

    const auto end = std::chrono::high_resolution_clock::now();
    const auto elapsedTime = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

    std::cout << results.size() << ": vector additions took: " << elapsedTime.count() << " milliseconds" << std::endl;

    return 0;
}
