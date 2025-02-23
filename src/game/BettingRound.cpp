#include "BettingRound.hpp"
#include "./util/InputHelper.hpp"
#include <algorithm>
#include <limits>

void handlePlayerAction(PokerGame &game, Agent &currentPlayer)
{
    double amountToCall = game.currentBet - currentPlayer.getCurrentBet();

    double raiseAmount = 0;
    double totalBet, addedAmount;

    if (amountToCall == 0) {
        ACTIONS action = get_action_from_input();

        switch (action) {
        case ACTIONS::CHECK:
            break;
        case ACTIONS::BET:
            raiseAmount = raiseHelper();
            totalBet = game.currentBet + raiseAmount;
            if (totalBet > currentPlayer.getChips()) { totalBet = currentPlayer.getChips(); }
            addedAmount = totalBet - currentPlayer.getCurrentBet();
            currentPlayer.deductChips(addedAmount);
            game.pot += addedAmount;
            currentPlayer.setCurrentBet(totalBet);
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
            currentPlayer.fold();
            break;
        case ACTIONS::CALL:
            if (amountToCall > currentPlayer.getChips()) { amountToCall = currentPlayer.getChips(); }
            currentPlayer.deductChips(amountToCall);
            game.pot += amountToCall;
            currentPlayer.setCurrentBet(game.currentBet);
            break;
        case ACTIONS::RAISE:
            raiseAmount = raiseHelper();
            totalBet = game.currentBet + raiseAmount;
            if (totalBet > currentPlayer.getChips()) { totalBet = currentPlayer.getChips(); }
            addedAmount = totalBet - currentPlayer.getCurrentBet();
            currentPlayer.deductChips(addedAmount);
            game.pot += addedAmount;
            currentPlayer.setCurrentBet(totalBet);
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
    Agent &player = *game.player;
    Agent &bot = *game.bot;

    bool playerTurn = game.playerIsDealer;
    bool bettingComplete = false;
    bool firstRound = true;

    while (!bettingComplete) {
        Agent &currentPlayer = playerTurn ? player : bot;
        Agent &opponent = playerTurn ? bot : player;

        if (currentPlayer.isActive()) {
            if (&currentPlayer == &player) {
                handlePlayerAction(game, currentPlayer);
            } else {
                Bot *botPlayer = dynamic_cast<Bot *>(&currentPlayer);
                if (botPlayer) {
                    botPlayer->makeMove(game.pot, game.currentBet);
                } else {
                    throw std::runtime_error("Expected bot to make a move, but currentPlayer is not a Bot.");
                }
            }
        }

        playerTurn = !playerTurn;

        if ((!opponent.isActive() || !currentPlayer.isActive())
            || (currentPlayer.getCurrentBet() == game.currentBet && opponent.getCurrentBet() == game.currentBet
                && !firstRound)) {
            bettingComplete = true;
        }

        firstRound = false;
    }

    game.setCurrentBet(0);
    player.setCurrentBet(0);
    bot.setCurrentBet(0);
}
