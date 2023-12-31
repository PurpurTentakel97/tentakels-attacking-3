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
        static inline utl::usize constexpr configVersionCount{ 2 };
        static inline utl::usize constexpr configSectionCount{ 10 };

        // versions
        static inline std::string const languageVersion{ "v0.1.5.4" };
        static inline std::string const configVersion{ "v0.1.5.0" };
        static inline std::string const gameVersion{ "v0.1.5" };
        static inline std::string const copyRight{ "(c) Purpur Tentakel" };

        // language string
        std::string currentLanguageName{ "english" };

        // game rounds
        utl::usize minRounds{ 20 };
        utl::usize currentTargetRound{ 50 };
        utl::usize maxRounds{ 100 };
        utl::usize currentRound{ 0 };

        // game
        bool isGameRunning{ false };
        bool isGamePaused{ true };
        bool isGameSaved{ true };

        // input
        bool acceptInputTriggered{ false };
    };
} // namespace cst
