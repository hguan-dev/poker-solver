#include "Card.hpp"
#include <gtest/gtest.h>

TEST(CardTest, ValidCard)
{
    Card card(Card::RANK::TEN, Card::SUIT::HEARTS);
    EXPECT_EQ(card.getRank(), Card::RANK::TEN);
    EXPECT_EQ(card.getSuit(), Card::SUIT::HEARTS);
    EXPECT_EQ(card.getValue(), 10);
}

TEST(CardTest, AceValue)
{
    Card card(Card::RANK::ACE, Card::SUIT::SPADES);
    EXPECT_EQ(card.getValue(), 14);
}

TEST(CardTest, KingValue)
{
    Card card(Card::RANK::KING, Card::SUIT::DIAMONDS);
    EXPECT_EQ(card.getValue(), 13);
}

TEST(CardTest, EqualityOperator)
{
    Card card1(Card::RANK::TEN, Card::SUIT::HEARTS);
    Card card2(Card::RANK::TEN, Card::SUIT::HEARTS);
    EXPECT_EQ(card1, card2);
}

TEST(CardTest, InequalityOperator)
{
    Card card1(Card::RANK::TEN, Card::SUIT::HEARTS);
    Card card2(Card::RANK::JACK, Card::SUIT::HEARTS);
    EXPECT_NE(card1, card2);
}

TEST(CardTest, LowerBound)
{
    Card card(Card::RANK::TWO, Card::SUIT::HEARTS);
    EXPECT_EQ(card.getRank(), Card::RANK::TWO);
    EXPECT_EQ(card.getSuit(), Card::SUIT::HEARTS);
    EXPECT_EQ(card.getValue(), 2);
}

TEST(CardTest, JackValue)
{
    Card card(Card::RANK::JACK, Card::SUIT::CLUBS);
    EXPECT_EQ(card.getValue(), 11);
    EXPECT_EQ(card.getRank(), Card::RANK::JACK);
    EXPECT_EQ(card.getSuit(), Card::SUIT::CLUBS);
}

TEST(CardTest, QueenValue)
{
    Card card(Card::RANK::QUEEN, Card::SUIT::DIAMONDS);
    EXPECT_EQ(card.getValue(), 12);
}

TEST(CardTest, NumericCard)
{
    Card card(Card::RANK::SEVEN, Card::SUIT::SPADES);
    EXPECT_EQ(card.getRank(), Card::RANK::SEVEN);
    EXPECT_EQ(card.getSuit(), Card::SUIT::SPADES);
    EXPECT_EQ(card.getValue(), 7);
}
TEST(CardTest, InequalitySuit)
{
    Card card1(Card::RANK::TEN, Card::SUIT::HEARTS);
    Card card2(Card::RANK::TEN, Card::SUIT::SPADES);
    EXPECT_NE(card1, card2);
}

TEST(CardTest, UpperBound)
{
    Card card(Card::RANK::ACE, Card::SUIT::CLUBS);
    EXPECT_EQ(card.getRank(), Card::RANK::ACE);
    EXPECT_EQ(card.getSuit(), Card::SUIT::CLUBS);
    EXPECT_EQ(card.getValue(), 14);
}
