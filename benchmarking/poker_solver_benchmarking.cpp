#include "PokerGame.hpp"
#include <chrono>
#include <fstream>
#include <iostream>
#include <iomanip>
#include <vector>
#include <algorithm>

int main()
{
    std::ifstream inputFile("input.txt");
    if (!inputFile) {
        std::cerr << "Error: Could not open input file." << std::endl;
        return 1;
    }
    std::cin.rdbuf(inputFile.rdbuf());

    const int num_runs = 10000;
    std::vector<double>durations_ns;
    durations_ns.reserve(num_runs);
    double tot = 0.0;

    for (int i = 0; i < num_runs; i++) {
        inputFile.clear();
        inputFile.seekg(0, std::ios::beg);

        auto start = std::chrono::high_resolution_clock::now();

        PokerGame pokergame;
        pokergame.playGame();

        auto end = std::chrono::high_resolution_clock::now();
        double duration_ns = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();

        durations_ns.push_back(duration_ns);
        tot += duration_ns;
    }

    double avg_time = tot / num_runs;
    double avg_time_per_game = tot / (num_runs * 10);
    double max_time = *std::max_element(durations_ns.begin(), durations_ns.end());
    double min_time = *std::min_element(durations_ns.begin(), durations_ns.end());

    std::cout << std::fixed << std::setprecision(2);
    std::cout << "---- Poker Solver Benchmarking ----";
    std::cout << "Total Runs: " << num_runs << "\n";
    std::cout << "Min Execution Time: " << min_time << " ns\n";
    std::cout << "Average Execution Time: " << avg_time << " ns\n";
    std::cout << "Max Execution Time: " << max_time << " ns\n";   
    std::cout << "Average Execution Time (per round): " << avg_time_per_game << " ns\n";
    return 0;
}
