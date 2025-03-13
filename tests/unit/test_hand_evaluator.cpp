#include "Card.hpp"
#include "HandEvaluator.hpp"
#include <gtest/gtest.h>

using cardArr2 = std::array<Card, 2>;
using cardArr5 = std::array<Card, 5>;


#include "Card.hpp"
#include "HandEvaluator.hpp"
#include <gtest/gtest.h>

using cardArr2 = std::array<Card, 2>;
using cardArr5 = std::array<Card, 5>;

// -----------------------------------------------------------------
// Adjacent ranking comparisons (10 tests)
// 1. Royal Flush beats Straight Flush
TEST(HandEvaluatorComparison, RoyalFlushBeatsStraightFlush)
{
    HandEvaluator evaluator;
    // Board provides 4 hearts needed for a royal flush but not enough to form a straight flush on its own.
    cardArr5 community = { Card('T', 'H'), Card('J', 'H'), Card('Q', 'H'), Card('K', 'H'), Card('2', 'C') };
    // Hole cards complete the royal flush.
    cardArr2 royalFlush = { Card('A', 'H'), Card('3', 'C') };
    // Opponent’s hole cards complete a lower straight flush (9♥ + board T,J,Q,K).
    cardArr2 straightFlush = { Card('9', 'H'), Card('4', 'C') };

    int royalFlushVal = evaluator.evaluateHand(royalFlush, community);
    int straightFlushVal = evaluator.evaluateHand(straightFlush, community);
    EXPECT_LT(royalFlushVal, straightFlushVal);
}

// 2. Straight Flush beats Four‐of‐a‐Kind (Quads)
TEST(HandEvaluatorComparison, StraightFlushBeatsQuads)
{
    HandEvaluator evaluator;
    // Board has a pair plus three suited cards in sequence.
    cardArr5 community = { Card('Q', 'H'), Card('Q', 'C'), Card('7', 'H'), Card('8', 'H'), Card('9', 'H') };
    // Hole cards form a straight flush: 6♥ and T♥ complete 6-7-8-9-T of hearts.
    cardArr2 straightFlush = { Card('6', 'H'), Card('T', 'H') };
    // Opponent’s hole cards form quads: with two Q’s in hand joining the pair on board.
    cardArr2 quads = { Card('Q', 'D'), Card('Q', 'S') };

    int straightFlushVal = evaluator.evaluateHand(straightFlush, community);
    int quadsVal = evaluator.evaluateHand(quads, community);
    EXPECT_LT(straightFlushVal, quadsVal);
}

// 3. Four‐of‐a‐Kind beats Full House
TEST(HandEvaluatorComparison, QuadsBeatsFullHouse)
{
    HandEvaluator evaluator;
    // Board with three 9’s and two kickers.
    cardArr5 community = { Card('9', 'S'), Card('9', 'H'), Card('9', 'D'), Card('K', 'C'), Card('Q', 'C') };
    // With hole cards, one hand makes quads (four 9’s).
    cardArr2 quads = { Card('9', 'C'), Card('2', 'S') };
    // Other hand uses hole cards to form a full house (jacks full of 9’s).
    cardArr2 fullHouse = { Card('K', 'D'), Card('K', 'H') };

    int quadsVal = evaluator.evaluateHand(quads, community);
    int fullHouseVal = evaluator.evaluateHand(fullHouse, community);
    EXPECT_LT(quadsVal, fullHouseVal);
}

// 4. Full House beats Flush
TEST(HandEvaluatorComparison, FullHouseBeatsFlush)
{
    HandEvaluator evaluator;
    // Board has a pair (5’s) but not a flush on its own.
    cardArr5 community = { Card('2', 'H'), Card('5', 'H'), Card('5', 'D'), Card('K', 'D'), Card('3', 'H') };
    // Hole cards that combine with board to form a full house (kings full of 5’s).
    cardArr2 fullHouse = { Card('K', 'H'), Card('K', 'C') };
    // Opponent’s hole cards yield a flush in hearts.
    cardArr2 flush = { Card('9', 'H'), Card('J', 'H') };

    int fullHouseVal = evaluator.evaluateHand(fullHouse, community);
    int flushVal = evaluator.evaluateHand(flush, community);
    EXPECT_LT(fullHouseVal, flushVal);
}

