#pragma once

#include "Actions.hpp"
#include "Card.hpp"

struct MCCFRState
{
    std::array<Card, 2> playerCards;
    std::array<Card, 2> opponentCards;
    std::array<Card, 5> communityCards;
    int communityCardIndex = 0;
    std::vector<ActionID> history;
    int pot = 0;
    int raisesThisStreet = 0;
    double piTraverser = 1.0;
    double piOpponent = 1.0;
    int traverser = 0;// 0 = player, 1 = opponent
    int street = 0;// 0 = preflop, 1 = flop, 2 = turn, 3 = river
    bool facingBet = false;
    bool traverserAllIn = false;
    bool opponentAllIn = false;
    int playerStack = 100;
    int opponentStack = 100;
    int iteration = 0;
};
