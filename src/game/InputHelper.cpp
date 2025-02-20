#include "InputHelper.hpp"

Available_actions get_action_from_input()
{
    std::string input;
    std::cin >> input;

    if (input == "check") {
        return Check;
    } else if (input == "bet") {
        return Bet;
    } else if (input == "fold") {
        return Fold;
    } else if (input == "call") {
        return Call;
    } else if (input == "raise") {
        return Raise;
    } else {
        throw std::invalid_argument("Invalid action");
    }
}