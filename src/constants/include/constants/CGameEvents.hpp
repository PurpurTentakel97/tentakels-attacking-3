//
// Purpur Tentakel
// 12.07.2023
//

#pragma once

#include "CGameEventTypes.hpp"
#include <alias/AliasUtils.hpp>
#include <utils/Probability.hpp>
#include <array>
#include <cstddef>

namespace cst {
    struct GameEvents {
        static inline utl::usize constexpr configEntryCount{ 13 };
        GameEventType events{ 0b11111111 }; // default "global"

        utl::Probability m_globalChance{ 2500 };

        utl::Probability m_pirateChance{ 1500 };
        utl::Probability m_revoltChance{ 1500 };
        utl::Probability m_renegadeShipsChance{ 1500 };
        utl::Probability m_blackHoleChance{ 200 };
        utl::Probability m_supernovaChance{ 100 };
        utl::Probability m_engineProblemChance{ 1000 };

        void SetFlag(GameEventType type, bool active);

        [[nodiscard]] bool IsFlag(GameEventType type) const;

        [[nodiscard]] utl::Probability ChanceByType(GameEventType type) const;
    };
} // namespace cst
