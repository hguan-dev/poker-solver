#include "Card.hpp"
#include "HandEvaluator.hpp"
#include <array>
#include <gtest/gtest.h>

using cardArr2 = std::array<Card, 2>;
using cardArr5 = std::array<Card, 5>;

// -----------------------------------------------------------------
// Adjacent ranking comparisons (10 tests)

// 1. Royal Flush beats Straight Flush
TEST(HandEvaluatorComparison, RoyalFlushBeatsStraightFlush)
{
    HandEvaluator evaluator;
    cardArr5 community = { Card(Card::RANK::TEN, Card::SUIT::HEARTS),
        Card(Card::RANK::JACK, Card::SUIT::HEARTS),
        Card(Card::RANK::QUEEN, Card::SUIT::HEARTS),
        Card(Card::RANK::KING, Card::SUIT::HEARTS),
        Card(Card::RANK::TWO, Card::SUIT::CLUBS) };
    cardArr2 royalFlush = { Card(Card::RANK::ACE, Card::SUIT::HEARTS), Card(Card::RANK::THREE, Card::SUIT::CLUBS) };
    cardArr2 straightFlush = { Card(Card::RANK::NINE, Card::SUIT::HEARTS), Card(Card::RANK::FOUR, Card::SUIT::CLUBS) };

    int royalFlushVal = evaluator.evaluateHand(royalFlush, community);
    int straightFlushVal = evaluator.evaluateHand(straightFlush, community);
    EXPECT_LT(royalFlushVal, straightFlushVal);
}

// 2. Straight Flush beats Four‐of‐a‐Kind (Quads)
TEST(HandEvaluatorComparison, StraightFlushBeatsQuads)
{
    HandEvaluator evaluator;
    cardArr5 community = { Card(Card::RANK::QUEEN, Card::SUIT::HEARTS),
        Card(Card::RANK::QUEEN, Card::SUIT::CLUBS),
        Card(Card::RANK::SEVEN, Card::SUIT::HEARTS),
        Card(Card::RANK::EIGHT, Card::SUIT::HEARTS),
        Card(Card::RANK::NINE, Card::SUIT::HEARTS) };
    cardArr2 straightFlush = { Card(Card::RANK::SIX, Card::SUIT::HEARTS), Card(Card::RANK::TEN, Card::SUIT::HEARTS) };
    cardArr2 quads = { Card(Card::RANK::QUEEN, Card::SUIT::DIAMONDS), Card(Card::RANK::QUEEN, Card::SUIT::SPADES) };

    int straightFlushVal = evaluator.evaluateHand(straightFlush, community);
    int quadsVal = evaluator.evaluateHand(quads, community);
    EXPECT_LT(straightFlushVal, quadsVal);
}

// 3. Four‐of‐a‐Kind beats Full House
TEST(HandEvaluatorComparison, QuadsBeatsFullHouse)
{
    HandEvaluator evaluator;
    cardArr5 community = { Card(Card::RANK::NINE, Card::SUIT::SPADES),
        Card(Card::RANK::NINE, Card::SUIT::HEARTS),
        Card(Card::RANK::NINE, Card::SUIT::DIAMONDS),
        Card(Card::RANK::KING, Card::SUIT::CLUBS),
        Card(Card::RANK::QUEEN, Card::SUIT::CLUBS) };
    cardArr2 quads = { Card(Card::RANK::NINE, Card::SUIT::CLUBS), Card(Card::RANK::TWO, Card::SUIT::SPADES) };
    cardArr2 fullHouse = { Card(Card::RANK::KING, Card::SUIT::DIAMONDS), Card(Card::RANK::KING, Card::SUIT::HEARTS) };

    int quadsVal = evaluator.evaluateHand(quads, community);
    int fullHouseVal = evaluator.evaluateHand(fullHouse, community);
    EXPECT_LT(quadsVal, fullHouseVal);
}

