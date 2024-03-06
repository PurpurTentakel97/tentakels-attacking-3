//
// Purpur Tentakel
// 06.03.2024
// This is a generated file. Do not edit this file.
//

#pragma once

#include <alias/AliasUtils.hpp>
#include <string>

namespace app {
     struct AppContext;
}

namespace cst {
    class G_Global final {
    public:
        friend struct G_Config_IO;
        friend struct app::AppContext;

    private:
        static inline utl::usize constexpr s_config_section_count = 7;
        static inline utl::usize constexpr s_total_config_entry_count = 9;
        static inline utl::usize constexpr s_load_config_entry_count = 5;
        static inline std::string const s_copyright = "(c) Purpur Tentakel";
        std::string m_current_language_name = "english";
        utl::usize m_min_rounds = 20;
        utl::usize m_max_rounds = 100;
        utl::usize m_current_target_round = 50;
        utl::usize m_current_round = 1;

    public:
        [[nodiscard]] utl::usize get_config_section_count() const {
            return s_config_section_count;
        }
        [[nodiscard]] utl::usize get_total_config_entry_count() const {
            return s_total_config_entry_count;
        }
        [[nodiscard]] utl::usize get_load_config_entry_count() const {
            return s_load_config_entry_count;
        }
        [[nodiscard]] std::string get_copyright() const {
            return s_copyright;
        }
        [[nodiscard]] std::string get_current_language_name() const {
            return m_current_language_name;
        }
        [[nodiscard]] utl::usize get_min_rounds() const {
            return m_min_rounds;
        }
        [[nodiscard]] utl::usize get_max_rounds() const {
            return m_max_rounds;
        }
        [[nodiscard]] utl::usize get_current_target_round() const {
            return m_current_target_round;
        }
        [[nodiscard]] utl::usize get_current_round() const {
            return m_current_round;
        }

         void set_current_language_name(std::string const& value) {
            m_current_language_name = value;
        }
         void set_min_rounds(utl::usize const value) {
            m_min_rounds = value;
        }
         void set_max_rounds(utl::usize const value) {
            m_max_rounds = value;
        }
         void set_current_target_round(utl::usize const value) {
            m_current_target_round = value;
        }
         void set_current_round(utl::usize const value) {
            m_current_round = value;
        }
    };

} // namespace cst
