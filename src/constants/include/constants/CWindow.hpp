//
// Purpur Tentakel
// 10.12.2022
//

#pragma once
#include <CustomRaylib.hpp>
#include <cstddef>
#include <helper/HResolution.hpp>
#include <helper/HVec2.hpp>
#include <string>
#include <vector>


namespace cst {
    struct Window final {
        static inline size_t constexpr configEntryCount{ 3 };

        Resolution currentResolutionEnum{ Resolution::LAST };
        Vector2 currentResolutionVec{ 800.0f, 600.0f };
        HVec2<int> nativeResolutionVec{ 800, 600 };

        bool isFullScreen{ true };
        size_t FPS{ 60 };

        [[nodiscard]] bool IsPossibleResolution(Resolution toProve) const;

        [[nodiscard]] std::vector<std::pair<Resolution, std::string>> GetAllResolutionsAsString() const;

        [[nodiscard]] std::string GetStringFromResolution(Resolution resolution) const;

        [[nodiscard]] HVec2<int> GetIntFromResolution(Resolution resolution) const;
    };
} // namespace cst
