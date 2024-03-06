//
// Purpur Tentakel
// 06.03.2024
//

#pragma once

#include <alias/AliasUtils.hpp>

namespace cst {
    struct HelperGameEvents final {
        [[nodiscard]] utl::Probability ChanceByType(utl::GameEventType type) const;

        [[nodiscard]] bool IsEventByType(utl::GameEventType type) const;

        void SetEventByType(utl::GameEventType type, bool is_active);
    };
} // namespace cst