// 4. Full House beats Flush
TEST(HandEvaluatorComparison, FullHouseBeatsFlush)
{
    HandEvaluator evaluator;
    cardArr5 community = { Card(Card::RANK::TWO, Card::SUIT::HEARTS),
        Card(Card::RANK::FIVE, Card::SUIT::HEARTS),
        Card(Card::RANK::FIVE, Card::SUIT::DIAMONDS),
        Card(Card::RANK::KING, Card::SUIT::DIAMONDS),
        Card(Card::RANK::THREE, Card::SUIT::HEARTS) };
    cardArr2 fullHouse = { Card(Card::RANK::KING, Card::SUIT::HEARTS), Card(Card::RANK::KING, Card::SUIT::CLUBS) };
    cardArr2 flush = { Card(Card::RANK::NINE, Card::SUIT::HEARTS), Card(Card::RANK::JACK, Card::SUIT::HEARTS) };

    int fullHouseVal = evaluator.evaluateHand(fullHouse, community);
    int flushVal = evaluator.evaluateHand(flush, community);
    EXPECT_LT(fullHouseVal, flushVal);
}

// 5. Flush beats Straight
TEST(HandEvaluatorComparison, FlushBeatsStraight)
{
    HandEvaluator evaluator;
    cardArr5 community = { Card(Card::RANK::FOUR, Card::SUIT::HEARTS),
        Card(Card::RANK::FIVE, Card::SUIT::HEARTS),
        Card(Card::RANK::NINE, Card::SUIT::HEARTS),
        Card(Card::RANK::TEN, Card::SUIT::CLUBS),
        Card(Card::RANK::JACK, Card::SUIT::DIAMONDS) };
    cardArr2 flushHand = { Card(Card::RANK::TWO, Card::SUIT::HEARTS), Card(Card::RANK::EIGHT, Card::SUIT::HEARTS) };
    cardArr2 straightHand = { Card(Card::RANK::SEVEN, Card::SUIT::CLUBS), Card(Card::RANK::EIGHT, Card::SUIT::CLUBS) };

    int flushVal = evaluator.evaluateHand(flushHand, community);
    int straightVal = evaluator.evaluateHand(straightHand, community);
    EXPECT_LT(flushVal, straightVal);
}

// 6. Straight beats Three‐of‐a‐Kind
TEST(HandEvaluatorComparison, StraightBeatsThreeOfAKind)
{
    HandEvaluator evaluator;
    cardArr5 community = { Card(Card::RANK::THREE, Card::SUIT::DIAMONDS),
        Card(Card::RANK::FIVE, Card::SUIT::CLUBS),
        Card(Card::RANK::SEVEN, Card::SUIT::HEARTS),
        Card(Card::RANK::QUEEN, Card::SUIT::SPADES),
        Card(Card::RANK::KING, Card::SUIT::DIAMONDS) };
    cardArr2 straightHand = { Card(Card::RANK::FOUR, Card::SUIT::HEARTS), Card(Card::RANK::SIX, Card::SUIT::HEARTS) };
    cardArr2 trips = { Card(Card::RANK::SEVEN, Card::SUIT::CLUBS), Card(Card::RANK::SEVEN, Card::SUIT::DIAMONDS) };

    int straightVal = evaluator.evaluateHand(straightHand, community);
    int tripsVal = evaluator.evaluateHand(trips, community);
    EXPECT_LT(straightVal, tripsVal);
}

// 7. Three‐of‐a‐Kind beats Two Pair
TEST(HandEvaluatorComparison, ThreeOfAKindBeatsTwoPair)
{
    HandEvaluator evaluator;
    cardArr5 community = { Card(Card::RANK::TWO, Card::SUIT::CLUBS),
        Card(Card::RANK::FIVE, Card::SUIT::DIAMONDS),
        Card(Card::RANK::NINE, Card::SUIT::HEARTS),
        Card(Card::RANK::KING, Card::SUIT::SPADES),
        Card(Card::RANK::THREE, Card::SUIT::DIAMONDS) };
    cardArr2 trips = { Card(Card::RANK::NINE, Card::SUIT::CLUBS), Card(Card::RANK::NINE, Card::SUIT::DIAMONDS) };
    cardArr2 twoPair = { Card(Card::RANK::KING, Card::SUIT::DIAMONDS), Card(Card::RANK::FIVE, Card::SUIT::CLUBS) };

    int tripsVal = evaluator.evaluateHand(trips, community);
    int twoPairVal = evaluator.evaluateHand(twoPair, community);
    EXPECT_LT(tripsVal, twoPairVal);
}

