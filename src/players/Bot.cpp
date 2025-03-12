#include "Bot.hpp"

Bot::Bot(double initialChips) : Agent(initialChips) {}

void Bot::makeMove(double &pot, double highestBet)
{
    double amountToCall = highestBet - this->getCurrentBet();

    if (amountToCall == 0) { return; }

    if (amountToCall > this->getChips()) {
        amountToCall = this->getChips();
        if (amountToCall == 0) { return; }
    } else {
        this->deductChips(amountToCall);
        pot += amountToCall;
        this->setCurrentBet(highestBet);
    }
}
