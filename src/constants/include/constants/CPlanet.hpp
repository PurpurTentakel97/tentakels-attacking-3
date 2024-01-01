//
// Purpur Tentakel
// 07.11.2022
//

#pragma once

#include <cstddef>

namespace cst {
    struct Planet final {
        static inline utl::usize constexpr configEntryCount{ 8 };

        utl::usize maxShipsFactor{ 25 };
        utl::usize startingHumanShipsMultiplicator{ 30 };
        utl::usize startingGlobalShipsMultiplicator{ 5 };

        utl::usize homeworldProduction{ 10 };
        utl::usize minProduction{ 3 };
        utl::usize maxProduction{ 7 };

        float homeworldSpacing{ 0.15f };
        float globalSpacing{ 0.02f };
    };
} // namespace cst
