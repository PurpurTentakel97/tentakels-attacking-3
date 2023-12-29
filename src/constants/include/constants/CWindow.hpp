//
// Purpur Tentakel
// 10.12.2022
//

#pragma once
#include "CResolution.hpp"
#include <CustomRaylib.hpp>
#include <cstddef>
#include <string>
#include <utils/Vec2.hpp>
#include <vector>


namespace cst {
    struct Window final {
        static inline size_t constexpr configEntryCount{ 3 };

        Resolution currentResolutionEnum{ Resolution::LAST };
        Vector2 currentResolutionVec{ 800.0f, 600.0f };
        utl::Vec2<int> nativeResolutionVec{ 800, 600 };

        bool isFullScreen{ true };
        size_t FPS{ 60 };

        [[nodiscard]] bool IsPossibleResolution(Resolution toProve) const;

        [[nodiscard]] std::vector<std::pair<Resolution, std::string>> GetAllResolutionsAsString() const;

        [[nodiscard]] std::string GetStringFromResolution(Resolution resolution) const;

        [[nodiscard]] utl::Vec2<int> GetIntFromResolution(Resolution resolution) const;
    };
} // namespace cst
