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
    EXPECT_TRUE(card1 == card2);
}

TEST(CardTest, InequalityOperator)
{
    Card card1('T', 'H');
    Card card2('J', 'H');
    EXPECT_TRUE(card1 != card2);
}

TEST(CardTest, LowerBound)
{
    Card card("2", "Hearts");
    EXPECT_EQ(card.getRank(), "2");
    EXPECT_EQ(card.getSuit(), "Hearts");
    EXPECT_EQ(card.getValue(), 2);
}

TEST(CardTest, JackValue)
{
    Card card("J", "Clubs");
    EXPECT_EQ(card.getValue(), 11);
    EXPECT_EQ(card.getRank(), "J");
    EXPECT_EQ(card.getSuit(), "Clubs");
}