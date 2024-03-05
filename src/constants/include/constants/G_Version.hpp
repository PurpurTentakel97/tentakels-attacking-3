//
// Purpur Tentakel
// 05.03.2024
// This is a generated file. Do not edit this file.
//

#pragma once

#include <string>

namespace cst {
    class G_Version final {
    public:
        friend struct G_ConfigIO;

    private:
        static inline utl::usize constexpr s_total_config_entry_count = 5;
        static inline utl::usize constexpr s_load_config_entry_count = 2;
        static inline std::string const s_game_version = "v0.1.7";
        static inline std::string const s_config_version = "v0.1.6.10";
        static inline std::string const s_language_version = "v0.1.7.1";

    public:
        [[nodiscard]] utl::usize get_total_config_entry_count() const {
            return s_total_config_entry_count;
        }
        [[nodiscard]] utl::usize get_load_config_entry_count() const {
            return s_load_config_entry_count;
        }
        [[nodiscard]] std::string get_game_version() const {
            return s_game_version;
        }
        [[nodiscard]] std::string get_config_version() const {
            return s_config_version;
        }
        [[nodiscard]] std::string get_language_version() const {
            return s_language_version;
        }

    };

} // namespace cst