// 5. Flush beats Straight
TEST(HandEvaluatorComparison, FlushBeatsStraight)
{
    HandEvaluator evaluator;
    // Board with three hearts (and two offsuit) so that flush and straight are possible.
    cardArr5 community = { Card('4', 'H'), Card('5', 'H'), Card('9', 'H'), Card('T', 'C'), Card('J', 'D') };
    // One hand gets a flush by adding two hearts.
    cardArr2 flushHand = { Card('2', 'H'), Card('8', 'H') };
    // Other hand makes a straight (using 7 and 8 off-suit with board T,J, plus 9).
    cardArr2 straightHand = { Card('7', 'C'), Card('8', 'C') };

    int flushVal = evaluator.evaluateHand(flushHand, community);
    int straightVal = evaluator.evaluateHand(straightHand, community);
    EXPECT_LT(flushVal, straightVal);
}

// 6. Straight beats Three‐of‐a‐Kind
TEST(HandEvaluatorComparison, StraightBeatsThreeOfAKind)
{
    HandEvaluator evaluator;
    // A neutral board that doesn’t itself form a straight.
    cardArr5 community = { Card('3', 'D'), Card('5', 'C'), Card('7', 'H'), Card('Q', 'S'), Card('K', 'D') };
    // Hole cards that complete a straight: 4 and 6 make 3-4-5-6-7.
    cardArr2 straightHand = { Card('4', 'H'), Card('6', 'H') };
    // Other hand makes three-of-a-kind (using 7’s).
    cardArr2 trips = { Card('7', 'C'), Card('7', 'D') };

    int straightVal = evaluator.evaluateHand(straightHand, community);
    int tripsVal = evaluator.evaluateHand(trips, community);
    EXPECT_LT(straightVal, tripsVal);
}

// 7. Three‐of‐a‐Kind beats Two Pair
TEST(HandEvaluatorComparison, ThreeOfAKindBeatsTwoPair)
{
    HandEvaluator evaluator;
    // Neutral board with no inherent pair.
    cardArr5 community = { Card('2', 'C'), Card('5', 'D'), Card('9', 'H'), Card('K', 'S'), Card('3', 'D') };
    // Hand that makes three-of-a-kind (with 9’s).
    cardArr2 trips = { Card('9', 'C'), Card('9', 'D') };
    // Hand that makes two pair (using K and 5 from hole cards).
    cardArr2 twoPair = { Card('K', 'D'), Card('5', 'C') };

    int tripsVal = evaluator.evaluateHand(trips, community);
    int twoPairVal = evaluator.evaluateHand(twoPair, community);
    EXPECT_LT(tripsVal, twoPairVal);
}

// 8. Two Pair beats One Pair
TEST(HandEvaluatorComparison, TwoPairBeatsOnePair)
{
    HandEvaluator evaluator;
    cardArr5 community = { Card('4', 'C'), Card('7', 'D'), Card('9', 'H'), Card('J', 'S'), Card('3', 'D') };
    // Hand with two pair (4’s and 7’s).
    cardArr2 twoPair = { Card('4', 'H'), Card('7', 'C') };
    // Hand with one pair (pair of 4’s).
    cardArr2 onePair = { Card('4', 'D'), Card('2', 'C') };

    int twoPairVal = evaluator.evaluateHand(twoPair, community);
    int onePairVal = evaluator.evaluateHand(onePair, community);
    EXPECT_LT(twoPairVal, onePairVal);
}

