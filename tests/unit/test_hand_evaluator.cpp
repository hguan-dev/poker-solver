#include "Card.hpp"
#include "HandEvaluator.hpp"
#include <gtest/gtest.h>

using cardVec = std::vector<Card>;

//
// Basic Tests
//
TEST(HandEvaluatorTest, RoyalFlush)
{
    HandEvaluator evaluator;
    cardVec hand = { Card('T', 'H'), Card('J', 'H') };
    cardVec communityCards = { Card('Q', 'H'), Card('K', 'H'), Card('A', 'H'), Card('4', 'S'), Card('9', 'H') };

    auto result = evaluator.evaluateHand(hand, communityCards);
    ASSERT_FALSE(result.identifier.empty()) << "Identifier should not be empty for Royal Flush";

    EXPECT_EQ(result.rank, HandEvaluator::HandRank::ROYAL_FLUSH);
    EXPECT_EQ(result.identifier[0], 14);
}

TEST(HandEvaluatorTest, StraightFlush)
{
    HandEvaluator evaluator;
    cardVec hand = { Card('9', 'C'), Card('T', 'C') };
    cardVec communityCards = { Card('J', 'C'), Card('Q', 'C'), Card('K', 'C'), Card('2', 'H'), Card('3', 'H') };

    auto result = evaluator.evaluateHand(hand, communityCards);
    ASSERT_FALSE(result.identifier.empty()) << "Identifier should not be empty for Straight Flush";

    EXPECT_EQ(result.rank, HandEvaluator::HandRank::STRAIGHT_FLUSH);
    EXPECT_EQ(result.identifier[0], 13);
}

TEST(HandEvaluatorTest, QuadsOverQuads)
{
    HandEvaluator evaluator;
    // Hand 1 is Quad 9's
    cardVec hand1 = { Card('9', 'C'), Card('9', 'D') };
    // Hand 2 is Quad 10's
    cardVec hand2 = { Card('T', 'C'), Card('T', 'D') };
    cardVec communityCards = { Card('9', 'H'), Card('9', 'S'), Card('T', 'H'), Card('T', 'S'), Card('2', 'H') };

    auto result1 = evaluator.evaluateHand(hand1, communityCards);
    auto result2 = evaluator.evaluateHand(hand2, communityCards);
    auto fastresult1 = evaluator.fastEvaluateHand(hand1, communityCards);
    auto fastresult2 = evaluator.fastEvaluateHand(hand2, communityCards);

    EXPECT_EQ(result1.highCards[0], 10);
    EXPECT_EQ(result2.highCards[0], 9);

    ASSERT_FALSE(result1.identifier.empty()) << "Identifier for result1 should not be empty";
    ASSERT_FALSE(result2.identifier.empty()) << "Identifier for result2 should not be empty";

    EXPECT_LT(result1, result2);
    EXPECT_GT(fastresult1, fastresult2);
}

TEST(HandEvaluatorTest, Quads)
{
    HandEvaluator evaluator;
    cardVec hand = { Card('9', 'C'), Card('9', 'D') };
    cardVec communityCards = { Card('9', 'H'), Card('9', 'S'), Card('K', 'C'), Card('4', 'H'), Card('6', 'D') };

    auto result = evaluator.evaluateHand(hand, communityCards);
    ASSERT_FALSE(result.identifier.empty()) << "Identifier should not be empty for Quads";
    ASSERT_FALSE(result.highCards.empty()) << "HighCards should not be empty for Quads";

    EXPECT_EQ(result.rank, HandEvaluator::HandRank::FOUR_OF_A_KIND);
    EXPECT_EQ(result.identifier[0], 9);
    EXPECT_EQ(result.highCards[0], 13);
}

TEST(HandEvaluatorTest, FullHouse)
{
    HandEvaluator evaluator;
    cardVec hand = { Card('T', 'C'), Card('T', 'D') };
    cardVec communityCards = { Card('T', 'H'), Card('J', 'S'), Card('J', 'C'), Card('4', 'H'), Card('9', 'D') };

    auto result = evaluator.evaluateHand(hand, communityCards);
    ASSERT_FALSE(result.identifier.empty()) << "Identifier should not be empty for Full House";

    EXPECT_EQ(result.rank, HandEvaluator::HandRank::FULL_HOUSE);
    EXPECT_EQ(result.identifier[0], 10);
    EXPECT_EQ(result.identifier[1], 11);
    EXPECT_EQ(result.highCards.size(), 0);
}