// 8. Two Pair beats One Pair
TEST(HandEvaluatorComparison, TwoPairBeatsOnePair)
{
    HandEvaluator evaluator;
    cardArr5 community = { Card(Card::RANK::FOUR, Card::SUIT::CLUBS),
        Card(Card::RANK::SEVEN, Card::SUIT::DIAMONDS),
        Card(Card::RANK::NINE, Card::SUIT::HEARTS),
        Card(Card::RANK::JACK, Card::SUIT::SPADES),
        Card(Card::RANK::THREE, Card::SUIT::DIAMONDS) };
    cardArr2 twoPair = { Card(Card::RANK::FOUR, Card::SUIT::HEARTS), Card(Card::RANK::SEVEN, Card::SUIT::CLUBS) };
    cardArr2 onePair = { Card(Card::RANK::FOUR, Card::SUIT::DIAMONDS), Card(Card::RANK::TWO, Card::SUIT::CLUBS) };

    int twoPairVal = evaluator.evaluateHand(twoPair, community);
    int onePairVal = evaluator.evaluateHand(onePair, community);
    EXPECT_LT(twoPairVal, onePairVal);
}

// 9. One Pair beats High Card
TEST(HandEvaluatorComparison, OnePairBeatsHighCard)
{
    HandEvaluator evaluator;
    cardArr5 community = { Card(Card::RANK::FOUR, Card::SUIT::CLUBS),
        Card(Card::RANK::SEVEN, Card::SUIT::DIAMONDS),
        Card(Card::RANK::NINE, Card::SUIT::HEARTS),
        Card(Card::RANK::JACK, Card::SUIT::SPADES),
        Card(Card::RANK::THREE, Card::SUIT::DIAMONDS) };
    cardArr2 onePair = { Card(Card::RANK::JACK, Card::SUIT::DIAMONDS), Card(Card::RANK::TWO, Card::SUIT::CLUBS) };
    cardArr2 highCard = { Card(Card::RANK::ACE, Card::SUIT::CLUBS), Card(Card::RANK::EIGHT, Card::SUIT::SPADES) };

    int onePairVal = evaluator.evaluateHand(onePair, community);
    int highCardVal = evaluator.evaluateHand(highCard, community);
    EXPECT_LT(onePairVal, highCardVal);
}

// 10. High Card Tie (both players’ best five cards come solely from the board)
TEST(HandEvaluatorComparison, HighCardTie)
{
    HandEvaluator evaluator;
    cardArr5 community = { Card(Card::RANK::FOUR, Card::SUIT::CLUBS),
        Card(Card::RANK::SEVEN, Card::SUIT::DIAMONDS),
        Card(Card::RANK::NINE, Card::SUIT::HEARTS),
        Card(Card::RANK::JACK, Card::SUIT::SPADES),
        Card(Card::RANK::KING, Card::SUIT::DIAMONDS) };
    cardArr2 highCard1 = { Card(Card::RANK::TWO, Card::SUIT::CLUBS), Card(Card::RANK::THREE, Card::SUIT::DIAMONDS) };
    cardArr2 highCard2 = { Card(Card::RANK::THREE, Card::SUIT::CLUBS), Card(Card::RANK::TWO, Card::SUIT::DIAMONDS) };

    int highCardVal1 = evaluator.evaluateHand(highCard1, community);
    int highCardVal2 = evaluator.evaluateHand(highCard2, community);
    EXPECT_EQ(highCardVal1, highCardVal2);
}

// -----------------------------------------------------------------
// Additional tests comparing non‐adjacent rankings

// 11. Royal Flush beats Quads
TEST(HandEvaluatorComparison, RoyalFlushBeatsQuads)
{
    HandEvaluator evaluator;
    cardArr5 community = { Card(Card::RANK::TEN, Card::SUIT::HEARTS),
        Card(Card::RANK::JACK, Card::SUIT::HEARTS),
        Card(Card::RANK::QUEEN, Card::SUIT::HEARTS),
        Card(Card::RANK::KING, Card::SUIT::HEARTS),
        Card(Card::RANK::KING, Card::SUIT::DIAMONDS) };
    cardArr2 royalFlush = { Card(Card::RANK::ACE, Card::SUIT::HEARTS), Card(Card::RANK::THREE, Card::SUIT::CLUBS) };
    cardArr2 quads = { Card(Card::RANK::KING, Card::SUIT::CLUBS), Card(Card::RANK::KING, Card::SUIT::SPADES) };

    int royalFlushVal = evaluator.evaluateHand(royalFlush, community);
    int quadsVal = evaluator.evaluateHand(quads, community);
    EXPECT_LT(royalFlushVal, quadsVal);
}