// 9. One Pair beats High Card
TEST(HandEvaluatorComparison, OnePairBeatsHighCard)
{
    HandEvaluator evaluator;
    cardArr5 community = { Card('4', 'C'), Card('7', 'D'), Card('9', 'H'), Card('J', 'S'), Card('3', 'D') };
    // Hand that makes one pair (pair of J’s from hole card + board).
    cardArr2 onePair = { Card('J', 'D'), Card('2', 'C') };
    // Hand that is only high card.
    cardArr2 highCard = { Card('A', 'C'), Card('8', 'S') };

    int onePairVal = evaluator.evaluateHand(onePair, community);
    int highCardVal = evaluator.evaluateHand(highCard, community);
    EXPECT_LT(onePairVal, highCardVal);
}

// 10. High Card Tie (both players’ best five cards come solely from the board)
TEST(HandEvaluatorComparison, HighCardTie)
{
    HandEvaluator evaluator;
    cardArr5 community = { Card('4', 'C'), Card('7', 'D'), Card('9', 'H'), Card('J', 'S'), Card('K', 'D') };
    // Both players have hole cards that do not improve on the board.
    cardArr2 highCard1 = { Card('2', 'C'), Card('3', 'D') };
    cardArr2 highCard2 = { Card('3', 'C'), Card('2', 'D') };

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
    // Board provides four suited cards that serve double duty:
    // It gives a royal flush for one hand and a pair for kings for the other.
    cardArr5 community = { Card('T', 'H'), Card('J', 'H'), Card('Q', 'H'), Card('K', 'H'), Card('K', 'D') };
    cardArr2 royalFlush = { Card('A', 'H'), Card('3', 'C') };
    // Opponent’s hole cards complete quads of kings.
    cardArr2 quads = { Card('K', 'C'), Card('K', 'S') };

    int royalFlushVal = evaluator.evaluateHand(royalFlush, community);
    int quadsVal = evaluator.evaluateHand(quads, community);
    EXPECT_LT(royalFlushVal, quadsVal);
}

// 12. Royal Flush beats Full House
TEST(HandEvaluatorComparison, RoyalFlushBeatsFullHouse)
{
    HandEvaluator evaluator;
    // Board has four royal cards plus an extra that makes a pair.
    cardArr5 community = { Card('T', 'H'), Card('J', 'H'), Card('Q', 'H'), Card('K', 'H'), Card('T', 'D') };
    cardArr2 royalFlush = { Card('A', 'H'), Card('3', 'C') };
    // Opponent forms full house using two jacks.
    cardArr2 fullHouse = { Card('J', 'C'), Card('J', 'D') };

    int royalFlushVal = evaluator.evaluateHand(royalFlush, community);
    int fullHouseVal = evaluator.evaluateHand(fullHouse, community);
    EXPECT_LT(royalFlushVal, fullHouseVal);
}

// 13. Royal Flush beats Flush
TEST(HandEvaluatorComparison, RoyalFlushBeatsFlush)
{
    HandEvaluator evaluator;
    cardArr5 community = { Card('T', 'H'), Card('J', 'H'), Card('Q', 'H'), Card('K', 'H'), Card('2', 'C') };
    cardArr2 royalFlush = { Card('A', 'H'), Card('3', 'C') };
    cardArr2 flush = { Card('9', 'H'), Card('4', 'H') };

    int royalFlushVal = evaluator.evaluateHand(royalFlush, community);
    int flushVal = evaluator.evaluateHand(flush, community);
    EXPECT_LT(royalFlushVal, flushVal);
}

// 14. Royal Flush beats Straight
TEST(HandEvaluatorComparison, RoyalFlushBeatsStraight)
{
    HandEvaluator evaluator;
    cardArr5 community = { Card('T', 'H'), Card('J', 'H'), Card('Q', 'H'), Card('K', 'H'), Card('2', 'C') };
    cardArr2 royalFlush = { Card('A', 'H'), Card('3', 'C') };
    // Opponent’s hole cards complete a straight (8 and 9, joining T,J,Q).
    cardArr2 straight = { Card('9', 'C'), Card('8', 'D') };

    int royalFlushVal = evaluator.evaluateHand(royalFlush, community);
    int straightVal = evaluator.evaluateHand(straight, community);
    EXPECT_LT(royalFlushVal, straightVal);
}

