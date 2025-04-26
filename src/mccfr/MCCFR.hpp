#pragma once

#include "Actions.hpp"
#include "InfoSet.hpp"
#include "Node.hpp"
#include "PokerGame.hpp"
#include <random>
#include <unordered_map>

class MCCFR
{
  public:
    explicit MCCFR(int iterations);

    void runIterations();

  private:
    double mccfr(const std::vector<Card> &playerCards,
      const std::vector<Card> &opponentCards,
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

    double computePayoff(const std::vector<Card> &playerCards,
      const std::vector<Card> &opponentCards,
      const std::array<Card, 5> &communityCards,
      int pot,
      int traverser) const;

    void dealNextStreet(std::array<Card, 5> &communityCards, int &communityCardIndex, int street);

    InfoSetKey createInfoSet(const Card &privateCard, const std::vector<ActionID> &history) const;

    std::vector<ActionID> getAvailableActions(bool facingBet,
      int raisesThisStreet,
      int street,
      bool traverserAllIn,
      bool opponentAllIn) const;

    int sampleAction(const std::vector<double> &strategy) const;

  private:
    int iterations_;
    int betOptions_;
    std::mt19937 rng_;

    std::unordered_map<InfoSetKey, Node> nodes_;

    Deck deck_;
    PokerGame game_;
};
