#include "Deck.hpp"
#include <algorithm>
#include <stdexcept>

Deck::Deck() : cards{}, rng(std::random_device{}()), activeSize(52)
{
    static constexpr std::array<Card::SUIT, 4> suits = {
        Card::SUIT::CLUBS, Card::SUIT::HEARTS, Card::SUIT::DIAMONDS, Card::SUIT::SPADES
    };
    static constexpr std::array<Card::RANK, 13> ranks = { Card::RANK::TWO,
        Card::RANK::THREE,
        Card::RANK::FOUR,
        Card::RANK::FIVE,
        Card::RANK::SIX,
        Card::RANK::SEVEN,
        Card::RANK::EIGHT,
        Card::RANK::NINE,
        Card::RANK::TEN,
        Card::RANK::JACK,
        Card::RANK::QUEEN,
        Card::RANK::KING,
        Card::RANK::ACE };

    size_t index = 0;
    for (const auto &suit : suits) {
        for (const auto &rank : ranks) { cards[index++] = Card(rank, suit); }
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
