//
// Purpur Tentakel
// 28.10.2022
//

#pragma once
#include <cstddef>
#include <string>

namespace cst {
    struct CGlobal final {
        // config counts
        static inline size_t constexpr configEntryCount{ 4 };
        static inline size_t constexpr configVersionCount{ 2 };
        static inline size_t constexpr configSectionCount{ 10 };

        // versions
        static inline std::string const languageVersion{ "v0.1.5.4" };
        static inline std::string const configVersion{ "v0.1.5.0" };
        static inline std::string const gameVersion{ "v0.1.5" };
        static inline std::string const copyRight{ "(c) Purpur Tentakel" };

        // language string
        std::string currentLanguageName{ "english" };

        // game rounds
        size_t minRounds{ 20 };
        size_t currentTargetRound{ 50 };
        size_t maxRounds{ 100 };
        size_t currentRound{ 0 };

        // game
        bool isGameRunning{ false };
        bool isGamePaused{ true };
        bool isGameSaved{ true };

        // input
        bool acceptInputTriggered{ false };
    };
} // namespace cst
