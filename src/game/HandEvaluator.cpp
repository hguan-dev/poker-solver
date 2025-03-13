#include "HandEvaluator.hpp"
#include <algorithm>

std::array<Card, 7> HandEvaluator::mergeHand(const std::array<Card, 2> &hand, const std::array<Card, 5> &communityCards)
{
    std::array<Card, 7> fullHand;
    std::copy(hand.begin(), hand.end(), fullHand.begin());
    std::copy(communityCards.begin(), communityCards.end(), fullHand.begin() + 2);
    return fullHand;
}

int getSuitValue(char suit)
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
        return 0;
    }
}

// Evaluates the best possible hand rank given a player's hole cards and community cards
int HandEvaluator::evaluateHand(const std::array<Card, 2> &hand, const std::array<Card, 5> &communityCards)
{
    std::array<Card, 7> fullHand = mergeHand(hand, communityCards);

    int cardIndices[7] = { 0 };// Encodes rank & suit for hashing
    int suitHash = 0;

    // Convert cards to numerical representation
    for (int i = 0; i < 7; i++) {
        int rankValue = fullHand[i].getValue() - 2;
        int suitValue = getSuitValue(fullHand[i].getSuit());

        cardIndices[i] = (rankValue * 4) + suitValue;
        suitHash += (1 << (suitValue * 3));
    }

    // Check if the hand is a flush
    if (SUITS_TABLE[suitHash]) {
        int suitBinary[4] = { 0 };

        for (int i = 0; i < 7; i++) {
            int suit = cardIndices[i] & 0x3;
            int rank = cardIndices[i] / 4;
            suitBinary[suit] |= (1 << rank);
        }

        return FLUSH_TABLE[suitBinary[SUITS_TABLE[suitHash] - 1]];
    }

    // Convert to quinary representation (number of each rank present)
    unsigned char rankQuinary[13] = { 0 };
    for (int i = 0; i < 7; i++) { rankQuinary[cardIndices[i] / 4]++; }

    int hash = hashQuinaryResult(rankQuinary);
    return NOFLUSH_TABLE[hash];
}

// Computes a unique hash for a hand based on rank frequency using precomputed DP table
int HandEvaluator::hashQuinaryResult(const unsigned char rankQuinary[])
{
    int sum = 0;
    int remainingCards = 7;

    for (int rank = 0; rank < 13; rank++) {
        sum += DP_TABLE[rankQuinary[rank]][13 - rank - 1][remainingCards];
        remainingCards -= rankQuinary[rank];

        if (remainingCards <= 0) break;
    }

    return sum;
}
