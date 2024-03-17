//
// Purpur Tentakel
// 17.03.2024
//

#pragma once

#include <alias/AliasUtils.hpp>
#include <array>
#include <string>

namespace hlp {
    enum class VersionResult {
        HIGHER,
        SAME,
        LOWER,
    };

    using version_ty = std::array<utl::usize,4>;

    [[nodiscard]] version_ty ParseVersion(std::string const& str);

    [[nodiscard]] VersionResult CompareVersion(std::string const& provided, std::string const& rhs);

    [[nodiscard]] VersionResult CompareVersion(version_ty const& provided, version_ty const& rhs);
} // namespace hlp
