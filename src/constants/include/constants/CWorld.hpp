//
// Purpur Tentakel
// 27.10.2022
//

#pragma once

#include <cstddef>


namespace cst {
    struct World final {
        static inline utl::usize constexpr configEntryCount{ 13 };

        utl::usize minPlanetCount{ 20 };
        utl::usize currentPlanetCount{ 50 };
        utl::usize maxPlanetCount{ 100 };
        utl::usize showPlanetCount{ 25 };

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
