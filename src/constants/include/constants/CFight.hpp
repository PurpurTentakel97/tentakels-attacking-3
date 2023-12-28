//
// Purpur Tentakel
// 04.06.2023
//

#pragma once
#include <cstddef>

namespace cst {
    struct Fight final {
        static inline size_t constexpr configEntryCount{ 6 };
        float hitChance{ 0.3f };
        int fleetFightRange{ 4 };

        bool isFightPlanetFleet{ true };
        bool isFightTargetPointFleet{ true };
        bool isFightTargetPointTargetPoint{ true };
        bool isFightPlanetTargetPoint{ true };
    };
} // namespace cst
