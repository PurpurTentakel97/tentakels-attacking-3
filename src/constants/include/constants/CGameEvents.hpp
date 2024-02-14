//
// Purpur Tentakel
// 12.07.2023
//

#pragma once

#include "utils/GameEventTypes.hpp"
#include <alias/AliasUtils.hpp>
#include <array>
#include <cstddef>
#include <utils/Probability.hpp>
#include <utils/GameEventTypes.hpp>

namespace cst {
    struct GameEvents {
        static inline utl::usize constexpr configEntryCount{ 14 };
        utl::GameEventType events{ 0b11111111 }; // default "global"

        utl::Probability m_globalChance{ 7500 };

        utl::Probability m_pirateChance{ 1500 };
        utl::Probability m_revoltChance{ 1500 };
        utl::Probability m_renegadeShipsChance{ 1500 };
        utl::Probability m_blackHoleChance{ 200 };
        utl::Probability m_supernovaChance{ 100 };
        utl::Probability m_engineProblemChance{ 1000 };

        utl::usize m_maxYearsEngineProblem{ 5 };

        void SetFlag(utl::GameEventType type, bool active);

        [[nodiscard]] bool IsFlag(utl::GameEventType type) const;

        [[nodiscard]] utl::Probability ChanceByType(utl::GameEventType type) const;
    };
} // namespace cst
