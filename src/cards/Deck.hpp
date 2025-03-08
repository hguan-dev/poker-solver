#pragma once

#include "Card.hpp"
#include <random>
#include <vector>

class Deck
{
  private:
    std::vector<Card> cards;
    size_t activeSize;
    std::mt19937 g;

  public:
    Deck();
    Card popTop();
    void shuffle();
    bool isEmpty() const;
    int getLength() const;
};

