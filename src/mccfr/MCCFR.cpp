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

        MCCFRState state;
        state.playerCards = { deck_.popTop(), deck_.popTop() };
        state.opponentCards = { deck_.popTop(), deck_.popTop() };
        state.communityCards.fill(Card());
        state.iteration = t;

        state.traverser = 0;
        state.street = 0;
        mccfr(state);

        state.traverser = 1;
        state.street = 0;
        mccfr(state);
    }
}

double MCCFR::mccfr(MCCFRState state)
{
    if (isTerminal(state)) { return computePayoff(state); }

    int plays = static_cast<int>(state.history.size());
    int acting = plays % 2;

    const Card &privateCard = (acting == 0) ? state.playerCards[0] : state.opponentCards[0];
    InfoSetKey key = createInfoSet(privateCard, state.history);

    auto actions = getAvailableActions(state);
    if (nodes_.find(key) == nodes_.end()) { nodes_.emplace(key, Node(static_cast<int>(actions.size()))); }
    Node &node = nodes_[key];

    auto strategy = node.getStrategy();

    if (acting == state.traverser) {
        double nodeUtil = 0.0;
        std::vector<double> utilities(actions.size());

        for (size_t i = 0; i < actions.size(); ++i) {
            MCCFRState nextState = state;
            nextState.history.push_back(actions[i]);
            // TODO: update nextState.pot, nextState.raisesThisStreet, nextState.facingBet if needed

            utilities[i] = mccfr(nextState);
            nodeUtil += strategy[i] * utilities[i];
        }

        for (size_t i = 0; i < actions.size(); ++i) {
            double regret = utilities[i] - nodeUtil;
            node.regretSum[i] += state.piOpponent * regret;
            node.strategySum[i] += state.piTraverser * strategy[i];
        }
        return nodeUtil;
    } else {
        int idx = sampleAction(strategy);
        ActionID action = actions[idx];

        MCCFRState nextState = state;
        nextState.history.push_back(action);
        // TODO: update nextState.pot, nextState.raisesThisStreet, nextState.facingBet if needed

        double util = mccfr(nextState);
        node.strategySum[idx] += state.piOpponent * strategy[idx];
        return util;
    }
}

bool MCCFR::isTerminal(const MCCFRState &state) const
{
    for (auto a : state.history) {
        if (a == ActionID::FOLD || a == ActionID::POSTFLOP_FOLD) { return true; }
    }
    if (state.traverserAllIn && state.opponentAllIn) { return true; }
    if (state.street == 3) { return true; }
    return false;
}

double MCCFR::computePayoff(const MCCFRState &state) const
{
    HandEvaluator eval;
    int playerRank = eval.evaluateHand(state.playerCards, state.communityCards);
    int opponentRank = eval.evaluateHand(state.opponentCards, state.communityCards);
    double payoff = 0.0;
    if (playerRank > opponentRank)
        payoff = state.pot;
    else if (playerRank < opponentRank)
        payoff = -state.pot;
    return (state.traverser == 0) ? payoff : -payoff;
}

InfoSetKey MCCFR::createInfoSet(const Card &privateCard, const std::vector<ActionID> &history) const
{
    InfoSetKey key;
    key.playerCard = privateCard.getValue();
    key.history = history;
    return key;
}

std::vector<ActionID> MCCFR::getAvailableActions(const MCCFRState &state) const
{
    if (state.traverserAllIn || state.opponentAllIn) { return {}; }
    bool canRaise = (state.raisesThisStreet < 3);

    if (state.facingBet) {
        if (canRaise) { return ActionSets::facingPostflopBet; }
        return { ActionID::POSTFLOP_CALL, ActionID::POSTFLOP_FOLD };
    } else {
        if (state.street == 0) {
            return ActionSets::preflopOpen;
        } else {
            return ActionSets::postflopOpen;
        }
    }
}

int MCCFR::sampleAction(const std::vector<double> &strat) const
{
    std::discrete_distribution<int> dist(strat.begin(), strat.end());
    return dist(rng_);
}

void MCCFR::dealNextStreet(std::array<Card, 5> &community, int &idx, int street)
{
    if (street == 0) {
        for (int i = 0; i < 3; ++i) { community[idx++] = deck_.popTop(); }
    } else if (street < 3) {
        community[idx++] = deck_.popTop();
    }
}

