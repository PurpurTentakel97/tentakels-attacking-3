//
// Purpur Tentakel
// 12.07.2023
//

#pragma once

#include "CGameEventTypes.hpp"
#include <alias/AliasUtils.hpp>
#include <array>
#include <cstddef>

namespace cst {
    struct GameEvents {

        static inline utl::usize constexpr configEntryCount{ 13 };
        GameEventType events{ 0b11111111 }; // default "global"

        float m_globalChance{ 25.0f };

        float m_pirateChance{ 15.0f };
        float m_revoltChance{ 15.0f };
        float m_renegadeShipsChance{ 15.0f };
        float m_blackHoleChance{ 2.0f };
        float m_supernovaChance{ 1.0f };
        float m_engineProblemChance{ 10.0f };

        void SetFlag(GameEventType type, bool active);

        [[nodiscard]] bool IsFlag(GameEventType type) const;
    };
} // namespace cst
