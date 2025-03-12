#pragma once

#include "Card.hpp"
#include <array>
#include <random>

class Deck
{
  private:
    std::array<Card, 52> cards;
    size_t activeSize;
    std::mt19937 g;

  public:
    Deck();
    Card popTop();
    void shuffle();
    bool isEmpty() const;
    int getLength() const;
};
