#pragma once

#include <string>

class Card
{
  public:
    Card(const char &rank, const char &suit);
    const char &getRank() const;
    const char &getSuit() const;
    int getValue() const;
    std::string toString() const;
    bool operator==(const Card &other) const
    {
        return rank == other.rank && suit == other.suit;
    }

    bool operator!=(const Card &other) const
    {
        return !(*this == other);
    }

  private:
    char rank;
    char suit;
};
