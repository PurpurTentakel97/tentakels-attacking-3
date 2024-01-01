//
// Purpur Tentakel
// 10.12.2022
//

#pragma once

#include "CResolution.hpp"
#include <CustomRaylib.hpp>
#include <alias/AliasUtils.hpp>
#include <cstddef>
#include <string>
#include <utils/Vec2.hpp>
#include <vector>


namespace cst {
    struct Window final {
        static inline utl::usize constexpr configEntryCount{ 3 };

        Resolution currentResolutionEnum{ Resolution::LAST };
        Vector2 currentResolutionVec{ 800.0f, 600.0f };
        utl::Vec2<utl::usize> nativeResolutionVec{ 800, 600 };

        bool isFullScreen{ true };
        utl::usize FPS{ 60 };

        [[nodiscard]] bool IsPossibleResolution(Resolution toProve) const;

        [[nodiscard]] std::vector<std::pair<Resolution, std::string>> GetAllResolutionsAsString() const;

        [[nodiscard]] std::string GetStringFromResolution(Resolution resolution) const;

        [[nodiscard]] utl::Vec2<utl::usize> GetIntFromResolution(Resolution resolution) const;
    };
} // namespace cst
