#pragma once

// #include <string>

class Card
{
  public:
    enum class SUIT { INVALID = -1, HEARTS, DIAMONDS, CLUBS, SPADES };

    enum class RANK { INVALID = 0, TWO = 2, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, TEN, JACK, QUEEN, KING, ACE };

    Card(RANK rank, SUIT suit);
    Card();
    RANK getRank() const;
    SUIT getSuit() const;
    int getValue() const;
    // std::string toString() const;
    bool operator==(const Card &other) const
    {
        return rank == other.rank && suit == other.suit;
    }

    bool operator!=(const Card &other) const
    {
        return !(*this == other);
    }

  private:
    RANK rank;
    SUIT suit;
};
