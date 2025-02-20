#pragma once

#include <iostream>
#include <stdexcept>
#include <string>

enum ACTIONS { CHECK, BET, FOLD, CALL, RAISE };

ACTIONS get_action_from_input();