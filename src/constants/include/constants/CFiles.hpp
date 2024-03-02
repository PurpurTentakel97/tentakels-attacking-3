//
// Purpur Tentakel
// 28.10.2022
//

#pragma once

#include <chrono>
#include <format>
#include <fstream>
#include <string>

namespace cst {
    struct Files final {
    private:
        static inline std::string const s_autoGameSavesDir{ "AutoSave" };
        static inline std::string const s_gameSavesDir{ "Game" };
        static inline std::string const s_debugLogDir{ "debug" };
        static inline std::string const s_autoSaveFile{ "auto_save.tas" };

    public:
        static inline std::string const s_configFile{ "config.tac" };
        static inline std::string s_debugLogFile{ "default.txt" };
        static inline std::string const s_savesDir{ "saves" };
        static inline std::ofstream s_debugLogStream{};

        [[nodiscard]] static inline std::string debugLogDir(){
            return s_savesDir + '/' + s_debugLogDir;
        }

        [[nodiscard]] static inline std::string gameSafeDir() {
            return { s_savesDir + "/" + s_gameSavesDir };
        }
        [[nodiscard]] static inline std::string autoGameSafeDir() {
            return { gameSafeDir() + "/" + s_autoGameSavesDir };
        }
        [[nodiscard]] static std::string autoGameSafeFile() {
            auto const now = std::chrono::system_clock::now();
            auto const str = std::format("{:%Y_%m_%d-%H_%M_%OS}", now);
            return str + '-' + s_autoSaveFile;
        }
        static inline void SetDebugLogFile(std::string const& filename) {
            s_debugLogFile = filename;
        }
    };
} // namespace cst
