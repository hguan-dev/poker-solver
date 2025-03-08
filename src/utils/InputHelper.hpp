#pragma once

#include <cmath>
#include <iostream>
#include <limits>
#include <stdexcept>
#include <string>

enum ACTIONS { CHECK, BET, FOLD, CALL, RAISE };

ACTIONS get_action_from_input();

double raiseHelper();