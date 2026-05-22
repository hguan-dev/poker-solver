#include "Node.hpp"
#include <algorithm>
#include <numeric>

Node::Node(int n) : numActions(n), regretSum(n, 0.0), strategy(n, 0.0), strategySum(n, 0.0) {}

std::vector<double> Node::getStrategy()
{
    double normalize = 0.0;
    for (int a = 0; a < numActions; ++a) {
        strategy[a] = std::max(regretSum[a], 0.0);
        normalize += strategy[a];
    }

    if (normalize > 0.0) {
        for (int a = 0; a < numActions; ++a) { strategy[a] /= normalize; }
    }

    if (normalize > 0.0) {
        for (int a = 0; a < numActions; ++a) { strategy[a] /= normalize; }
    } else {
        double uniform = 1.0 / numActions;
        for (int a = 0; a < numActions; ++a) { strategy[a] = uniform; }
    }
    return strategy;
}

std::vector<double> Node::getAverageStrategy()
{
    std::vector<double> avgStrategy(numActions, 0.0);
    double normalize = std::accumulate(strategySum.begin(), strategySum.end(), 0);

    if (normalize > 0.0) {
        for (int a = 0; a < numActions; ++a) { avgStrategy[a] = strategySum[a] / normalize; }
    } else {
        double uniform = 1.0 / numActions;
        for (int a = 0; a < numActions; ++a) { avgStrategy[a] = uniform; }
    }

    return avgStrategy;
}
