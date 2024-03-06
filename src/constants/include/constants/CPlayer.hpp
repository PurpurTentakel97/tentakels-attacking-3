//
// Purpur Tentakel
// 27.10.2022
//

#pragma once

#include <alias/AliasUtils.hpp>

namespace cst {
    struct Player final {
        static inline utl::usize constexpr configEntryCount{ 3 };

        utl::usize minPlayerCount{ 2 };
        utl::usize maxPlayerCount{ 7 };
        bool shuffle{ false };
    };
} // namespace cst
