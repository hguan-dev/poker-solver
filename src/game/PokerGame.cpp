#include "PokerGame.hpp"
#include "BettingRound.hpp"
#include "HandEvaluator.hpp"
#include <cstdlib>
#include <iostream>
#include <stdexcept>

PokerGame::PokerGame() : pot(0), currentBet(0), playerIsDealer(true)
{
    deck = std::make_unique<Deck>();
    player = std::make_unique<Player>(100.0);
    bot = std::make_unique<Bot>(100.0);
}

void PokerGame::playGame()
{
    while (true) {
        resetGameState();

        std::string play_again;
        std::cin >> play_again;

        if (play_again == "n") { return; }

        collectBlinds();
        dealHoleCards();

        preflop();
        flop();
        turn();
        river();

        if (player->isActive() && bot->isActive()) {
            payout();
        } else if (!player->isActive()) {
            bot->addChips(pot);
        } else if (!bot->isActive()) {
            player->addChips(pot);
        } else {
            throw std::runtime_error("Invalid folding logic.");
        }

        if (player->getChips() == 0 || bot->getChips() == 0) { break; }

        shiftDealerButton();
    }
}

void PokerGame::resetGameState()
{
    pot = 0;
    currentBet = 0;
    communityCards.fill(Card());
    deck->shuffle();
    player->reset();
    bot->reset();
}

void PokerGame::collectBlinds()
{
    double smallBlind = 0.5;
    double bigBlind = 1;

    if (playerIsDealer) {
        player->deductChips(smallBlind);
        player->setCurrentBet(smallBlind);
        bot->deductChips(bigBlind);
        bot->setCurrentBet(bigBlind);
        pot += smallBlind + bigBlind;
    } else {
        bot->deductChips(smallBlind);
        bot->setCurrentBet(smallBlind);
        player->deductChips(bigBlind);
        player->setCurrentBet(bigBlind);
        pot += smallBlind + bigBlind;
    }

    currentBet = bigBlind;
}

void PokerGame::shiftDealerButton()
{
    playerIsDealer = !playerIsDealer;
}

void PokerGame::dealHoleCards()
{
    player->setHand({ deck->popTop(), deck->popTop() });
    bot->setHand({ deck->popTop(), deck->popTop() });
}

void PokerGame::dealCommunityCards(int numCards)
{
    for (int i = 0; i < numCards; ++i) { communityCards[i] = deck->popTop(); }
}


double PokerGame::getCurrentBet()
{
    return currentBet;
}

void PokerGame::setCurrentBet(double newBet)
{
    currentBet = newBet;
}

double PokerGame::getPot()
{
    return pot;
}

void PokerGame::addToPot(double value)
{
    pot += value;
}

void PokerGame::handlePhase(int numCommunityCards)
{
    if (numCommunityCards > 0) dealCommunityCards(numCommunityCards);
    executeBettingRound(*this);
}

void PokerGame::preflop()
{
    handlePhase(0);
}

void PokerGame::flop()
{
    handlePhase(3);
}

void PokerGame::turn()
{
    handlePhase(1);
}

void PokerGame::river()
{
    handlePhase(1);
}

void PokerGame::payout()
{
    HandEvaluator evaluator;

    auto heroResult = evaluator.evaluateHand(player->getHand(), communityCards);
    auto villainResult = evaluator.evaluateHand(bot->getHand(), communityCards);

    if (heroResult == villainResult) {
        player->addChips(pot / 2);
        bot->addChips(pot / 2);
    } else if (heroResult > villainResult) {
        player->addChips(pot);
    } else {
        bot->addChips(pot);
    }

    pot = 0;
}
