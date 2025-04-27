#include "MCCFR.hpp"
#include <gtest/gtest.h>

// Helper to sum the strategy vector
double sumStrategy(const std::vector<double> &strat)
{
    double sum = 0.0;
    for (double p : strat) sum += p;
    return sum;
}

// Friend accessor to access MCCFR private members for testing
struct MCCFRTest_FriendAccessor
{
    static auto &getNodes(MCCFR &solver)
    {
        return solver.nodes_;
    }
    static double runMCCFR(MCCFR &solver, MCCFRState state)
    {
        return solver.mccfr(state);
    }
};

// Basic Sanity Test: MCCFR runs without crashing
TEST(MCCFRTest, RunSanityTest)
{
    MCCFR solver(100);// only 100 iterations, quick
    solver.runIterations();
    SUCCEED();// If we reach here without crash, test passes
}

// Test that after running MCCFR, some nodes are created
TEST(MCCFRTest, NodesExistAfterRunning)
{
    MCCFR solver(1000);
    solver.runIterations();

    EXPECT_FALSE(MCCFRTest_FriendAccessor::getNodes(solver).empty()) << "No nodes were created after running MCCFR!";
}

// Test that average strategies approximately sum to 1
TEST(MCCFRTest, StrategyNormalization)
{
    MCCFR solver(1000);
    solver.runIterations();

    for (const auto &[key, node] : MCCFRTest_FriendAccessor::getNodes(solver)) {
        auto avgStrategy = node.getAverageStrategy();
        double stratSum = sumStrategy(avgStrategy);
        EXPECT_NEAR(stratSum, 1.0, 1e-5) << "Average strategy does not sum to 1";
    }
}

// Test running MCCFR from a custom fixed state
TEST(MCCFRTest, CustomFixedStateConvergence)
{
    MCCFR solver(5000);// more iterations since it's fixed cards

    MCCFRState state;
    state.playerCards = { Card(Card::RANK::ACE, Card::SUIT::SPADES), Card(Card::RANK::KING, Card::SUIT::HEARTS) };
    state.opponentCards = { Card(Card::RANK::NINE, Card::SUIT::DIAMONDS), Card(Card::RANK::EIGHT, Card::SUIT::CLUBS) };
    state.communityCards = { Card(Card::RANK::TWO, Card::SUIT::HEARTS),
        Card(Card::RANK::SEVEN, Card::SUIT::SPADES),
        Card(Card::RANK::TEN, Card::SUIT::CLUBS),
        Card(),
        Card() };
    state.communityCardIndex = 3;
    state.street = 1;// Flop

    MCCFRTest_FriendAccessor::runMCCFR(solver, state);

    EXPECT_FALSE(MCCFRTest_FriendAccessor::getNodes(solver).empty()) << "Nodes were not created from a custom state!";

    for (const auto &[key, node] : MCCFRTest_FriendAccessor::getNodes(solver)) {
        auto avgStrategy = node.getAverageStrategy();
        double stratSum = sumStrategy(avgStrategy);
        EXPECT_NEAR(stratSum, 1.0, 1e-5) << "Custom state average strategy does not sum to 1!";
    }
}

