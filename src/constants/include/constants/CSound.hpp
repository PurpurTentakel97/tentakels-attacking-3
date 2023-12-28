//
// Purpur Tentakel
// 28.10.2022
//

#pragma once
#include <cstddef>

namespace cst {
    struct Sound final {
        static inline size_t constexpr configEntryCount{ 2 };

        bool muteVolume{ false };
        float masterVolume{ 50.0f };
    };
} // namespace cst
