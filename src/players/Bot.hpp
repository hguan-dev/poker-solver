#pragma once

#include "Agent.hpp"

class Bot : public Agent
{
  public:
    Bot(double initialChips);

    void makeMove(double &pot, double highestBet);
};
