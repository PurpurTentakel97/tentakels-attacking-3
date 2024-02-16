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

        // general
        static inline utl::usize constexpr configEntryCount{ 18 };
        utl::GameEventType events{ 0b11111111 }; // default "global"
        bool isMinEventYear{ false };
        utl::usize minEventYear{ 5 };
        bool isEventOnHomeWorld{ false };
        utl::Probability globalChance{ 7500 };

        // pirates
        utl::Probability pirateChance{ 1500 };

        // revolts
        utl::Probability revoltChance{ 1500 };

        // renegade ships
        utl::Probability renegadeShipsChance{ 1500 };

        // supernova
        utl::Probability supernovaChance{ 100 };
        utl::usize minBlackHoleRange{ 3 };
        bool isMaxBlackHoleRange{ true };
        utl::usize maxBlackHoleRange{ 10 };

        // engine problems
        utl::Probability engineProblemChance{ 1000 };
        utl::usize maxYearsEngineProblem{ 5 };

        void SetFlag(utl::GameEventType type, bool active);

        [[nodiscard]] bool IsFlag(utl::GameEventType type) const;

        [[nodiscard]] utl::Probability ChanceByType(utl::GameEventType type) const;
    };
} // namespace cst
