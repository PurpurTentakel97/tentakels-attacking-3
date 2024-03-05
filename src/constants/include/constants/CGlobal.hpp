//
// Purpur Tentakel
// 28.10.2022
//

#pragma once

#include <cstddef>
#include <string>


namespace cst {
    struct Global final {
        // config counts
        static inline utl::usize constexpr configEntryCount{ 4 };
        static inline utl::usize constexpr configSectionCount{ 3 };

        static inline std::string const copyRight{ "(c) Purpur Tentakel" };

        // language string
        std::string currentLanguageName{ "english" };

        // game rounds
        utl::usize minRounds{ 20 };
        utl::usize currentTargetRound{ 50 };
        utl::usize maxRounds{ 100 };
        utl::usize currentRound{ 1 };

        // game
        bool isGameRunning{ false };
        bool isGamePaused{ true };
        bool isGameSaved{ true };

        // input
        bool acceptInputTriggered{ false };
    };
} // namespace cst
