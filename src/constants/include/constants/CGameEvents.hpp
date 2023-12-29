//
// Purpur Tentakel
// 12.07.2023
//

#pragma once
#include "CGameEventTypes.hpp"
#include <array>
#include <cstddef>

namespace cst {
    struct GameEvents {
        static inline size_t constexpr configEntryCount{ 7 };

        HGameEventType events{ 0b11111111 }; // default "global"
        float globalEventChance{ 25.0f };

        void SetFlag(HGameEventType type, bool active);

        [[nodiscard]] bool IsFlag(HGameEventType type) const;
    };
} // namespace cst
