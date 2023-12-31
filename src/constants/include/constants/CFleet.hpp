//
// Purpur Tentakel
// 24.05.2023
//

#pragma once

#include <cstddef>

namespace cst {
    struct Fleet final {
        static inline utl::usize constexpr configEntryCount{ 3 };

        int minFleetSpeed{ 1 };
        int currentFleetSpeed{ 5 };
        int maxFleetSpeed{ 20 };
    };
} // namespace cst