TEST(HandEvaluatorTest, Flush)
{
    HandEvaluator evaluator;
    cardVec hand = { Card('2', 'H'), Card('5', 'H') };
    cardVec communityCards = { Card('9', 'H'), Card('J', 'H'), Card('K', 'H'), Card('3', 'D'), Card('8', 'S') };

    auto result = evaluator.evaluateHand(hand, communityCards);
    ASSERT_FALSE(result.highCards.empty()) << "HighCards should not be empty for Flush";

    EXPECT_EQ(result.rank, HandEvaluator::HandRank::FLUSH);
    EXPECT_EQ(result.identifier[0], 13);
    EXPECT_EQ(result.highCards.size(), 5);
    EXPECT_EQ(result.highCards[0], 13);
    EXPECT_EQ(result.highCards[1], 11);
    EXPECT_EQ(result.highCards[2], 9);
    EXPECT_EQ(result.highCards[3], 5);
    EXPECT_EQ(result.highCards[4], 2);
}

TEST(HandEvaluatorTest, Straight)
{
    HandEvaluator evaluator;
    cardVec hand = { Card('2', 'D'), Card('3', 'C') };
    cardVec communityCards = { Card('4', 'H'), Card('5', 'S'), Card('6', 'C'), Card('K', 'H'), Card('7', 'D') };

    auto result = evaluator.evaluateHand(hand, communityCards);
    ASSERT_FALSE(result.identifier.empty()) << "Identifier should not be empty for Straight";

    EXPECT_EQ(result.rank, HandEvaluator::HandRank::STRAIGHT);
    EXPECT_EQ(result.identifier[0], 7);
}

TEST(HandEvaluatorTest, AceHighStraight)
{
    HandEvaluator evaluator;
    cardVec hand = { Card('A', 'D'), Card('2', 'C') };
    cardVec communityCards = { Card('K', 'H'), Card('Q', 'S'), Card('T', 'C'), Card('3', 'H'), Card('J', 'D') };

    auto result = evaluator.evaluateHand(hand, communityCards);
    ASSERT_FALSE(result.identifier.empty()) << "Identifier should not be empty for Straight";

    EXPECT_EQ(result.rank, HandEvaluator::HandRank::STRAIGHT);
    EXPECT_EQ(result.identifier[0], 14);
}

TEST(HandEvaluatorTest, AceLowStraight)
{
    HandEvaluator evaluator;
    cardVec hand = { Card('2', 'D'), Card('A', 'C') };
    cardVec communityCards = { Card('4', 'H'), Card('5', 'S'), Card('3', 'C'), Card('K', 'H'), Card('7', 'D') };

    auto result = evaluator.evaluateHand(hand, communityCards);
    ASSERT_FALSE(result.identifier.empty()) << "Identifier should not be empty for Straight";

    EXPECT_EQ(result.rank, HandEvaluator::HandRank::STRAIGHT);
    EXPECT_EQ(result.identifier[0], 5);
}

TEST(HandEvaluatorTest, ThreeOfAKind)
{
    HandEvaluator evaluator;
    cardVec hand = { Card('T', 'C'), Card('T', 'D') };
    cardVec communityCards = { Card('T', 'H'), Card('J', 'S'), Card('K', 'C') };

    auto result = evaluator.evaluateHand(hand, communityCards);
    EXPECT_EQ(result.rank, HandEvaluator::HandRank::THREE_OF_A_KIND);
    EXPECT_EQ(result.identifier[0], 10);
    EXPECT_EQ(result.highCards[0], 13);
    EXPECT_EQ(result.highCards[1], 11);
}

TEST(HandEvaluatorTest, TwoPair)
{
    HandEvaluator evaluator;
    cardVec hand = { Card('T', 'C'), Card('T', 'D') };
    cardVec communityCards = { Card('J', 'H'), Card('J', 'S'), Card('K', 'C') };

    auto result = evaluator.evaluateHand(hand, communityCards);
    EXPECT_EQ(result.rank, HandEvaluator::HandRank::TWO_PAIR);
    EXPECT_EQ(result.identifier[0], 11);
    EXPECT_EQ(result.identifier[1], 10);
    EXPECT_EQ(result.highCards[0], 13);
}

