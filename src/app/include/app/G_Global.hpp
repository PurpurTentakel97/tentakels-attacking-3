//
// Purpur Tentakel
// 16.03.2024
// This is a generated file. Do not edit this file.
//

#pragma once

#include <alias/AliasUtils.hpp>
#include <string>


namespace app {
    class G_Global final {
    private:
        static inline utl::usize constexpr s_save_section_count = 1;
        static inline utl::usize constexpr s_global_total_save_entry_count = 6;
        static inline utl::usize constexpr s_global_load_save_entry_count = 2;
        std::string m_global_game_version;
        std::string m_global_save_version;

    public:
        G_Global(std::string global_game_version,
                std::string global_save_version)
            : m_global_game_version{ std::move(global_game_version) },
                m_global_save_version{ std::move(global_save_version) } {}

        [[nodiscard]] utl::usize get_save_section_count() const {
            return s_save_section_count;
        }
        [[nodiscard]] utl::usize get_global_total_save_entry_count() const {
            return s_global_total_save_entry_count;
        }
        [[nodiscard]] utl::usize get_global_load_save_entry_count() const {
            return s_global_load_save_entry_count;
        }
        [[nodiscard]] std::string get_global_game_version() const {
            return m_global_game_version;
        }
        [[nodiscard]] std::string get_global_save_version() const {
            return m_global_save_version;
        }

        void set_global_game_version(std::string value) {
            m_global_game_version = std::move(value);
        }
        void set_global_save_version(std::string value) {
            m_global_save_version = std::move(value);
        }
    };

} // namespace app
