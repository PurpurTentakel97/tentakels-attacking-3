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
        Vector2 currentResolutionVec{ 800.0f, 600.0f };
        utl::vec2pos_ty nativeResolutionVec{ 800, 600 };

        bool isFullScreen{ true };
        utl::usize FPS{ 60 };
    };
} // namespace cst
