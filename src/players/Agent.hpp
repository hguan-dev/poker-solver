#pragma once

#include "Card.hpp"
#include <array>

class Agent
{
  public:
    virtual ~Agent() = default;
    Agent(double initialChips);

    double getChips() const;
    bool isActive() const;
    const std::array<Card, 2> &getHand() const;
    double getCurrentBet() const;

    void addChips(double amount);
    void deductChips(double amount);
    void fold();
    void reset();
    void setHand(const std::array<Card, 2> &newHand);
    void setCurrentBet(double amount);

  protected:
    double chips;
    bool active;
    std::array<Card, 2> hand;
    double currentBet;
};
