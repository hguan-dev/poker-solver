#include "Deck.hpp"
#include <algorithm>
#include <stdexcept>

Deck::Deck() : g(std::random_device{}())
{
    const char suits[4] = { 'H', 'D', 'C', 'S' };
    const char ranks[13] = { '2', '3', '4', '5', '6', '7', '8', '9', 'T', 'J', 'Q', 'K', 'A' };

    for (const char &suit : suits) {
        for (const char &rank : ranks) { cards.emplace_back(rank, suit); }
    }
    activeSize = cards.size();
}

Card Deck::popTop()
{
    if (isEmpty()) { throw std::out_of_range("No cards left in deck"); }
    return std::move(cards[--activeSize]);
}

void Deck::shuffle()
{
    std::shuffle(cards.begin(), cards.end(), g);
    activeSize = cards.size();
}

bool Deck::isEmpty() const
{
    return activeSize == 0;
}

int Deck::getLength() const
{
    return static_cast<int>(activeSize);
}
