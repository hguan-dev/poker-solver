#pragma once

#include "Card.hpp"
#include "HandHashes.hpp"
#include <array>

class HandEvaluator
{
  public:
    int evaluateHand(const std::array<Card, 2> &hand, const std::array<Card, 5> &communityCards);
    int hashQuinaryResult(const unsigned char quinary[]);


  private:
    std::array<Card, 7> mergeHand(const ::std::array<Card, 2> &hand, const std::array<Card, 5> &communityCards);
};
