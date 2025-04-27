#pragma once

#include "Actions.hpp"
#include "Deck.hpp"
#include "InfoSet.hpp"
#include "Node.hpp"
#include <unordered_map>

class MCCFR
{
  public:
    explicit MCCFR(int iterations);

    void runIterations();

  private:
    double mccfr(std::array<Card, 2> playerCards,
      std::array<Card, 2> opponentCards,
      std::array<Card, 5> communityCards,
      int communityCardIndex,
      std::vector<ActionID> history,
      int pot,
      int raisesThisStreet,
      double piTraverser,
      double piOpponent,
      int traverser,
      int street,
      bool facingBet,
      bool traverserAllIn,
      bool opponentAllIn,
      int playerStack,
      int opponentStack,
      int t);

    bool isTerminal(const std::vector<ActionID> &history,
      int raisesThisStreet,
      int street,
      bool traverserAllIn,
      bool opponentAllIn) const;

    double computePayoff(const std::array<Card, 2> &player,
      const std::array<Card, 2> &opponent,
      const std::array<Card, 5> &community,
      int pot,
      int traverser) const;

    void dealNextStreet(std::array<Card, 5> &community, int &idx, int street);

    InfoSetKey createInfoSet(const Card &privateCard, const std::vector<ActionID> &history) const;

    std::vector<ActionID> getAvailableActions(bool facingBet,
      int raisesThisStreet,
      int street,
      bool traverserAllIn,
      bool opponentAllIn) const;

    int sampleAction(const std::vector<double> &strat) const;

  private:
    int iterations_;
    int betOptions_;
    mutable std::mt19937 rng_;

    std::unordered_map<InfoSetKey, Node> nodes_;

    Deck deck_;
};
