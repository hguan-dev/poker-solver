#pragma once

#include "Bot.hpp"
#include "Deck.hpp"
#include "Player.hpp"
#include <array>
#include <memory>

class PokerGame
{
  private:
    std::unique_ptr<Deck> deck;
    std::unique_ptr<Player> player;
    std::unique_ptr<Bot> bot;
    std::array<Card, 5> communityCards;
    double pot;
    double currentBet;
    bool playerIsDealer;

  public:
    PokerGame();
    void playGame();
    void setCurrentBet(double newBet);
    double getCurrentBet();
    double getPot();
    void addToPot(double value);


  private:
    friend void executeBettingRound(PokerGame &game);
    friend void handlePlayerAction(PokerGame &game, Agent &currentPlayer);
    void resetGameState();
    void collectBlinds();
    void shiftDealerButton();
    void dealHoleCards();
    void dealCommunityCards(int numCards);
    void handlePhase(int numCommunityCards = 0);
    void preflop();
    void flop();
    void turn();
    void river();
    void payout();
};
