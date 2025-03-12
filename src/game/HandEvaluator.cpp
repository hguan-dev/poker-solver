#include "HandEvaluator.hpp"
#include <algorithm>

std::array<Card, 7> HandEvaluator::mergeHand(const std::array<Card, 2> &hand, const std::array<Card, 5> &communityCards)
{
    std::array<Card, 7> fullHand;
    std::copy(hand.begin(), hand.end(), fullHand.begin());
    std::copy(communityCards.begin(), communityCards.end(), fullHand.begin() + 2);

    return fullHand;
}

int HandEvaluator::evaluateHand(const std::array<Card, 2> &hand, const std::array<Card, 5> &communityCards)
{
    std::array<Card, 7> fullHand = mergeHand(hand, communityCards);
    int cards[7] = { 0 };
    int suit_hash = 0;

    for (int i = 0; i < 7; i++) {
        int rankValue = fullHand[i].getValue() - 2;

        int suitValue;
        char suit = fullHand[i].getSuit();
        switch (suit) {
        case 'H':
            suitValue = 0;
            break;
        case 'D':
            suitValue = 1;
            break;
        case 'S':
            suitValue = 2;
            break;
        case 'C':
            suitValue = 3;
            break;
        default:
            suitValue = 0;
        }

        cards[i] = (rankValue * 4) + suitValue;

        suit_hash += (1 << (suitValue * 3));
    }

    if (SUITS_TABLE[suit_hash]) {
        int suit_binary[4] = { 0 };
        for (int i = 0; i < 7; i++) { suit_binary[cards[i] & 0x3] |= (1 << (cards[i] / 4)); }

        return FLUSH_TABLE[suit_binary[SUITS_TABLE[suit_hash] - 1]];
    }

    unsigned char quinary[13] = { 0 };
    for (int i = 0; i < 7; i++) { quinary[cards[i] / 4]++; }

    const int hash = hashQuinaryResult(quinary);

    return NOFLUSH_TABLE[hash];
}


int HandEvaluator::hashQuinaryResult(const unsigned char quinary[])
{
    int sum = 0;
    const int len = 13;
    int i;
    int k = 7;

    for (i = 0; i < len; i++) {
        sum += DP_TABLE[quinary[i]][len - i - 1][k];

        k -= quinary[i];

        if (k <= 0) { break; }
    }

    return sum;
}