// 12. Royal Flush beats Full House
TEST(HandEvaluatorComparison, RoyalFlushBeatsFullHouse)
{
    HandEvaluator evaluator;
    cardArr5 community = { Card(Card::RANK::TEN, Card::SUIT::HEARTS),
        Card(Card::RANK::JACK, Card::SUIT::HEARTS),
        Card(Card::RANK::QUEEN, Card::SUIT::HEARTS),
        Card(Card::RANK::KING, Card::SUIT::HEARTS),
        Card(Card::RANK::TEN, Card::SUIT::DIAMONDS) };
    cardArr2 royalFlush = { Card(Card::RANK::ACE, Card::SUIT::HEARTS), Card(Card::RANK::THREE, Card::SUIT::CLUBS) };
    cardArr2 fullHouse = { Card(Card::RANK::JACK, Card::SUIT::CLUBS), Card(Card::RANK::JACK, Card::SUIT::DIAMONDS) };

    int royalFlushVal = evaluator.evaluateHand(royalFlush, community);
    int fullHouseVal = evaluator.evaluateHand(fullHouse, community);
    EXPECT_LT(royalFlushVal, fullHouseVal);
}

// 13. Royal Flush beats Flush
TEST(HandEvaluatorComparison, RoyalFlushBeatsFlush)
{
    HandEvaluator evaluator;
    cardArr5 community = { Card(Card::RANK::TEN, Card::SUIT::HEARTS),
        Card(Card::RANK::JACK, Card::SUIT::HEARTS),
        Card(Card::RANK::QUEEN, Card::SUIT::HEARTS),
        Card(Card::RANK::KING, Card::SUIT::HEARTS),
        Card(Card::RANK::TWO, Card::SUIT::CLUBS) };
    cardArr2 royalFlush = { Card(Card::RANK::ACE, Card::SUIT::HEARTS), Card(Card::RANK::THREE, Card::SUIT::CLUBS) };
    cardArr2 flush = { Card(Card::RANK::NINE, Card::SUIT::HEARTS), Card(Card::RANK::FOUR, Card::SUIT::HEARTS) };

    int royalFlushVal = evaluator.evaluateHand(royalFlush, community);
    int flushVal = evaluator.evaluateHand(flush, community);
    EXPECT_LT(royalFlushVal, flushVal);
}

// 14. Royal Flush beats Straight
TEST(HandEvaluatorComparison, RoyalFlushBeatsStraight)
{
    HandEvaluator evaluator;
    cardArr5 community = { Card(Card::RANK::TEN, Card::SUIT::HEARTS),
        Card(Card::RANK::JACK, Card::SUIT::HEARTS),
        Card(Card::RANK::QUEEN, Card::SUIT::HEARTS),
        Card(Card::RANK::KING, Card::SUIT::HEARTS),
        Card(Card::RANK::TWO, Card::SUIT::CLUBS) };
    cardArr2 royalFlush = { Card(Card::RANK::ACE, Card::SUIT::HEARTS), Card(Card::RANK::THREE, Card::SUIT::CLUBS) };
    cardArr2 straight = { Card(Card::RANK::NINE, Card::SUIT::CLUBS), Card(Card::RANK::EIGHT, Card::SUIT::DIAMONDS) };

    int royalFlushVal = evaluator.evaluateHand(royalFlush, community);
    int straightVal = evaluator.evaluateHand(straight, community);
    EXPECT_LT(royalFlushVal, straightVal);
}

// 15. Royal Flush beats Three‐of‐a‐Kind
TEST(HandEvaluatorComparison, RoyalFlushBeatsThreeOfAKind)
{
    HandEvaluator evaluator;
    cardArr5 community = { Card(Card::RANK::TEN, Card::SUIT::HEARTS),
        Card(Card::RANK::JACK, Card::SUIT::HEARTS),
        Card(Card::RANK::QUEEN, Card::SUIT::HEARTS),
        Card(Card::RANK::KING, Card::SUIT::HEARTS),
        Card(Card::RANK::TWO, Card::SUIT::CLUBS) };
    cardArr2 royalFlush = { Card(Card::RANK::ACE, Card::SUIT::HEARTS), Card(Card::RANK::THREE, Card::SUIT::CLUBS) };
    cardArr2 trips = { Card(Card::RANK::TWO, Card::SUIT::DIAMONDS), Card(Card::RANK::TWO, Card::SUIT::SPADES) };

    int royalFlushVal = evaluator.evaluateHand(royalFlush, community);
    int tripsVal = evaluator.evaluateHand(trips, community);
    EXPECT_LT(royalFlushVal, tripsVal);
}

