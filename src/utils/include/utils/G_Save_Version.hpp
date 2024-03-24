//
// Purpur Tentakel
// 24.03.2024
// This is a generated file. Do not edit this file.
//

#pragma once

#include <string>
#include <alias/AliasUtils.hpp>


namespace utl {
    class G_Save_Version final {
    private:
        static inline utl::usize constexpr s_total_save_entry_count = 3;
        static inline utl::usize constexpr s_load_save_entry_count = 1;
        std::string m_save_game_version = "v0.0.0.0";

    public:
        [[nodiscard]] utl::usize get_total_save_entry_count() const {
            return s_total_save_entry_count;
        }
        [[nodiscard]] utl::usize get_load_save_entry_count() const {
            return s_load_save_entry_count;
        }
        [[nodiscard]] std::string get_save_game_version() const {
            return m_save_game_version;
        }

        void set_save_game_version(std::string value) {
            m_save_game_version = std::move(value);
        }
    };

} // namespace utl