// 15. Royal Flush beats Three‐of‐a‐Kind
TEST(HandEvaluatorComparison, RoyalFlushBeatsThreeOfAKind)
{
    HandEvaluator evaluator;
    cardArr5 community = { Card('T', 'H'), Card('J', 'H'), Card('Q', 'H'), Card('K', 'H'), Card('2', 'C') };
    cardArr2 royalFlush = { Card('A', 'H'), Card('3', 'C') };
    // Opponent’s hole cards make trips (using the board 2).
    cardArr2 trips = { Card('2', 'D'), Card('2', 'S') };

    int royalFlushVal = evaluator.evaluateHand(royalFlush, community);
    int tripsVal = evaluator.evaluateHand(trips, community);
    EXPECT_LT(royalFlushVal, tripsVal);
}

// 16. Royal Flush beats Two Pair
TEST(HandEvaluatorComparison, RoyalFlushBeatsTwoPair)
{
    HandEvaluator evaluator;
    cardArr5 community = { Card('T', 'H'), Card('J', 'H'), Card('Q', 'H'), Card('K', 'H'), Card('2', 'C') };
    cardArr2 royalFlush = { Card('A', 'H'), Card('3', 'C') };
    // Opponent’s hole cards form two pair.
    cardArr2 twoPair = { Card('T', 'C'), Card('J', 'C') };

    int royalFlushVal = evaluator.evaluateHand(royalFlush, community);
    int twoPairVal = evaluator.evaluateHand(twoPair, community);
    EXPECT_LT(royalFlushVal, twoPairVal);
}

// 17. Royal Flush beats One Pair
TEST(HandEvaluatorComparison, RoyalFlushBeatsOnePair)
{
    HandEvaluator evaluator;
    cardArr5 community = { Card('T', 'H'), Card('J', 'H'), Card('Q', 'H'), Card('K', 'H'), Card('2', 'C') };
    cardArr2 royalFlush = { Card('A', 'H'), Card('4', 'C') };
    // Opponent’s hole cards form one pair (pair of 3’s).
    cardArr2 onePair = { Card('3', 'D'), Card('3', 'S') };

    int royalFlushVal = evaluator.evaluateHand(royalFlush, community);
    int onePairVal = evaluator.evaluateHand(onePair, community);
    EXPECT_LT(royalFlushVal, onePairVal);
}

// 18. Royal Flush beats High Card
TEST(HandEvaluatorComparison, RoyalFlushBeatsHighCard)
{
    HandEvaluator evaluator;
    cardArr5 community = { Card('T', 'H'), Card('J', 'H'), Card('Q', 'H'), Card('K', 'H'), Card('2', 'C') };
    cardArr2 royalFlush = { Card('A', 'H'), Card('4', 'C') };
    // Opponent’s hole cards do not improve on the board.
    cardArr2 highCard = { Card('8', 'D'), Card('7', 'S') };

    int royalFlushVal = evaluator.evaluateHand(royalFlush, community);
    int highCardVal = evaluator.evaluateHand(highCard, community);
    EXPECT_LT(royalFlushVal, highCardVal);
}

// 19. Straight Flush beats Full House
TEST(HandEvaluatorComparison, StraightFlushBeatsFullHouse)
{
    HandEvaluator evaluator;
    // Board with three hearts in sequence and a pair of kings.
    cardArr5 community = { Card('6', 'H'), Card('7', 'H'), Card('8', 'H'), Card('K', 'S'), Card('K', 'D') };
    // Opponent’s hole cards form a straight flush.
    cardArr2 straightFlush = { Card('4', 'H'), Card('5', 'H') };
    // Other hand makes a full house (using a king and an 8).
    cardArr2 fullHouse = { Card('K', 'H'), Card('8', 'S') };

    int straightFlushVal = evaluator.evaluateHand(straightFlush, community);
    int fullHouseVal = evaluator.evaluateHand(fullHouse, community);
    EXPECT_LT(straightFlushVal, fullHouseVal);
}

