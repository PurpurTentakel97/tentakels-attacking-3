//
// Purpur Tentakel
// 06.03.2024
// This is a generated file. Do not edit this file.
//

#pragma once

#include <alias/AliasUtils.hpp>

namespace app {
     struct AppContext;
}

namespace cst {
    class G_Fleet final {
    public:
        friend struct G_Config_IO;
        friend struct app::AppContext;

    private:
        static inline utl::usize constexpr s_total_config_entry_count = 5;
        static inline utl::usize constexpr s_load_config_entry_count = 3;
        utl::usize m_min_fleet_speed = 1;
        utl::usize m_current_fleet_speed = 5;
        utl::usize m_max_fleet_speed = 20;

    public:
        [[nodiscard]] utl::usize get_total_config_entry_count() const {
            return s_total_config_entry_count;
        }
        [[nodiscard]] utl::usize get_load_config_entry_count() const {
            return s_load_config_entry_count;
        }
        [[nodiscard]] utl::usize get_min_fleet_speed() const {
            return m_min_fleet_speed;
        }
        [[nodiscard]] utl::usize get_current_fleet_speed() const {
            return m_current_fleet_speed;
        }
        [[nodiscard]] utl::usize get_max_fleet_speed() const {
            return m_max_fleet_speed;
        }

         void set_min_fleet_speed(utl::usize const value) {
            m_min_fleet_speed = value;
        }
         void set_current_fleet_speed(utl::usize const value) {
            m_current_fleet_speed = value;
        }
         void set_max_fleet_speed(utl::usize const value) {
            m_max_fleet_speed = value;
        }
    };

} // namespace cst