TEST(HandEvaluatorTest, TwoPairCounterfeited)
{
    HandEvaluator evaluator;
    cardVec hand = { Card('T', 'C'), Card('T', 'D') };
    cardVec communityCards = { Card('J', 'H'), Card('J', 'S'), Card('K', 'C'), Card('K', 'H'), Card('8', 'C') };

    auto result = evaluator.evaluateHand(hand, communityCards);
    EXPECT_EQ(result.rank, HandEvaluator::HandRank::TWO_PAIR);
    EXPECT_EQ(result.identifier[0], 13);
    EXPECT_EQ(result.identifier[1], 11);
    EXPECT_EQ(result.highCards[0], 10);
}

TEST(HandEvaluatorTest, OnePair)
{
    HandEvaluator evaluator;
    cardVec hand = { Card('T', 'C'), Card('T', 'D') };
    cardVec communityCards = { Card('J', 'H'), Card('Q', 'S'), Card('K', 'C') };

    auto result = evaluator.evaluateHand(hand, communityCards);
    EXPECT_EQ(result.rank, HandEvaluator::HandRank::ONE_PAIR);
    EXPECT_EQ(result.identifier[0], 10);
    EXPECT_EQ(result.highCards[0], 13);
    EXPECT_EQ(result.highCards[1], 12);
    EXPECT_EQ(result.highCards[2], 11);
}

TEST(HandEvaluatorTest, HighCard)
{
    HandEvaluator evaluator;
    cardVec hand = { Card('2', 'D'), Card('5', 'C') };
    cardVec communityCards = { Card('7', 'H'), Card('9', 'S'), Card('J', 'C') };

    auto result = evaluator.evaluateHand(hand, communityCards);
    EXPECT_EQ(result.rank, HandEvaluator::HandRank::HIGH_CARD);
    EXPECT_EQ(result.identifier[0], 11);
    EXPECT_EQ(result.highCards[0], 9);
    EXPECT_EQ(result.highCards[1], 7);
    EXPECT_EQ(result.highCards[2], 5);
    EXPECT_EQ(result.highCards[3], 2);
}

//
// Different Kicker Tests
//
TEST(HandEvaluatorTest, TwoPairsWithDifferentKickers)
{
    HandEvaluator evaluator;

    cardVec communityCards = { Card('K', 'H'), Card('7', 'D'), Card('3', 'C'), Card('3', 'S'), Card('2', 'H') };

    cardVec hand1 = { Card('K', 'D'), Card('A', 'C') };
    cardVec hand2 = { Card('K', 'C'), Card('Q', 'S') };

    auto result1 = evaluator.evaluateHand(hand1, communityCards);
    auto result2 = evaluator.evaluateHand(hand2, communityCards);
    auto fastresult1 = evaluator.fastEvaluateHand(hand1, communityCards);
    auto fastresult2 = evaluator.fastEvaluateHand(hand2, communityCards);
    EXPECT_EQ(result1.rank, HandEvaluator::HandRank::TWO_PAIR);
    EXPECT_EQ(result2.rank, HandEvaluator::HandRank::TWO_PAIR);

    EXPECT_GT(result1, result2);
    EXPECT_LT(fastresult1, fastresult2);
}

TEST(HandEvaluatorTest, FullHouseTripsTiebreaker)
{
    HandEvaluator evaluator;

    cardVec communityCards = { Card('Q', 'C'), Card('J', 'S'), Card('J', 'D'), Card('4', 'H'), Card('2', 'C') };

    // Queens over Jacks
    cardVec hand1 = { Card('Q', 'H'), Card('Q', 'D') };

    // Jacks over Queens
    cardVec hand2 = { Card('J', 'C'), Card('Q', 'D') };

    auto result1 = evaluator.evaluateHand(hand1, communityCards);
    auto result2 = evaluator.evaluateHand(hand2, communityCards);

    auto fastresult1 = evaluator.fastEvaluateHand(hand1, communityCards);
    auto fastresult2 = evaluator.fastEvaluateHand(hand2, communityCards);

    EXPECT_EQ(result1.rank, HandEvaluator::HandRank::FULL_HOUSE);
    EXPECT_EQ(result2.rank, HandEvaluator::HandRank::FULL_HOUSE);

    EXPECT_GT(result1, result2);
    EXPECT_LT(fastresult1, fastresult2);
}

