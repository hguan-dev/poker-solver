#pragma once

#include <iostream>
#include <stdexcept>
#include <string>

enum Available_actions { Check, Bet, Fold, Call, Raise };

Available_actions get_action_from_input();