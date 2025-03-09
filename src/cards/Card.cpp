#include "Card.hpp"
#include <fmt/core.h>

Card::Card(const char &rank, const char &suit) : rank(rank), suit(suit) {}

const char &Card::getRank() const
{
    return rank;
}
const char &Card::getSuit() const
{
    return suit;
}

int Card::getValue() const
{

    switch (rank) {
    case 'A':
        return 14;
    case 'K':
        return 13;
    case 'Q':
        return 12;
    case 'J':
        return 11;
    case 'T':
        return 10;
    default:
        break;
    }

    return rank - '0';
}

std::string Card::toString() const
{
    std::string suit_str;
    switch (suit) {
    case 'H':
        suit_str = "Hearts";
        break;
    case 'D':
        suit_str = "Diamonds";
        break;
    case 'S':
        suit_str = "Spades";
        break;
    case 'C':
        suit_str = "Clubs";
        break;
    default:
        return "Error. Invalid suit.\n";
    }

    return fmt::format("{} of {}", rank, suit_str);
}
