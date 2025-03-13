#include "Deck.hpp"
#include <algorithm>
#include <stdexcept>

Deck::Deck() : cards{}, rng(std::random_device{}()), activeSize(52)
{
    const char suits[4] = { 'H', 'D', 'C', 'S' };
    const char ranks[13] = { '2', '3', '4', '5', '6', '7', '8', '9', 'T', 'J', 'Q', 'K', 'A' };

    size_t index = 0;
    for (char suit : suits) {
        for (char rank : ranks) { cards[index++] = Card(rank, suit); }
    }
}

Card Deck::popTop()
{
    if (activeSize <= 0) { throw std::out_of_range("No cards left in deck"); }

    return cards[--activeSize];
}

void Deck::shuffle()
{
    activeSize = 52;
    std::shuffle(cards.begin(), cards.begin() + activeSize, rng);
}

int Deck::getLength() const
{
    return static_cast<int>(activeSize);
}
