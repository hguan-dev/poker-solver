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
    std::ifstream inputFile("input.txt");
    if (!inputFile) {
        std::cerr << "Error: Could not open input file." << std::endl;
        return 1;
    }
    std::cin.rdbuf(inputFile.rdbuf());

    constexpr int num_runs = 10000;
    std::vector<double> durations_ns(num_runs);

    for (int i = 0; i < num_runs; i++) {
        inputFile.seekg(0);

        auto start = std::chrono::steady_clock::now();

        PokerGame pokergame;
        pokergame.playGame();

        auto end = std::chrono::steady_clock::now();
        durations_ns[i] = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
    }

    double total_time = std::accumulate(durations_ns.begin(), durations_ns.end(), 0.0);
    double avg_time = total_time / num_runs;
    double avg_time_per_game = avg_time / 16;

    auto [min_it, max_it] = std::minmax_element(durations_ns.begin(), durations_ns.end());
    double min_time = *min_it;
    double max_time = *max_it;

    std::sort(durations_ns.begin(), durations_ns.end());
    double median_time = durations_ns[num_runs / 2];

    std::cout << std::fixed << std::setprecision(3);
    std::cout << "---- Poker Solver Benchmarking ----\n";
    std::cout << "Total Runs: " << num_runs << "\n";
    std::cout << "Min Execution Time: " << min_time << " ns\n";
    std::cout << "Median Execution Time: " << median_time << " ns\n";
    std::cout << "Average Execution Time: " << avg_time << " ns\n";
    std::cout << "Max Execution Time: " << max_time << " ns\n";
    std::cout << "Average Execution Time (per round): " << avg_time_per_game << " ns\n";

    return 0;
}

