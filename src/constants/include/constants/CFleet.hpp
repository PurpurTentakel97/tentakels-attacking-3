//
// Purpur Tentakel
// 24.05.2023
//

#pragma once

#include <cstddef>

namespace cst {
    struct Fleet final {
        static inline utl::usize constexpr configEntryCount{ 3 };

        utl::usize minFleetSpeed{ 1 };
        utl::usize currentFleetSpeed{ 5 };
        utl::usize maxFleetSpeed{ 20 };
    };
} // namespace cst
