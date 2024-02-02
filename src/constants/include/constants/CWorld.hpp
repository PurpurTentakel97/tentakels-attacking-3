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

        utl::usize minDimensionX{ 60 };
        utl::usize currentDimensionX{ 150 };
        utl::usize maxDimensionX{ 300 };

        utl::usize minDimensionY{ 20 };
        utl::usize currentDimensionY{ 80 };
        utl::usize maxDimensionY{ 160 };

        utl::usize showDimensionX{ 200 };
        utl::usize showDimensionY{ 112 };

        utl::usize discoverRangeFactor{ 3 };
    };
} // namespace cst
