//
// Purpur Tentakel
// 24.03.2024
// This is a generated file. Do not edit this file.
//

#pragma once

#include <alias/AliasUtils.hpp>

namespace app {
     struct AppContext;
}

namespace cst {
    class G_World final {
    public:
        friend struct G_Config_IO;
        friend struct app::AppContext;

    private:
        static inline utl::usize constexpr s_total_config_entry_count = 15;
        static inline utl::usize constexpr s_load_config_entry_count = 13;
        utl::usize m_min_planet_count = 20;
        utl::usize m_current_planet_count = 50;
        utl::usize m_max_planet_count = 100;
        utl::usize m_show_planet_count = 25;
        utl::usize m_min_dimension_x = 60;
        utl::usize m_current_dimension_x = 150;
        utl::usize m_max_dimension_x = 300;
        utl::usize m_min_dimension_y = 20;
        utl::usize m_current_dimension_y = 80;
        utl::usize m_max_dimension_y = 160;
        utl::usize m_show_dimension_x = 200;
        utl::usize m_show_dimension_y = 112;
        utl::usize m_discover_range_factor = 3;

    public:
        [[nodiscard]] utl::usize get_total_config_entry_count() const {
            return s_total_config_entry_count;
        }
        [[nodiscard]] utl::usize get_load_config_entry_count() const {
            return s_load_config_entry_count;
        }
        [[nodiscard]] utl::usize get_min_planet_count() const {
            return m_min_planet_count;
        }
        [[nodiscard]] utl::usize get_current_planet_count() const {
            return m_current_planet_count;
        }
        [[nodiscard]] utl::usize get_max_planet_count() const {
            return m_max_planet_count;
        }
        [[nodiscard]] utl::usize get_show_planet_count() const {
            return m_show_planet_count;
        }
        [[nodiscard]] utl::usize get_min_dimension_x() const {
            return m_min_dimension_x;
        }
        [[nodiscard]] utl::usize get_current_dimension_x() const {
            return m_current_dimension_x;
        }
        [[nodiscard]] utl::usize get_max_dimension_x() const {
            return m_max_dimension_x;
        }
        [[nodiscard]] utl::usize get_min_dimension_y() const {
            return m_min_dimension_y;
        }
        [[nodiscard]] utl::usize get_current_dimension_y() const {
            return m_current_dimension_y;
        }
        [[nodiscard]] utl::usize get_max_dimension_y() const {
            return m_max_dimension_y;
        }
        [[nodiscard]] utl::usize get_show_dimension_x() const {
            return m_show_dimension_x;
        }
        [[nodiscard]] utl::usize get_show_dimension_y() const {
            return m_show_dimension_y;
        }
        [[nodiscard]] utl::usize get_discover_range_factor() const {
            return m_discover_range_factor;
        }

        void set_min_planet_count(utl::usize const value) {
            m_min_planet_count = value;
        }
        void set_current_planet_count(utl::usize const value) {
            m_current_planet_count = value;
        }
        void set_max_planet_count(utl::usize const value) {
            m_max_planet_count = value;
        }
        void set_show_planet_count(utl::usize const value) {
            m_show_planet_count = value;
        }
        void set_min_dimension_x(utl::usize const value) {
            m_min_dimension_x = value;
        }
        void set_current_dimension_x(utl::usize const value) {
            m_current_dimension_x = value;
        }
        void set_max_dimension_x(utl::usize const value) {
            m_max_dimension_x = value;
        }
        void set_min_dimension_y(utl::usize const value) {
            m_min_dimension_y = value;
        }
        void set_current_dimension_y(utl::usize const value) {
            m_current_dimension_y = value;
        }
        void set_max_dimension_y(utl::usize const value) {
            m_max_dimension_y = value;
        }
        void set_show_dimension_x(utl::usize const value) {
            m_show_dimension_x = value;
        }
        void set_show_dimension_y(utl::usize const value) {
            m_show_dimension_y = value;
        }
        void set_discover_range_factor(utl::usize const value) {
            m_discover_range_factor = value;
        }
    };

} // namespace cst