TEST(HandEvaluatorTest, FullHousePairTiebreaker)
{
    HandEvaluator evaluator;

    cardVec communityCards = { Card('Q', 'C'), Card('Q', 'S'), Card('9', 'D'), Card('7', 'H'), Card('2', 'C') };

    // Queens over Nines
    cardVec hand1 = { Card('9', 'H'), Card('Q', 'D') };

    // Queens over Sevens
    cardVec hand2 = { Card('Q', 'H'), Card('7', 'S') };

    auto result1 = evaluator.evaluateHand(hand1, communityCards);
    auto result2 = evaluator.evaluateHand(hand2, communityCards);
    auto fastresult1 = evaluator.fastEvaluateHand(hand1, communityCards);
    auto fastresult2 = evaluator.fastEvaluateHand(hand2, communityCards);
    EXPECT_EQ(result1.rank, HandEvaluator::HandRank::FULL_HOUSE);
    EXPECT_EQ(result2.rank, HandEvaluator::HandRank::FULL_HOUSE);

    EXPECT_GT(result1, result2);
    EXPECT_LT(fastresult1, fastresult2);
}

TEST(HandEvaluatorTest, FlushTiebreaker)
{
    HandEvaluator evaluator;

    cardVec communityCards = { Card('A', 'H'), Card('K', 'H'), Card('7', 'H'), Card('6', 'D'), Card('2', 'S') };

    // Tiebreaker card is 4
    cardVec hand1 = { Card('3', 'H'), Card('4', 'H') };

    // Tiebreaker card is 5
    cardVec hand2 = { Card('2', 'H'), Card('5', 'H') };

    auto result1 = evaluator.evaluateHand(hand1, communityCards);
    auto result2 = evaluator.evaluateHand(hand2, communityCards);

    auto fastresult1 = evaluator.fastEvaluateHand(hand1, communityCards);
    auto fastresult2 = evaluator.fastEvaluateHand(hand2, communityCards);

    ASSERT_FALSE(result1.identifier.empty());
    ASSERT_FALSE(result2.identifier.empty());

    EXPECT_EQ(result1.rank, HandEvaluator::HandRank::FLUSH);
    EXPECT_EQ(result2.rank, HandEvaluator::HandRank::FLUSH);

    EXPECT_LT(result1, result2);
    EXPECT_GT(fastresult1, fastresult2);
}

TEST(HandEvaluatorTest, FiveCardStraightFlush)
{
    HandEvaluator evaluator;
    cardVec hand = { Card('6', 'D'), Card('7', 'D') };
    cardVec communityCards = { Card('8', 'D'), Card('9', 'D'), Card('T', 'D') };

    auto result = evaluator.evaluateHand(hand, communityCards);
    EXPECT_EQ(result.rank, HandEvaluator::HandRank::STRAIGHT_FLUSH);
    EXPECT_EQ(result.identifier[0], 10);
}

TEST(HandEvaluatorTest, FourOfAKindVsFullHouse)
{
    HandEvaluator evaluator;
    cardVec communityCards = { Card('A', 'H'), Card('A', 'D'), Card('A', 'C'), Card('K', 'D'), Card('K', 'H') };

    // Four Aces
    cardVec hand1 = { Card('A', 'S'), Card('Q', 'C') };

    // Full House (Kings full of Aces)
    cardVec hand2 = { Card('K', 'S'), Card('2', 'C') };

    auto result1 = evaluator.evaluateHand(hand1, communityCards);
    auto result2 = evaluator.evaluateHand(hand2, communityCards);
    auto fastresult1 = evaluator.fastEvaluateHand(hand1, communityCards);
    auto fastresult2 = evaluator.fastEvaluateHand(hand2, communityCards);


    EXPECT_GT(result1, result2);
    EXPECT_LT(fastresult1, fastresult2);
}

