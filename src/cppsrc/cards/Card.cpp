#include "Card.h"

// Constructor
Card::Card(const std::string &rank, const std::string &suit) : rank(rank), suit(suit) {}

// Getters
std::string Card::getRank() const
{
    return rank;
}
std::string Card::getSuit() const
{
    return suit;
}

int Card::getValue() const
{
    if (rank == "A") return 14;
    if (rank == "K") return 13;
    if (rank == "Q") return 12;
    if (rank == "J") return 11;

    try {
        return std::stoi(rank);
    } catch (const std::invalid_argument &) {
        throw std::runtime_error("Invalid rank: " + rank);
    }
}

std::string Card::toString() const
{
    return rank + " of " + suit;
}

// Equality operator
bool Card::operator==(const Card &other) const
{
    return rank == other.rank && suit == other.suit;
}

// Inequality operator
bool Card::operator!=(const Card &other) const
{
    return !(*this == other);
}
