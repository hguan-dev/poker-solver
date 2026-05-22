#pragma once

#include <vector>

class Node
{
  public:
    int numActions;
    std::vector<double> regretSum;
    std::vector<double> strategy;
    std::vector<double> strategySum;

    Node(int n);

    std::vector<double> getStrategy();
    std::vector<double> getAverageStrategy();
};