// 16. Royal Flush beats Two Pair
TEST(HandEvaluatorComparison, RoyalFlushBeatsTwoPair)
{
    HandEvaluator evaluator;
    cardArr5 community = { Card(Card::RANK::TEN, Card::SUIT::HEARTS),
        Card(Card::RANK::JACK, Card::SUIT::HEARTS),
        Card(Card::RANK::QUEEN, Card::SUIT::HEARTS),
        Card(Card::RANK::KING, Card::SUIT::HEARTS),
        Card(Card::RANK::TWO, Card::SUIT::CLUBS) };
    cardArr2 royalFlush = { Card(Card::RANK::ACE, Card::SUIT::HEARTS), Card(Card::RANK::THREE, Card::SUIT::CLUBS) };
    cardArr2 twoPair = { Card(Card::RANK::TEN, Card::SUIT::CLUBS), Card(Card::RANK::JACK, Card::SUIT::CLUBS) };

    int royalFlushVal = evaluator.evaluateHand(royalFlush, community);
    int twoPairVal = evaluator.evaluateHand(twoPair, community);
    EXPECT_LT(royalFlushVal, twoPairVal);
}

// 17. Royal Flush beats One Pair
TEST(HandEvaluatorComparison, RoyalFlushBeatsOnePair)
{
    HandEvaluator evaluator;
    cardArr5 community = { Card(Card::RANK::TEN, Card::SUIT::HEARTS),
        Card(Card::RANK::JACK, Card::SUIT::HEARTS),
        Card(Card::RANK::QUEEN, Card::SUIT::HEARTS),
        Card(Card::RANK::KING, Card::SUIT::HEARTS),
        Card(Card::RANK::TWO, Card::SUIT::CLUBS) };
    cardArr2 royalFlush = { Card(Card::RANK::ACE, Card::SUIT::HEARTS), Card(Card::RANK::FOUR, Card::SUIT::CLUBS) };
    cardArr2 onePair = { Card(Card::RANK::THREE, Card::SUIT::DIAMONDS), Card(Card::RANK::THREE, Card::SUIT::SPADES) };

    int royalFlushVal = evaluator.evaluateHand(royalFlush, community);
    int onePairVal = evaluator.evaluateHand(onePair, community);
    EXPECT_LT(royalFlushVal, onePairVal);
}

// 18. Royal Flush beats High Card
TEST(HandEvaluatorComparison, RoyalFlushBeatsHighCard)
{
    HandEvaluator evaluator;
    cardArr5 community = { Card(Card::RANK::TEN, Card::SUIT::HEARTS),
        Card(Card::RANK::JACK, Card::SUIT::HEARTS),
        Card(Card::RANK::QUEEN, Card::SUIT::HEARTS),
        Card(Card::RANK::KING, Card::SUIT::HEARTS),
        Card(Card::RANK::TWO, Card::SUIT::CLUBS) };
    cardArr2 royalFlush = { Card(Card::RANK::ACE, Card::SUIT::HEARTS), Card(Card::RANK::FOUR, Card::SUIT::CLUBS) };
    cardArr2 highCard = { Card(Card::RANK::EIGHT, Card::SUIT::DIAMONDS), Card(Card::RANK::SEVEN, Card::SUIT::SPADES) };

    int royalFlushVal = evaluator.evaluateHand(royalFlush, community);
    int highCardVal = evaluator.evaluateHand(highCard, community);
    EXPECT_LT(royalFlushVal, highCardVal);
}

// 19. Straight Flush beats Full House
TEST(HandEvaluatorComparison, StraightFlushBeatsFullHouse)
{
    HandEvaluator evaluator;
    cardArr5 community = { Card(Card::RANK::SIX, Card::SUIT::HEARTS),
        Card(Card::RANK::SEVEN, Card::SUIT::HEARTS),
        Card(Card::RANK::EIGHT, Card::SUIT::HEARTS),
        Card(Card::RANK::KING, Card::SUIT::SPADES),
        Card(Card::RANK::KING, Card::SUIT::DIAMONDS) };
    cardArr2 straightFlush = { Card(Card::RANK::FOUR, Card::SUIT::HEARTS), Card(Card::RANK::FIVE, Card::SUIT::HEARTS) };
    cardArr2 fullHouse = { Card(Card::RANK::KING, Card::SUIT::HEARTS), Card(Card::RANK::EIGHT, Card::SUIT::SPADES) };

    int straightFlushVal = evaluator.evaluateHand(straightFlush, community);
    int fullHouseVal = evaluator.evaluateHand(fullHouse, community);
    EXPECT_LT(straightFlushVal, fullHouseVal);
}

