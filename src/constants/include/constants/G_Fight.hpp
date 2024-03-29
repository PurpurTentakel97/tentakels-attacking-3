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
    class G_Fight final {
    public:
        friend struct G_Config_IO;
        friend struct app::AppContext;

    private:
        static inline utl::usize constexpr s_total_config_entry_count = 8;
        static inline utl::usize constexpr s_load_config_entry_count = 6;
        float m_hit_chance = 0.1f;
        utl::usize m_fleet_fight_range = 4;
        bool m_is_fight_planet_fleet = true;
        bool m_is_fight_target_point_fleet = true;
        bool m_is_fight_target_point_target_point = true;
        bool m_is_fight_planet_target_point = true;

    public:
        [[nodiscard]] utl::usize get_total_config_entry_count() const {
            return s_total_config_entry_count;
        }
        [[nodiscard]] utl::usize get_load_config_entry_count() const {
            return s_load_config_entry_count;
        }
        [[nodiscard]] float get_hit_chance() const {
            return m_hit_chance;
        }
        [[nodiscard]] utl::usize get_fleet_fight_range() const {
            return m_fleet_fight_range;
        }
        [[nodiscard]] bool get_is_fight_planet_fleet() const {
            return m_is_fight_planet_fleet;
        }
        [[nodiscard]] bool get_is_fight_target_point_fleet() const {
            return m_is_fight_target_point_fleet;
        }
        [[nodiscard]] bool get_is_fight_target_point_target_point() const {
            return m_is_fight_target_point_target_point;
        }
        [[nodiscard]] bool get_is_fight_planet_target_point() const {
            return m_is_fight_planet_target_point;
        }

         void set_hit_chance(float const value) {
            m_hit_chance = value;
        }
         void set_fleet_fight_range(utl::usize const value) {
            m_fleet_fight_range = value;
        }
         void set_is_fight_planet_fleet(bool const value) {
            m_is_fight_planet_fleet = value;
        }
         void set_is_fight_target_point_fleet(bool const value) {
            m_is_fight_target_point_fleet = value;
        }
         void set_is_fight_target_point_target_point(bool const value) {
            m_is_fight_target_point_target_point = value;
        }
         void set_is_fight_planet_target_point(bool const value) {
            m_is_fight_planet_target_point = value;
        }
    };

} // namespace cst
