#include "Deck.hpp"
#include <gtest/gtest.h>

TEST(DeckTest, CreateDeck)
{
    Deck deck;
    EXPECT_EQ(deck.getLength(), 52);
}

TEST(DeckTest, PopTop)
{
    Deck deck;
    deck.popTop();
    EXPECT_EQ(deck.getLength(), 51);
}