// 20. Straight Flush beats Flush
TEST(HandEvaluatorComparison, StraightFlushBeatsFlush)
{
    HandEvaluator evaluator;
    cardArr5 community = { Card(Card::RANK::SIX, Card::SUIT::HEARTS),
        Card(Card::RANK::SEVEN, Card::SUIT::HEARTS),
        Card(Card::RANK::EIGHT, Card::SUIT::HEARTS),
        Card(Card::RANK::TWO, Card::SUIT::CLUBS),
        Card(Card::RANK::THREE, Card::SUIT::DIAMONDS) };
    cardArr2 straightFlush = { Card(Card::RANK::FOUR, Card::SUIT::HEARTS), Card(Card::RANK::FIVE, Card::SUIT::HEARTS) };
    cardArr2 flush = { Card(Card::RANK::NINE, Card::SUIT::HEARTS), Card(Card::RANK::QUEEN, Card::SUIT::HEARTS) };

    int straightFlushVal = evaluator.evaluateHand(straightFlush, community);
    int flushVal = evaluator.evaluateHand(flush, community);
    EXPECT_LT(straightFlushVal, flushVal);
}

// 21. Straight Flush beats Straight
TEST(HandEvaluatorComparison, StraightFlushBeatsStraight)
{
    HandEvaluator evaluator;
    cardArr5 community = { Card(Card::RANK::SEVEN, Card::SUIT::HEARTS),
        Card(Card::RANK::EIGHT, Card::SUIT::HEARTS),
        Card(Card::RANK::NINE, Card::SUIT::HEARTS),
        Card(Card::RANK::FOUR, Card::SUIT::CLUBS),
        Card(Card::RANK::TWO, Card::SUIT::DIAMONDS) };
    cardArr2 straightFlush = { Card(Card::RANK::FIVE, Card::SUIT::HEARTS), Card(Card::RANK::SIX, Card::SUIT::HEARTS) };
    cardArr2 straight = { Card(Card::RANK::TEN, Card::SUIT::CLUBS), Card(Card::RANK::JACK, Card::SUIT::CLUBS) };

    int straightFlushVal = evaluator.evaluateHand(straightFlush, community);
    int straightVal = evaluator.evaluateHand(straight, community);
    EXPECT_LT(straightFlushVal, straightVal);
}

// 22. Straight Flush beats Three‐of‐a‐Kind
TEST(HandEvaluatorComparison, StraightFlushBeatsThreeOfAKind)
{
    HandEvaluator evaluator;
    cardArr5 community = { Card(Card::RANK::SEVEN, Card::SUIT::HEARTS),
        Card(Card::RANK::EIGHT, Card::SUIT::HEARTS),
        Card(Card::RANK::NINE, Card::SUIT::HEARTS),
        Card(Card::RANK::FOUR, Card::SUIT::CLUBS),
        Card(Card::RANK::TWO, Card::SUIT::DIAMONDS) };
    cardArr2 straightFlush = { Card(Card::RANK::FIVE, Card::SUIT::HEARTS), Card(Card::RANK::SIX, Card::SUIT::HEARTS) };
    cardArr2 trips = { Card(Card::RANK::SEVEN, Card::SUIT::CLUBS), Card(Card::RANK::SEVEN, Card::SUIT::DIAMONDS) };

    int straightFlushVal = evaluator.evaluateHand(straightFlush, community);
    int tripsVal = evaluator.evaluateHand(trips, community);
    EXPECT_LT(straightFlushVal, tripsVal);
}

