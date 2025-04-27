#pragma once

#include <vector>

enum class ActionID {
    // Preflop open
    CHECK = 0,
    BET_2_5BB = 1,
    BET_2BB_MIN = 2,
    BET_3BB = 3,

    // Facing PFR
    MIN_RAISE = 4,
    RAISE_50P = 5,
    RAISE_75P = 6,
    RAISE_POT = 7,
    CALL = 8,
    FOLD = 9,

    // Postflop no bet
    BET_20POT = 10,
    BET_25POT = 11,
    BET_35POT = 12,
    BET_50POT = 13,
    BET_75POT = 14,
    BET_100POT = 15,
    POSTFLOP_CHECK = 16,

    // Postflop facing bet
    RAISE_2X = 17,
    RAISE_2_5X = 18,
    RAISE_3X = 19,
    RAISE_3_5X = 20,
    RAISE_4X = 21,
    POSTFLOP_RAISE_POT = 22,
    POSTFLOP_RAISE_75POT = 23,
    POSTFLOP_CALL = 24,
    POSTFLOP_FOLD = 25
};

namespace ActionSets {
// Preflop open actions
static const std::vector<ActionID> preflopOpen = { ActionID::CHECK,
    ActionID::BET_2_5BB,
    ActionID::BET_2BB_MIN,
    ActionID::BET_3BB };

// Facing PFR
static const std::vector<ActionID> facingPreflopRaise = { ActionID::MIN_RAISE,
    ActionID::RAISE_50P,
    ActionID::RAISE_75P,
    ActionID::RAISE_POT,
    ActionID::CALL,
    ActionID::FOLD };

// Postflop, no previous bet
static const std::vector<ActionID> postflopOpen = { ActionID::BET_20POT,
    ActionID::BET_25POT,
    ActionID::BET_35POT,
    ActionID::BET_50POT,
    ActionID::BET_75POT,
    ActionID::BET_100POT,
    ActionID::POSTFLOP_CHECK };

// Postflop facing bet
static const std::vector<ActionID> facingPostflopBet = { ActionID::RAISE_2X,
    ActionID::RAISE_2_5X,
    ActionID::RAISE_3X,
    ActionID::RAISE_3_5X,
    ActionID::RAISE_4X,
    ActionID::POSTFLOP_RAISE_POT,
    ActionID::POSTFLOP_RAISE_75POT,
    ActionID::POSTFLOP_CALL,
    ActionID::POSTFLOP_FOLD };
}// namespace ActionSets
