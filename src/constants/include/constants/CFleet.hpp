//
// Purpur Tentakel
// 24.05.2023
//

#pragma once
#include <cstddef>

namespace cst {
    struct CFleet final {
        static inline size_t constexpr configEntryCount{ 3 };

        int minFleetSpeed{ 1 };
        int currentFleetSpeed{ 5 };
        int maxFleetSpeed{ 20 };
    };
} // namespace cst
