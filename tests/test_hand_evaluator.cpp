#include "Card.hpp"
#include "HandEvaluator.hpp"
#include <gtest/gtest.h>

using cardVec = std::vector<Card>;

TEST(HandEvaluatorTest, RoyalFlush)
{
    HandEvaluator evaluator;
    cardVec hand = { Card("T", "Hearts"), Card("J", "Hearts") };
    cardVec communityCards = {
        Card("Q", "Hearts"), Card("K", "Hearts"), Card("A", "Hearts"), Card("4", "Spades"), Card("9", "Hearts")
    };

    auto result = evaluator.evaluateHand(hand, communityCards);
    EXPECT_EQ(result.rank, HandEvaluator::ROYAL_FLUSH);
    EXPECT_EQ(result.identifier[0], 14);

    int fast_result = evaluator.fastEvaluateHand(hand, communityCards);
    EXPECT_GT(fast_result, 0);
}

TEST(HandEvaluatorTest, StraightFlush)
{
    HandEvaluator evaluator;
    cardVec hand = { Card("9", "Clubs"), Card("T", "Clubs") };
    cardVec communityCards = {
        Card("J", "Clubs"), Card("Q", "Clubs"), Card("K", "Clubs"), Card("2", "Hearts"), Card("3", "Hearts")
    };

    auto result = evaluator.evaluateHand(hand, communityCards);
    EXPECT_EQ(result.rank, HandEvaluator::STRAIGHT_FLUSH);
    EXPECT_EQ(result.identifier[0], 13);

    int fast_result = evaluator.fastEvaluateHand(hand, communityCards);
    EXPECT_GT(fast_result, 0);
}

TEST(HandEvaluatorTest, FourOfAKind)
{
    HandEvaluator evaluator;
    cardVec hand = { Card("J", "Diamonds"), Card("J", "Spades") };
    cardVec communityCards = {
        Card("J", "Clubs"), Card("J", "Hearts"), Card("A", "Diamonds"), Card("7", "Clubs"), Card("2", "Hearts")
    };

    auto result = evaluator.evaluateHand(hand, communityCards);
    EXPECT_EQ(result.rank, HandEvaluator::FOUR_OF_A_KIND);
    EXPECT_EQ(result.identifier[0], 11);
    EXPECT_EQ(result.highCards[0], 14);

    int fast_result = evaluator.fastEvaluateHand(hand, communityCards);
    EXPECT_GT(fast_result, 0);
}

TEST(HandEvaluatorTest, FullHouse)
{
    HandEvaluator evaluator;
    cardVec hand = { Card("K", "Diamonds"), Card("K", "Spades") };
    cardVec communityCards = {
        Card("K", "Hearts"), Card("9", "Clubs"), Card("9", "Diamonds"), Card("4", "Hearts"), Card("2", "Clubs")
    };

    auto result = evaluator.evaluateHand(hand, communityCards);
    EXPECT_EQ(result.rank, HandEvaluator::FULL_HOUSE);
    EXPECT_EQ(result.identifier[0], 13);
    EXPECT_EQ(result.identifier[1], 9);

    int fast_result = evaluator.fastEvaluateHand(hand, communityCards);
    EXPECT_GT(fast_result, 0);
}

TEST(HandEvaluatorTest, RandomMixedHands)
{
    HandEvaluator evaluator;
    cardVec hand1 = { Card("6", "Hearts"), Card("8", "Spades") };
    cardVec hand2 = { Card("10", "Diamonds"), Card("J", "Clubs") };
    cardVec communityCards = {
        Card("7", "Hearts"), Card("9", "Spades"), Card("Q", "Diamonds"), Card("K", "Clubs"), Card("A", "Hearts")
    };

    auto result1 = evaluator.evaluateHand(hand1, communityCards);
    auto result2 = evaluator.evaluateHand(hand2, communityCards);
    EXPECT_LT(result1, result2);

    int fast_result1 = evaluator.fastEvaluateHand(hand1, communityCards);
    int fast_result2 = evaluator.fastEvaluateHand(hand2, communityCards);
    EXPECT_LT(fast_result1, fast_result2);
}

TEST(HandEvaluatorTest, DifferentKickerComparison)
{
    HandEvaluator evaluator;
    cardVec hand1 = { Card("10", "Diamonds"), Card("A", "Spades") };
    cardVec hand2 = { Card("10", "Clubs"), Card("K", "Hearts") };
    cardVec communityCards = {
        Card("10", "Hearts"), Card("9", "Diamonds"), Card("5", "Clubs"), Card("4", "Spades"), Card("2", "Hearts")
    };

    auto result1 = evaluator.evaluateHand(hand1, communityCards);
    auto result2 = evaluator.evaluateHand(hand2, communityCards);
    EXPECT_GT(result1, result2);

    int fast_result1 = evaluator.fastEvaluateHand(hand1, communityCards);
    int fast_result2 = evaluator.fastEvaluateHand(hand2, communityCards);
    EXPECT_GT(fast_result1, fast_result2);
}

