//
// Purpur Tentakel
// 09.03.2024
// This is a generated file. Do not edit this file.
//

#pragma once

#include <alias/AliasUtils.hpp>

namespace app {
     struct AppContext;
}

namespace cst {
    class G_Planet final {
    public:
        friend struct G_Config_IO;
        friend struct app::AppContext;

    private:
        static inline utl::usize constexpr s_total_config_entry_count = 10;
        static inline utl::usize constexpr s_load_config_entry_count = 8;
        utl::usize m_max_ships_factor = 25;
        utl::usize m_starting_human_ships_multiplier = 30;
        utl::usize m_starting_global_ships_multiplier = 5;
        utl::usize m_home_world_production = 10;
        utl::usize m_min_production = 3;
        utl::usize m_max_production = 7;
        float m_home_world_spacing = 0.15f;
        float m_global_spacing = 0.02f;

    public:
        [[nodiscard]] utl::usize get_total_config_entry_count() const {
            return s_total_config_entry_count;
        }
        [[nodiscard]] utl::usize get_load_config_entry_count() const {
            return s_load_config_entry_count;
        }
        [[nodiscard]] utl::usize get_max_ships_factor() const {
            return m_max_ships_factor;
        }
        [[nodiscard]] utl::usize get_starting_human_ships_multiplier() const {
            return m_starting_human_ships_multiplier;
        }
        [[nodiscard]] utl::usize get_starting_global_ships_multiplier() const {
            return m_starting_global_ships_multiplier;
        }
        [[nodiscard]] utl::usize get_home_world_production() const {
            return m_home_world_production;
        }
        [[nodiscard]] utl::usize get_min_production() const {
            return m_min_production;
        }
        [[nodiscard]] utl::usize get_max_production() const {
            return m_max_production;
        }
        [[nodiscard]] float get_home_world_spacing() const {
            return m_home_world_spacing;
        }
        [[nodiscard]] float get_global_spacing() const {
            return m_global_spacing;
        }

         void set_max_ships_factor(utl::usize const value) {
            m_max_ships_factor = value;
        }
         void set_starting_human_ships_multiplier(utl::usize const value) {
            m_starting_human_ships_multiplier = value;
        }
         void set_starting_global_ships_multiplier(utl::usize const value) {
            m_starting_global_ships_multiplier = value;
        }
         void set_home_world_production(utl::usize const value) {
            m_home_world_production = value;
        }
         void set_min_production(utl::usize const value) {
            m_min_production = value;
        }
         void set_max_production(utl::usize const value) {
            m_max_production = value;
        }
         void set_home_world_spacing(float const value) {
            m_home_world_spacing = value;
        }
         void set_global_spacing(float const value) {
            m_global_spacing = value;
        }
    };

} // namespace cst
