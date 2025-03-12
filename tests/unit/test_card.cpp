#include "Card.hpp"
#include <gtest/gtest.h>

TEST(CardTest, ValidCard)
{
    Card card('T', 'H');
    EXPECT_EQ(card.getRank(), 'T');
    EXPECT_EQ(card.getSuit(), 'H');
    EXPECT_EQ(card.getValue(), 10);
}

TEST(CardTest, AceValue)
{
    Card card('A', 'S');
    EXPECT_EQ(card.getValue(), 14);
}

TEST(CardTest, KingValue)
{
    Card card('K', 'D');
    EXPECT_EQ(card.getValue(), 13);
}

TEST(CardTest, ToString)
{
    Card card('Q', 'C');
    EXPECT_EQ(card.toString(), "Q of Clubs");
}

TEST(CardTest, EqualityOperator)
{
    Card card1('T', 'H');
    Card card2('T', 'H');
    EXPECT_EQ(card1, card2);
}

TEST(CardTest, InequalityOperator)
{
    Card card1('T', 'H');
    Card card2('J', 'H');
    EXPECT_NE(card1, card2);
}

TEST(CardTest, LowerBound)
{
    Card card('2', 'H');
    EXPECT_EQ(card.getRank(), '2');
    EXPECT_EQ(card.getSuit(), 'H');
    EXPECT_EQ(card.getValue(), 2);
}

TEST(CardTest, JackValue)
{
    Card card('J', 'C');
    EXPECT_EQ(card.getValue(), 11);
    EXPECT_EQ(card.getRank(), 'J');
    EXPECT_EQ(card.getSuit(), 'C');
}
TEST(CardTest, QueenValue)
{
    Card card('Q', 'D');
    EXPECT_EQ(card.getValue(), 12);
}

TEST(CardTest, NumericCard)
{
    Card card('7', 'S');
    EXPECT_EQ(card.getRank(), '7');
    EXPECT_EQ(card.getSuit(), 'S');
    EXPECT_EQ(card.getValue(), 7);
}

TEST(CardTest, ToStringForHearts)
{
    Card card('A', 'H');
    EXPECT_EQ(card.toString(), "A of Hearts");
}

TEST(CardTest, ToStringForDiamonds)
{
    Card card('8', 'D');
    EXPECT_EQ(card.toString(), "8 of Diamonds");
}

TEST(CardTest, ToStringForSpades)
{
    Card card('K', 'S');
    EXPECT_EQ(card.toString(), "K of Spades");
}

TEST(CardTest, InequalitySuit)
{
    Card card1('T', 'H');
    Card card2('T', 'S');
    EXPECT_NE(card1, card2);
}

TEST(CardTest, UpperBound)
{
    Card card('A', 'C');
    EXPECT_EQ(card.getRank(), 'A');
    EXPECT_EQ(card.getSuit(), 'C');
    EXPECT_EQ(card.getValue(), 14);
}
