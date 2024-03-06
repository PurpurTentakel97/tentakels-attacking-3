//
// Purpur Tentakel
// 10.12.2022
//

#pragma once

#include "CResolution.hpp"
#include <alias/AliasUtils.hpp>
#include <utils/Vec2.hpp>


namespace cst {
    struct Window final {
        static inline utl::usize constexpr configEntryCount{ 3 };

        Resolution currentResolutionEnum{ Resolution::LAST };

        bool isFullScreen{ true };
        utl::usize FPS{ 60 };
    };
} // namespace cst
