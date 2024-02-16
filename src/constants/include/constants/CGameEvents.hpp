//
// Purpur Tentakel
// 12.07.2023
//

#pragma once

#include "utils/GameEventTypes.hpp"
#include <alias/AliasUtils.hpp>
#include <array>
#include <cstddef>
#include <utils/GameEventTypes.hpp>
#include <utils/Probability.hpp>

namespace cst {
    struct GameEvents {
        static inline utl::usize constexpr configEntryCount{ 15 };
        utl::GameEventType events{ 0b11111111 }; // default "global"

        utl::usize minEventYear{ 5 };
        bool isMinEventYear{ false };
        bool isEventOnHomeWorld{ false };

        utl::Probability globalChance{ 7500 };

        utl::Probability pirateChance{ 1500 };
        utl::Probability revoltChance{ 1500 };
        utl::Probability renegadeShipsChance{ 1500 };
        utl::Probability supernovaChance{ 100 };
        utl::Probability engineProblemChance{ 1000 };

        utl::usize maxYearsEngineProblem{ 5 };

        void SetFlag(utl::GameEventType type, bool active);

        [[nodiscard]] bool IsFlag(utl::GameEventType type) const;

        [[nodiscard]] utl::Probability ChanceByType(utl::GameEventType type) const;
    };
} // namespace cst
