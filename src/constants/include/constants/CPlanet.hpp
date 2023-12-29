//
// Purpur Tentakel
// 07.11.2022
//

#pragma once

#include <cstddef>

namespace cst {
    struct Planet final {
        static inline size_t constexpr configEntryCount{ 8 };

        size_t maxShipsFactor{ 25 };
        size_t startingHumanShipsMultiplicator{ 30 };
        size_t startingGlobalShipsMultiplicator{ 5 };

        size_t homeworldProduction{ 10 };
        size_t minProduction{ 3 };
        size_t maxProduction{ 7 };

        float homeworldSpacing{ 0.15f };
        float globalSpacing{ 0.02f };
    };
} // namespace cst
