//
// Purpur Tentakel
// 06.03.2024
//

#pragma once

#include "CResolution.hpp"
#include <alias/AliasUtils.hpp>
#include <string>
#include <vector>


namespace cst {
    struct HelperWindow final {
        [[nodiscard]] bool IsPossibleResolution(Resolution toProve) const;

        [[nodiscard]] std::vector<std::pair<Resolution, std::string>> GetAllResolutionsAsString() const;

        [[nodiscard]] std::string GetStringFromResolution(Resolution resolution) const;

        [[nodiscard]] utl::vec2pos_ty GetIntFromResolution(Resolution resolution) const;
    };
} // namespace cst
