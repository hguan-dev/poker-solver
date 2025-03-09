#include "PokerGame.hpp"
#include <algorithm>
#include <chrono>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <numeric>
#include <vector>

int main()
{
    constexpr const char *INPUT_FILE = "input.txt";
    std::ifstream inputFile(INPUT_FILE);
    if (!inputFile) {
        std::cerr << "Error: Could not open input file." << std::endl;
        return 1;
    }
    std::cin.rdbuf(inputFile.rdbuf());

    constexpr int NUM_RUNS = 100000;
    std::vector<double> durations_ns(NUM_RUNS);

    for (int i = 0; i < NUM_RUNS; i++) {
        inputFile.seekg(0);

        auto start = std::chrono::steady_clock::now();

        PokerGame pokergame;
        pokergame.playGame();

        auto end = std::chrono::steady_clock::now();
        durations_ns[i] = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
    }

    double total_time = std::accumulate(durations_ns.begin(), durations_ns.end(), 0.0);
    double avg_time = total_time / NUM_RUNS;
    constexpr int NUM_GAMES = 16;
    double avg_time_per_game = avg_time / NUM_GAMES;

    auto [min_it, max_it] = std::minmax_element(durations_ns.begin(), durations_ns.end());
    double min_time = *min_it;
    double max_time = *max_it;

    std::sort(durations_ns.begin(), durations_ns.end());
    double median_time = durations_ns[NUM_RUNS / 2];

    std::cout << std::fixed << std::setprecision(3);
    std::cout << "---- Poker Solver Benchmarking ----\n";
    std::cout << "Total Runs: " << NUM_RUNS << "\n";
    std::cout << "Min Execution Time: " << min_time << " ns\n";
    std::cout << "Median Execution Time: " << median_time << " ns\n";
    std::cout << "Average Execution Time: " << avg_time << " ns\n";
    std::cout << "Max Execution Time: " << max_time << " ns\n";
    std::cout << "Average Execution Time (per round): " << avg_time_per_game << " ns\n";

    return 0;
}
