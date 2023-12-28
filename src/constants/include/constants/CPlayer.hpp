//
// Purpur Tentakel
// 27.10.2022
//

#pragma once
#include <cstddef>


struct CPlayer final {
    static inline size_t constexpr configEntryCount{ 3 };

    size_t minPlayerCount{ 2 };
    size_t maxPlayerCount{ 7 };
    bool shuffle{ false };
};