// 20. Straight Flush beats Flush
TEST(HandEvaluatorComparison, StraightFlushBeatsFlush)
{
    HandEvaluator evaluator;
    // Board with three hearts (but not in sequence) plus two neutral cards.
    cardArr5 community = { Card('6', 'H'), Card('7', 'H'), Card('8', 'H'), Card('2', 'C'), Card('3', 'D') };
    cardArr2 straightFlush = { Card('4', 'H'), Card('5', 'H') };
    cardArr2 flush = { Card('9', 'H'), Card('Q', 'H') };

    int straightFlushVal = evaluator.evaluateHand(straightFlush, community);
    int flushVal = evaluator.evaluateHand(flush, community);
    EXPECT_LT(straightFlushVal, flushVal);
}

// 21. Straight Flush beats Straight
TEST(HandEvaluatorComparison, StraightFlushBeatsStraight)
{
    HandEvaluator evaluator;
    // Board that does not itself form a straight.
    cardArr5 community = { Card('7', 'H'), Card('8', 'H'), Card('9', 'H'), Card('4', 'C'), Card('2', 'D') };
    cardArr2 straightFlush = { Card('5', 'H'), Card('6', 'H') };
    // Opponent’s hole cards make a straight.
    cardArr2 straight = { Card('T', 'C'), Card('J', 'C') };

    int straightFlushVal = evaluator.evaluateHand(straightFlush, community);
    int straightVal = evaluator.evaluateHand(straight, community);
    EXPECT_LT(straightFlushVal, straightVal);
}

// 22. Straight Flush beats Three‐of‐a‐Kind
TEST(HandEvaluatorComparison, StraightFlushBeatsThreeOfAKind)
{
    HandEvaluator evaluator;
    cardArr5 community = { Card('7', 'H'), Card('8', 'H'), Card('9', 'H'), Card('4', 'C'), Card('2', 'D') };
    cardArr2 straightFlush = { Card('5', 'H'), Card('6', 'H') };
    cardArr2 trips = { Card('7', 'C'), Card('7', 'D') };

    int straightFlushVal = evaluator.evaluateHand(straightFlush, community);
    int tripsVal = evaluator.evaluateHand(trips, community);
    EXPECT_LT(straightFlushVal, tripsVal);
}

// 23. Straight Flush beats Two Pair
TEST(HandEvaluatorComparison, StraightFlushBeatsTwoPair)
{
    HandEvaluator evaluator;
    cardArr5 community = { Card('7', 'H'), Card('8', 'H'), Card('9', 'H'), Card('4', 'C'), Card('2', 'D') };
    cardArr2 straightFlush = { Card('5', 'H'), Card('6', 'H') };
    cardArr2 twoPair = { Card('7', 'C'), Card('8', 'C') };

    int straightFlushVal = evaluator.evaluateHand(straightFlush, community);
    int twoPairVal = evaluator.evaluateHand(twoPair, community);
    EXPECT_LT(straightFlushVal, twoPairVal);
}

// 24. Straight Flush beats One Pair
TEST(HandEvaluatorComparison, StraightFlushBeatsOnePair)
{
    HandEvaluator evaluator;
    cardArr5 community = { Card('7', 'H'), Card('8', 'H'), Card('9', 'H'), Card('4', 'C'), Card('2', 'D') };
    cardArr2 straightFlush = { Card('5', 'H'), Card('6', 'H') };
    cardArr2 onePair = { Card('7', 'C'), Card('3', 'D') };

    int straightFlushVal = evaluator.evaluateHand(straightFlush, community);
    int onePairVal = evaluator.evaluateHand(onePair, community);
    EXPECT_LT(straightFlushVal, onePairVal);
}

// 25. Straight Flush beats High Card
TEST(HandEvaluatorComparison, StraightFlushBeatsHighCard)
{
    HandEvaluator evaluator;
    cardArr5 community = { Card('7', 'H'), Card('8', 'H'), Card('9', 'H'), Card('4', 'C'), Card('2', 'D') };
    cardArr2 straightFlush = { Card('5', 'H'), Card('6', 'H') };
    cardArr2 highCard = { Card('A', 'C'), Card('3', 'C') };

    int straightFlushVal = evaluator.evaluateHand(straightFlush, community);
    int highCardVal = evaluator.evaluateHand(highCard, community);
    EXPECT_LT(straightFlushVal, highCardVal);
}

