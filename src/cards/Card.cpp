#include "Card.hpp"
#include <fmt/core.h>

Card::Card(RANK rank, SUIT suit) : rank(rank), suit(suit) {}
Card::Card() : rank(RANK::INVALID), suit(SUIT::INVALID) {}

Card::RANK Card::getRank() const
{
    return rank;
}

Card::SUIT Card::getSuit() const
{
    return suit;
}

int Card::getValue() const
{
    return static_cast<int>(rank);
}

/*
std::string Card::toString() const
{
    std::string suit_str;
    switch (suit) {
    case SUIT::HEARTS:
        suit_str = "Hearts";
        break;
    case SUIT::DIAMONDS:
        suit_str = "Diamonds";
        break;
    case SUIT::SPADES:
        suit_str = "Spades";
        break;
    case SUIT::CLUBS:
        suit_str = "Clubs";
        break;
    default:
        return "Error. Invalid suit.\n";
    }

    return fmt::format("{} of {}", static_cast<int>(rank), suit_str);
}
*/
