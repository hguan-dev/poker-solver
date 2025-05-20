#pragma once

#include "Actions.hpp"

struct InfoSetKey
{
    int playerCard;
    std::vector<ActionID> history;

    bool operator==(const InfoSetKey &other) const
    {
        return playerCard == other.playerCard && history == other.history;
    }
};

namespace std {
template<> struct hash<InfoSetKey>
{
    size_t operator()(const InfoSetKey &k) const
    {
        size_t res = std::hash<int>()(k.playerCard);
        for (const auto &action : k.history) {
            res ^= std::hash<int>()(static_cast<int>(action)) + 0x9e3779b9 + (res << 6) + (res >> 2);
        }
        return res;
    }
};
}// namespace std