// 23. Straight Flush beats Two Pair
TEST(HandEvaluatorComparison, StraightFlushBeatsTwoPair)
{
    HandEvaluator evaluator;
    cardArr5 community = { Card(Card::RANK::SEVEN, Card::SUIT::HEARTS),
        Card(Card::RANK::EIGHT, Card::SUIT::HEARTS),
        Card(Card::RANK::NINE, Card::SUIT::HEARTS),
        Card(Card::RANK::FOUR, Card::SUIT::CLUBS),
        Card(Card::RANK::TWO, Card::SUIT::DIAMONDS) };
    cardArr2 straightFlush = { Card(Card::RANK::FIVE, Card::SUIT::HEARTS), Card(Card::RANK::SIX, Card::SUIT::HEARTS) };
    cardArr2 twoPair = { Card(Card::RANK::SEVEN, Card::SUIT::CLUBS), Card(Card::RANK::EIGHT, Card::SUIT::CLUBS) };

    int straightFlushVal = evaluator.evaluateHand(straightFlush, community);
    int twoPairVal = evaluator.evaluateHand(twoPair, community);
    EXPECT_LT(straightFlushVal, twoPairVal);
}

// 24. Straight Flush beats One Pair
TEST(HandEvaluatorComparison, StraightFlushBeatsOnePair)
{
    HandEvaluator evaluator;
    cardArr5 community = { Card(Card::RANK::SEVEN, Card::SUIT::HEARTS),
        Card(Card::RANK::EIGHT, Card::SUIT::HEARTS),
        Card(Card::RANK::NINE, Card::SUIT::HEARTS),
        Card(Card::RANK::FOUR, Card::SUIT::CLUBS),
        Card(Card::RANK::TWO, Card::SUIT::DIAMONDS) };
    cardArr2 straightFlush = { Card(Card::RANK::FIVE, Card::SUIT::HEARTS), Card(Card::RANK::SIX, Card::SUIT::HEARTS) };
    cardArr2 onePair = { Card(Card::RANK::SEVEN, Card::SUIT::CLUBS), Card(Card::RANK::THREE, Card::SUIT::DIAMONDS) };

    int straightFlushVal = evaluator.evaluateHand(straightFlush, community);
    int onePairVal = evaluator.evaluateHand(onePair, community);
    EXPECT_LT(straightFlushVal, onePairVal);
}

// 25. Straight Flush beats High Card
TEST(HandEvaluatorComparison, StraightFlushBeatsHighCard)
{
    HandEvaluator evaluator;
    cardArr5 community = { Card(Card::RANK::SEVEN, Card::SUIT::HEARTS),
        Card(Card::RANK::EIGHT, Card::SUIT::HEARTS),
        Card(Card::RANK::NINE, Card::SUIT::HEARTS),
        Card(Card::RANK::FOUR, Card::SUIT::CLUBS),
        Card(Card::RANK::TWO, Card::SUIT::DIAMONDS) };
    cardArr2 straightFlush = { Card(Card::RANK::FIVE, Card::SUIT::HEARTS), Card(Card::RANK::SIX, Card::SUIT::HEARTS) };
    cardArr2 highCard = { Card(Card::RANK::ACE, Card::SUIT::CLUBS), Card(Card::RANK::THREE, Card::SUIT::CLUBS) };

    int straightFlushVal = evaluator.evaluateHand(straightFlush, community);
    int highCardVal = evaluator.evaluateHand(highCard, community);
    EXPECT_LT(straightFlushVal, highCardVal);
}

// 26. Four‐of‐a‐Kind beats Flush
TEST(HandEvaluatorComparison, QuadsBeatsFlush)
{
    HandEvaluator evaluator;
    cardArr5 community = { Card(Card::RANK::NINE, Card::SUIT::SPADES),
        Card(Card::RANK::NINE, Card::SUIT::HEARTS),
        Card(Card::RANK::NINE, Card::SUIT::DIAMONDS),
        Card(Card::RANK::FOUR, Card::SUIT::HEARTS),
        Card(Card::RANK::SEVEN, Card::SUIT::HEARTS) };
    cardArr2 quads = { Card(Card::RANK::NINE, Card::SUIT::CLUBS), Card(Card::RANK::TWO, Card::SUIT::SPADES) };
    cardArr2 flush = { Card(Card::RANK::ACE, Card::SUIT::HEARTS), Card(Card::RANK::KING, Card::SUIT::HEARTS) };

    int quadsVal = evaluator.evaluateHand(quads, community);
    int flushVal = evaluator.evaluateHand(flush, community);
    EXPECT_LT(quadsVal, flushVal);
}