// 26. Four‐of‐a‐Kind beats Flush
TEST(HandEvaluatorComparison, QuadsBeatsFlush)
{
    HandEvaluator evaluator;
    // Board with a pair of hearts (and one heart among the quads rank).
    cardArr5 community = { Card('9', 'S'), Card('9', 'H'), Card('9', 'D'), Card('4', 'H'), Card('7', 'H') };
    cardArr2 quads = { Card('9', 'C'), Card('2', 'S') };
    cardArr2 flush = { Card('A', 'H'), Card('K', 'H') };

    int quadsVal = evaluator.evaluateHand(quads, community);
    int flushVal = evaluator.evaluateHand(flush, community);
    EXPECT_LT(quadsVal, flushVal);
}

// 27. Four‐of‐a‐Kind beats Straight
TEST(HandEvaluatorComparison, QuadsBeatsStraight)
{
    HandEvaluator evaluator;
    // Board that gives a pair plus extra cards.
    cardArr5 community = { Card('9', 'S'), Card('9', 'H'), Card('9', 'D'), Card('8', 'S'), Card('7', 'D') };
    cardArr2 quads = { Card('9', 'C'), Card('2', 'C') };
    cardArr2 straight = { Card('T', 'C'), Card('J', 'C') };

    int quadsVal = evaluator.evaluateHand(quads, community);
    int straightVal = evaluator.evaluateHand(straight, community);
    EXPECT_LT(quadsVal, straightVal);
}

// 28. Four‐of‐a‐Kind beats Three‐of‐a‐Kind
TEST(HandEvaluatorComparison, QuadsBeatsThreeOfAKind)
{
    HandEvaluator evaluator;
    // Board with three 5’s.
    cardArr5 community = { Card('5', 'C'), Card('5', 'D'), Card('5', 'H'), Card('8', 'S'), Card('7', 'D') };
    cardArr2 quads = { Card('5', 'S'), Card('2', 'C') };
    cardArr2 trips = { Card('8', 'C'), Card('8', 'D') };

    int quadsVal = evaluator.evaluateHand(quads, community);
    int tripsVal = evaluator.evaluateHand(trips, community);
    EXPECT_LT(quadsVal, tripsVal);
}

// 29. Four‐of‐a‐Kind beats Two Pair
TEST(HandEvaluatorComparison, QuadsBeatsTwoPair)
{
    HandEvaluator evaluator;
    // Board with three 4’s.
    cardArr5 community = { Card('4', 'C'), Card('4', 'D'), Card('4', 'H'), Card('9', 'S'), Card('7', 'D') };
    cardArr2 quads = { Card('4', 'S'), Card('2', 'C') };
    cardArr2 twoPair = { Card('9', 'C'), Card('7', 'C') };

    int quadsVal = evaluator.evaluateHand(quads, community);
    int twoPairVal = evaluator.evaluateHand(twoPair, community);
    EXPECT_LT(quadsVal, twoPairVal);
}

// 30. Four‐of‐a‐Kind beats One Pair
TEST(HandEvaluatorComparison, QuadsBeatsOnePair)
{
    HandEvaluator evaluator;
    // Use a board that provides a pair (but not a set) so that a pair in the hand remains just one pair.
    cardArr5 community = { Card('3', 'C'), Card('3', 'D'), Card('8', 'H'), Card('T', 'S'), Card('Q', 'D') };
    cardArr2 quads = { Card('3', 'H'), Card('3', 'S') };
    cardArr2 onePair = { Card('4', 'H'), Card('6', 'H') };

    int quadsVal = evaluator.evaluateHand(quads, community);
    int onePairVal = evaluator.evaluateHand(onePair, community);
    EXPECT_LT(quadsVal, onePairVal);
}
