//
// Purpur Tentakel
// 27.10.2022
//

#pragma once
#include <cstddef>


namespace cst {
    struct World final {
        static inline size_t constexpr configEntryCount{ 13 };

        size_t minPlanetCount{ 20 };
        size_t currentPlanetCount{ 50 };
        size_t maxPlanetCount{ 100 };
        size_t showPlanetCount{ 25 };

        int minDimensionX{ 60 };
        int currentDimensionX{ 150 };
        int maxDimensionX{ 300 };

        int minDimensionY{ 20 };
        int currentDimensionY{ 80 };
        int maxDimensionY{ 160 };

        int showDimensionX{ 200 };
        int showDimensionY{ 150 };

        int discoverRangeFactor{ 3 };
    };
} // namespace cst
