#pragma once

#include "Actions.hpp"
#include "Deck.hpp"
#include "InfoSet.hpp"
#include "MCCFRState.hpp"
#include "Node.hpp"

#include <array>
#include <random>
#include <unordered_map>
#include <vector>

class MCCFR
{
  public:
    explicit MCCFR(int iterations);

    void runIterations();

  private:
    double mccfr(MCCFRState state);

    bool isTerminal(const MCCFRState &state) const;

    double computePayoff(const MCCFRState &state) const;

    void dealNextStreet(std::array<Card, 5> &community, int &idx, int street);

    InfoSetKey createInfoSet(const Card &privateCard, const std::vector<ActionID> &history) const;

    MCCFRState applyAction(const MCCFRState &state, ActionID action);

    std::vector<ActionID> getAvailableActions(const MCCFRState &state) const;

    int sampleAction(const std::vector<double> &strat) const;

    friend struct MCCFRTest_FriendAccessor;

  private:
    int iterations_;
    int betOptions_;
    mutable std::mt19937 rng_;

    std::unordered_map<InfoSetKey, Node> nodes_;

    Deck deck_;
};