TEST(HandEvaluatorTest, StraightVsFlush)
{
    HandEvaluator evaluator;
    cardVec communityCards = { Card('7', 'H'), Card('8', 'H'), Card('9', 'H'), Card('T', 'D'), Card('J', 'S') };

    // Straight
    cardVec hand1 = { Card('Q', 'D'), Card('K', 'C') };

    // Flush
    cardVec hand2 = { Card('2', 'H'), Card('A', 'H') };

    auto result1 = evaluator.evaluateHand(hand1, communityCards);
    auto result2 = evaluator.evaluateHand(hand2, communityCards);

    auto fastresult1 = evaluator.fastEvaluateHand(hand1, communityCards);
    auto fastresult2 = evaluator.fastEvaluateHand(hand2, communityCards);

    EXPECT_LT(result1, result2);
    EXPECT_GT(fastresult1, fastresult2);
}

TEST(HandEvaluatorTest, SameRankDifferentSuits)
{
    HandEvaluator evaluator;
    // The suits shouldn't affect the ranking
    cardVec hand1 = { Card('A', 'H'), Card('K', 'H') };
    cardVec hand2 = { Card('A', 'S'), Card('K', 'S') };
    cardVec communityCards = { Card('Q', 'D'), Card('J', 'C'), Card('T', 'H'), Card('9', 'S'), Card('8', 'D') };

    auto result1 = evaluator.evaluateHand(hand1, communityCards);
    auto result2 = evaluator.evaluateHand(hand2, communityCards);

    EXPECT_EQ(result1.rank, result2.rank);
    EXPECT_EQ(result1, result2);
}

TEST(HandEvaluatorTest, TieFullHouse)
{
    HandEvaluator evaluator;
    cardVec communityCards = { Card('Q', 'D'), Card('Q', 'S'), Card('Q', 'H'), Card('J', 'D'), Card('J', 'H') };

    cardVec hand1 = { Card('A', 'S'), Card('K', 'C') };
    cardVec hand2 = { Card('A', 'H'), Card('K', 'D') };

    auto result1 = evaluator.evaluateHand(hand1, communityCards);
    auto result2 = evaluator.evaluateHand(hand2, communityCards);

    EXPECT_EQ(result1.rank, HandEvaluator::HandRank::FULL_HOUSE);
    EXPECT_EQ(result2.rank, HandEvaluator::HandRank::FULL_HOUSE);
    EXPECT_EQ(result1, result2);
}

TEST(HandEvaluatorTest, LowStraightWithHighCard)
{
    HandEvaluator evaluator;
    cardVec hand = { Card('A', 'H'), Card('2', 'D') };
    cardVec communityCards = { Card('3', 'S'), Card('4', 'C'), Card('5', 'H'), Card('K', 'D'), Card('Q', 'S') };

    auto result = evaluator.evaluateHand(hand, communityCards);

    EXPECT_EQ(result.rank, HandEvaluator::HandRank::STRAIGHT);
    EXPECT_EQ(result.identifier[0], 5);// Highest card in the straight is 5
}

TEST(HandEvaluatorTest, MultipleFlushes)
{
    HandEvaluator evaluator;
    cardVec communityCards = { Card('2', 'S'), Card('5', 'S'), Card('7', 'S'), Card('9', 'S'), Card('J', 'H') };

    // Higher flush
    cardVec hand1 = { Card('A', 'S'), Card('K', 'D') };

    // Lower flush
    cardVec hand2 = { Card('3', 'S'), Card('Q', 'D') };

    auto result1 = evaluator.evaluateHand(hand1, communityCards);
    auto result2 = evaluator.evaluateHand(hand2, communityCards);
    auto fastresult1 = evaluator.fastEvaluateHand(hand1, communityCards);
    auto fastresult2 = evaluator.fastEvaluateHand(hand2, communityCards);


    EXPECT_EQ(result1.rank, HandEvaluator::HandRank::FLUSH);
    EXPECT_EQ(result2.rank, HandEvaluator::HandRank::FLUSH);
    EXPECT_GT(result1, result2);
    EXPECT_LT(fastresult1, fastresult2);
}