// 27. Four‐of‐a‐Kind beats Straight
TEST(HandEvaluatorComparison, QuadsBeatsStraight)
{
    HandEvaluator evaluator;
    cardArr5 community = { Card(Card::RANK::NINE, Card::SUIT::SPADES),
        Card(Card::RANK::NINE, Card::SUIT::HEARTS),
        Card(Card::RANK::NINE, Card::SUIT::DIAMONDS),
        Card(Card::RANK::EIGHT, Card::SUIT::SPADES),
        Card(Card::RANK::SEVEN, Card::SUIT::DIAMONDS) };
    cardArr2 quads = { Card(Card::RANK::NINE, Card::SUIT::CLUBS), Card(Card::RANK::TWO, Card::SUIT::CLUBS) };
    cardArr2 straight = { Card(Card::RANK::TEN, Card::SUIT::CLUBS), Card(Card::RANK::JACK, Card::SUIT::CLUBS) };

    int quadsVal = evaluator.evaluateHand(quads, community);
    int straightVal = evaluator.evaluateHand(straight, community);
    EXPECT_LT(quadsVal, straightVal);
}

// 28. Four‐of‐a‐Kind beats Three‐of‐a‐Kind
TEST(HandEvaluatorComparison, QuadsBeatsThreeOfAKind)
{
    HandEvaluator evaluator;
    cardArr5 community = { Card(Card::RANK::FIVE, Card::SUIT::CLUBS),
        Card(Card::RANK::FIVE, Card::SUIT::DIAMONDS),
        Card(Card::RANK::FIVE, Card::SUIT::HEARTS),
        Card(Card::RANK::EIGHT, Card::SUIT::SPADES),
        Card(Card::RANK::SEVEN, Card::SUIT::DIAMONDS) };
    cardArr2 quads = { Card(Card::RANK::FIVE, Card::SUIT::SPADES), Card(Card::RANK::TWO, Card::SUIT::CLUBS) };
    cardArr2 trips = { Card(Card::RANK::EIGHT, Card::SUIT::CLUBS), Card(Card::RANK::EIGHT, Card::SUIT::DIAMONDS) };

    int quadsVal = evaluator.evaluateHand(quads, community);
    int tripsVal = evaluator.evaluateHand(trips, community);
    EXPECT_LT(quadsVal, tripsVal);
}

// 29. Four‐of‐a‐Kind beats Two Pair
TEST(HandEvaluatorComparison, QuadsBeatsTwoPair)
{
    HandEvaluator evaluator;
    cardArr5 community = { Card(Card::RANK::FOUR, Card::SUIT::CLUBS),
        Card(Card::RANK::FOUR, Card::SUIT::DIAMONDS),
        Card(Card::RANK::FOUR, Card::SUIT::HEARTS),
        Card(Card::RANK::NINE, Card::SUIT::SPADES),
        Card(Card::RANK::SEVEN, Card::SUIT::DIAMONDS) };
    cardArr2 quads = { Card(Card::RANK::FOUR, Card::SUIT::SPADES), Card(Card::RANK::TWO, Card::SUIT::CLUBS) };
    cardArr2 twoPair = { Card(Card::RANK::NINE, Card::SUIT::CLUBS), Card(Card::RANK::SEVEN, Card::SUIT::CLUBS) };

    int quadsVal = evaluator.evaluateHand(quads, community);
    int twoPairVal = evaluator.evaluateHand(twoPair, community);
    EXPECT_LT(quadsVal, twoPairVal);
}

// 30. Four‐of‐a‐Kind beats One Pair
TEST(HandEvaluatorComparison, QuadsBeatsOnePair)
{
    HandEvaluator evaluator;
    cardArr5 community = { Card(Card::RANK::THREE, Card::SUIT::CLUBS),
        Card(Card::RANK::THREE, Card::SUIT::DIAMONDS),
        Card(Card::RANK::EIGHT, Card::SUIT::HEARTS),
        Card(Card::RANK::TEN, Card::SUIT::SPADES),
        Card(Card::RANK::QUEEN, Card::SUIT::DIAMONDS) };
    cardArr2 quads = { Card(Card::RANK::THREE, Card::SUIT::HEARTS), Card(Card::RANK::THREE, Card::SUIT::SPADES) };
    cardArr2 onePair = { Card(Card::RANK::FOUR, Card::SUIT::HEARTS), Card(Card::RANK::SIX, Card::SUIT::HEARTS) };

    int quadsVal = evaluator.evaluateHand(quads, community);
    int onePairVal = evaluator.evaluateHand(onePair, community);
    EXPECT_LT(quadsVal, onePairVal);
}

