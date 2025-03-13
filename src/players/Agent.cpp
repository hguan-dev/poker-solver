#include "Agent.hpp"

Agent::Agent(double initialChips) : chips(initialChips), active(true), hand{}, currentBet(0) {}

double Agent::getChips() const
{
    return chips;
}

bool Agent::isActive() const
{
    return active;
}

const std::array<Card, 2> &Agent::getHand() const
{
    return hand;
}

double Agent::getCurrentBet() const
{
    return currentBet;
}

void Agent::addChips(double amount)
{
    chips += amount;
}

void Agent::deductChips(double amount)
{
    chips -= amount;
}

void Agent::fold()
{
    active = false;
}

void Agent::reset()
{
    active = true;
    hand = {};
    currentBet = 0;
}

void Agent::setHand(const std::array<Card, 2> &newHand)
{
    hand = newHand;
}

void Agent::setCurrentBet(double amount)
{
    currentBet = amount;
}
