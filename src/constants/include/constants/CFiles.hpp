//
// Purpur Tentakel
// 28.10.2022
//

#pragma once
#include <fstream>
#include <string>

namespace cst {
    struct Files final {
    private:
        static inline std::string const m_configFile{ "config.tac" };
        static inline std::string m_debugLogFile{ "default.txt" };
        static inline std::string const m_debugLogDir{ "debug" };

    public:
        static inline std::string const savesDir{ "saves" };
        static inline std::ofstream debugLogStream{};

        [[nodiscard]] static inline std::string configFile() {
            return { savesDir + "/" + m_configFile };
        }
        [[nodiscard]] static inline std::string debugLogDir() {
            return { savesDir + "/" + m_debugLogDir };
        }
        [[nodiscard]] static inline std::string debugLogFile() {
            return { debugLogDir() + "/" + m_debugLogFile };
        }
        static inline void SetDebugLogFile(std::string const& filename) {
            m_debugLogFile = filename;
        }
    };
} // namespace cst
