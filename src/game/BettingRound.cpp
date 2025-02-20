#include "BettingRound.hpp"
#include "InputHelper.hpp"
#include <algorithm>
#include <iostream>
#include <limits>
#include <string>

double raiseHelper(double raiseAmount)
{
    while (std::cin.fail() || raiseAmount <= 0) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cin >> raiseAmount;
    }
    return raiseAmount;
}

void handlePlayerAction(PokerGame &game, Agent *currentPlayer)
{
    double amountToCall = game.currentBet - currentPlayer->getCurrentBet();

    double raiseAmount = 0;
    double totalBet, addedAmount;

    if (amountToCall == 0) {
        ACTIONS action = get_action_from_input();

        switch (action) {
        case ACTIONS::CHECK:
            break;
        case ACTIONS::BET:
            std::cin >> raiseAmount;

            raiseAmount = raiseHelper(raiseAmount);

            totalBet = game.currentBet + raiseAmount;
            if (totalBet > currentPlayer->getChips()) { totalBet = currentPlayer->getChips(); }

            addedAmount = totalBet - currentPlayer->getCurrentBet();
            currentPlayer->deductChips(addedAmount);
            game.pot += addedAmount;
            currentPlayer->setCurrentBet(totalBet);
            game.currentBet = totalBet;
            break;
        default:
            handlePlayerAction(game, currentPlayer);
            break;
        }
    } else {
        ACTIONS action = get_action_from_input();

        switch (action) {
        case ACTIONS::FOLD:
            currentPlayer->fold();
            break;
        case ACTIONS::CALL:
            if (amountToCall > currentPlayer->getChips()) { amountToCall = currentPlayer->getChips(); }
            currentPlayer->deductChips(amountToCall);
            game.pot += amountToCall;
            currentPlayer->setCurrentBet(game.currentBet);
            break;
        case ACTIONS::RAISE:
            std::cin >> raiseAmount;

            raiseAmount = raiseHelper(raiseAmount);

            totalBet = game.currentBet + raiseAmount;
            if (totalBet > currentPlayer->getChips()) { totalBet = currentPlayer->getChips(); }

            addedAmount = totalBet - currentPlayer->getCurrentBet();
            currentPlayer->deductChips(addedAmount);
            game.pot += addedAmount;
            currentPlayer->setCurrentBet(totalBet);
            game.currentBet = totalBet;
            break;
        default:
            handlePlayerAction(game, currentPlayer);
            break;
        }
    }
}

void executeBettingRound(PokerGame &game)
{
    Agent *currentPlayer =
      game.playerIsDealer ? static_cast<Agent *>(game.player.get()) : static_cast<Agent *>(game.bot.get());
    Agent *opponent =
      game.playerIsDealer ? static_cast<Agent *>(game.bot.get()) : static_cast<Agent *>(game.player.get());

    bool bettingComplete = false;
    bool firstRound = true;

    while (!bettingComplete) {
        if (currentPlayer->isActive()) {
            if (currentPlayer == game.player.get()) {

                handlePlayerAction(game, currentPlayer);
            } else {
                game.bot->makeMove(game.pot, game.currentBet);
            }
        }

        std::swap(currentPlayer, opponent);

        if ((!opponent->isActive() || !currentPlayer->isActive())
            || (currentPlayer->getCurrentBet() == game.currentBet && opponent->getCurrentBet() == game.currentBet
                && !firstRound)) {
            bettingComplete = true;
        }
        firstRound = false;
    }

    game.setCurrentBet(0);
    game.player->setCurrentBet(0);
    game.bot->setCurrentBet(0);
}
