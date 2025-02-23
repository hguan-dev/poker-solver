#include "InputHelper.hpp"

ACTIONS get_action_from_input()
{
    std::string input;
    std::cin >> input;

    if (input == "check" || input == "ch") {
        return ACTIONS::CHECK;
    } else if (input == "bet" || input == "b") {
        return ACTIONS::BET;
    } else if (input == "fold" || input == "f") {
        return ACTIONS::FOLD;
    } else if (input == "call" || input == "c") {
        return ACTIONS::CALL;
    } else if (input == "raise" || input == "r") {
        return ACTIONS::RAISE;
    } else {
        throw std::invalid_argument("Invalid action");
    }
}

double raiseHelper()
{
    double raiseAmount;
    std::cin >> raiseAmount;

    while (std::cin.fail() || raiseAmount <= 0) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cin >> raiseAmount;
    }
    return raiseAmount;
}