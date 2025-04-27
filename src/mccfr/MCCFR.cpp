#include "MCCFR.hpp"
#include "HandEvaluator.hpp"

MCCFR::MCCFR(int iterations)
  : iterations_(iterations), betOptions_(static_cast<int>(ActionSets::preflopOpen.size())),
    rng_(std::random_device{}()), deck_()
{}

void MCCFR::runIterations()
{
    for (int t = 1; t <= iterations_; ++t) {
        deck_.shuffle();
        std::array<Card, 2> playerCards{ deck_.popTop(), deck_.popTop() };
        std::array<Card, 2> opponentCards{ deck_.popTop(), deck_.popTop() };

        std::array<Card, 5> communityCards;
        communityCards.fill(Card());
        int communityIndex = 0;

        std::vector<ActionID> history;
        int pot = 0;
        int raisesThisStreet = 0;
        bool facingBet = false;
        bool trAllIn = false;
        bool opAllIn = false;
        int playerStack = 100;
        int opponentStack = 100;

        mccfr(playerCards,
          opponentCards,
          communityCards,
          communityIndex,
          history,
          pot,
          raisesThisStreet,
          1.0,// piTraverser
          1.0,// piOpponent
          0,// traverser = player 0
          0,// street   = preflop
          facingBet,
          trAllIn,
          opAllIn,
          playerStack,
          opponentStack,
          t);

        mccfr(playerCards,
          opponentCards,
          communityCards,
          communityIndex,
          history,
          pot,
          raisesThisStreet,
          1.0,
          1.0,
          1,// traverser = player 1
          0,// street    = preflop
          facingBet,
          trAllIn,
          opAllIn,
          playerStack,
          opponentStack,
          t);
    }
}

double MCCFR::mccfr(std::array<Card, 2> playerCards,
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
  int t)
{
    if (isTerminal(history, raisesThisStreet, street, traverserAllIn, opponentAllIn)) {
        return computePayoff(playerCards, opponentCards, communityCards, pot, traverser);
    }

    int plays = static_cast<int>(history.size());
    int acting = plays % 2;

    const Card &privateCard = (acting == 0 ? playerCards[0] : opponentCards[0]);
    InfoSetKey key = createInfoSet(privateCard, history);

    auto actions = getAvailableActions(facingBet, raisesThisStreet, street, traverserAllIn, opponentAllIn);
    if (nodes_.find(key) == nodes_.end()) { nodes_.emplace(key, Node(static_cast<int>(actions.size()))); }
    Node &node = nodes_[key];

    auto strategy = node.getStrategy();

    if (acting == traverser) {
        double nodeUtil = 0.0;
        std::vector<double> utilities(actions.size());
        for (size_t i = 0; i < actions.size(); ++i) {
            auto nextHistory = history;
            nextHistory.push_back(actions[i]);
            int nextPot = pot;// TODO: adjust based on action
            int nextRaises = raisesThisStreet;
            bool nextFacing = false;// TODO: update if bet occurred
            bool nextTrAllIn = traverserAllIn;
            bool nextOpAllIn = opponentAllIn;

            utilities[i] = mccfr(playerCards,
              opponentCards,
              communityCards,
              communityCardIndex,
              nextHistory,
              nextPot,
              nextRaises,
              piTraverser * strategy[i],
              piOpponent,
              traverser,
              street,
              nextFacing,
              nextTrAllIn,
              nextOpAllIn,
              playerStack,
              opponentStack,
              t);
            nodeUtil += strategy[i] * utilities[i];
        }

        for (size_t i = 0; i < actions.size(); ++i) {
            double regret = utilities[i] - nodeUtil;
            node.regretSum[i] += piOpponent * regret;
            node.strategySum[i] += piTraverser * strategy[i];
        }
        return nodeUtil;
    } else {
        int idx = sampleAction(strategy);
        ActionID action = actions[idx];

        auto nextHistory = history;
        nextHistory.push_back(action);
        int nextPot = pot;// TODO: adjust based on action
        int nextRaises = raisesThisStreet;
        bool nextFacing = false;// TODO: update if bet occurred
        bool nextTrAllIn = traverserAllIn;
        bool nextOpAllIn = opponentAllIn;

        double util = mccfr(playerCards,
          opponentCards,
          communityCards,
          communityCardIndex,
          nextHistory,
          nextPot,
          nextRaises,
          piTraverser,
          piOpponent * strategy[idx],
          traverser,
          street,
          nextFacing,
          nextTrAllIn,
          nextOpAllIn,
          playerStack,
          opponentStack,
          t);
        node.strategySum[idx] += piOpponent * strategy[idx];
        return util;
    }
}

bool MCCFR::isTerminal(const std::vector<ActionID> &history,
  int raisesThisStreet,
  int street,
  bool traverserAllIn,
  bool opponentAllIn) const
{
    for (auto a : history) {
        if (a == ActionID::FOLD || a == ActionID::POSTFLOP_FOLD) return true;
    }
    if (traverserAllIn && opponentAllIn) return true;
    // River reached and no further betting
    if (street == 3) return true;
    return false;
}

double MCCFR::computePayoff(const std::array<Card, 2> &player,
  const std::array<Card, 2> &opponent,
  const std::array<Card, 5> &community,
  int pot,
  int traverser) const
{
    HandEvaluator eval;
    int playerRank = eval.evaluateHand(player, community);
    int opponentRank = eval.evaluateHand(opponent, community);
    double payoff = 0.0;
    if (playerRank > opponentRank)
        payoff = pot;
    else if (playerRank < opponentRank)
        payoff = -pot;
    // Return from perspective of traverser
    return (traverser == 0 ? payoff : -payoff);
}

void MCCFR::dealNextStreet(std::array<Card, 5> &community, int &idx, int street)
{
    if (street == 0) {
        for (int i = 0; i < 3; ++i) community[idx++] = deck_.popTop();
    } else if (street < 3) {
        community[idx++] = deck_.popTop();
    }
}

InfoSetKey MCCFR::createInfoSet(const Card &privateCard, const std::vector<ActionID> &history) const
{
    InfoSetKey key;
    key.playerCard = privateCard.getValue();
    key.history = history;
    return key;
}

std::vector<ActionID> MCCFR::getAvailableActions(bool facingBet,
  int raisesThisStreet,
  int street,
  bool traverserAllIn,
  bool opponentAllIn) const
{
    if (traverserAllIn || opponentAllIn) { return {}; }
    bool canRaise = (raisesThisStreet < 3);
    if (facingBet) {
        if (canRaise) return ActionSets::facingPostflopBet;
        return { ActionID::POSTFLOP_CALL, ActionID::POSTFLOP_FOLD };
    } else {
        if (street == 0)
            return ActionSets::preflopOpen;
        else
            return ActionSets::postflopOpen;
    }
}

int MCCFR::sampleAction(const std::vector<double> &strat) const
{
    std::discrete_distribution<int> dist(strat.begin(), strat.end());
    return dist(rng_);
}
