#include "HandEvaluator.hpp"
#include <algorithm>

std::array<Card, 7> HandEvaluator::mergeHand(const std::array<Card, 2> &hand, const std::array<Card, 5> &communityCards)
{
    std::array<Card, 7> fullHand;
    std::copy(hand.begin(), hand.end(), fullHand.begin());
    std::copy(communityCards.begin(), communityCards.end(), fullHand.begin() + hand.size());
    return fullHand;
}

constexpr int getSuitValue(char suit)
{
    switch (suit) {
    case 'H':
        return 0;
    case 'D':
        return 1;
    case 'S':
        return 2;
    case 'C':
        return 3;
    default:
        return 999;// Should never get here...
    }
}

// Evaluates the best possible hand rank given a player's hole cards and community cards
int HandEvaluator::evaluateHand(const std::array<Card, 2> &hand, const std::array<Card, 5> &communityCards)
{
    std::array<Card, 7> fullHand = mergeHand(hand, communityCards);

    std::array<int, 7> cardIndices{};
    int suitHash = 0;
    std::array<int, 4> suitBinary{};
    static constexpr std::array<int, 4> SUIT_SHIFT = { 1, 8, 64, 512 };

    for (size_t i = 0; i < fullHand.size(); i++) {
        int rankValue = fullHand[i].getValue() - 2;
        int suitValue = getSuitValue(fullHand[i].getSuit());

        cardIndices[i] = (rankValue * 4) + suitValue;
        suitHash += SUIT_SHIFT[suitValue];// Precomputed bit shift
        suitBinary[suitValue] |= (1 << rankValue);
    }

    if (SUITS_TABLE[suitHash]) { return FLUSH_TABLE[suitBinary[SUITS_TABLE[suitHash] - 1]]; }

    std::array<unsigned char, 13> rankQuinary{};
    for (const auto &index : cardIndices) { rankQuinary[index / 4]++; }

    return NOFLUSH_TABLE[hashQuinaryResult(rankQuinary)];
}

// Computes a unique hash for a hand based on rank frequency using precomputed DP table
int HandEvaluator::hashQuinaryResult(const std::array<unsigned char, 13> &rankQuinary)
{
    int sum = 0;
    int remainingCards = 7;

    for (size_t rank = 0; rank < rankQuinary.size(); rank++) {
        sum += DP_TABLE[rankQuinary[rank]][13 - rank - 1][remainingCards];
        remainingCards -= rankQuinary[rank];

        if (remainingCards <= 0) break;
    }

    return sum;
}
