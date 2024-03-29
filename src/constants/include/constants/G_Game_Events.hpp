//
// Purpur Tentakel
// 06.03.2024
// This is a generated file. Do not edit this file.
//

#pragma once

#include <alias/AliasUtils.hpp>
#include <array>
#include <utils/GameEventTypes.hpp>
#include <utils/Probability.hpp>

namespace app {
     struct AppContext;
}

namespace cst {
    class G_Game_Events final {
    public:
        friend struct G_Config_IO;
        friend struct app::AppContext;

    private:
        static inline utl::usize constexpr s_total_config_entry_count = 25;
        static inline utl::usize constexpr s_load_config_entry_count = 23;
        bool m_is_min_event_year = true;
        utl::usize m_min_event_year = 5;
        bool m_is_event_on_home_world = false;
        utl::Probability m_global_chance = 7500;
        bool m_is_pirates = true;
        utl::Probability m_pirate_chance = 1000;
        utl::usize m_min_pirate_ships = 30;
        utl::usize m_max_pirate_ships = 150;
        bool m_is_revolts = true;
        utl::Probability m_revolts_chance = 1000;
        bool m_is_renegade_ships = true;
        utl::Probability m_renegade_ships_chance = 1000;
        bool m_is_supernova = true;
        utl::Probability m_supernova_chance = 300;
        float m_min_black_hole_range_factor = 0.05f;
        float m_max_black_hole_range_factor = 0.2f;
        bool m_is_max_black_hole_range_factor = true;
        bool m_is_engine_problem = true;
        utl::Probability m_engine_problem_chance = 1000;
        utl::usize m_max_engine_problem_years = 5;
        bool m_is_production_problem = true;
        utl::Probability m_production_problem_chance = 1000;
        utl::usize m_max_production_problem_years = 5;

    public:
        [[nodiscard]] utl::usize get_total_config_entry_count() const {
            return s_total_config_entry_count;
        }
        [[nodiscard]] utl::usize get_load_config_entry_count() const {
            return s_load_config_entry_count;
        }
        [[nodiscard]] bool get_is_min_event_year() const {
            return m_is_min_event_year;
        }
        [[nodiscard]] utl::usize get_min_event_year() const {
            return m_min_event_year;
        }
        [[nodiscard]] bool get_is_event_on_home_world() const {
            return m_is_event_on_home_world;
        }
        [[nodiscard]] utl::Probability get_global_chance() const {
            return m_global_chance;
        }
        [[nodiscard]] bool get_is_pirates() const {
            return m_is_pirates;
        }
        [[nodiscard]] utl::Probability get_pirate_chance() const {
            return m_pirate_chance;
        }
        [[nodiscard]] utl::usize get_min_pirate_ships() const {
            return m_min_pirate_ships;
        }
        [[nodiscard]] utl::usize get_max_pirate_ships() const {
            return m_max_pirate_ships;
        }
        [[nodiscard]] bool get_is_revolts() const {
            return m_is_revolts;
        }
        [[nodiscard]] utl::Probability get_revolts_chance() const {
            return m_revolts_chance;
        }
        [[nodiscard]] bool get_is_renegade_ships() const {
            return m_is_renegade_ships;
        }
        [[nodiscard]] utl::Probability get_renegade_ships_chance() const {
            return m_renegade_ships_chance;
        }
        [[nodiscard]] bool get_is_supernova() const {
            return m_is_supernova;
        }
        [[nodiscard]] utl::Probability get_supernova_chance() const {
            return m_supernova_chance;
        }
        [[nodiscard]] float get_min_black_hole_range_factor() const {
            return m_min_black_hole_range_factor;
        }
        [[nodiscard]] float get_max_black_hole_range_factor() const {
            return m_max_black_hole_range_factor;
        }
        [[nodiscard]] bool get_is_max_black_hole_range_factor() const {
            return m_is_max_black_hole_range_factor;
        }
        [[nodiscard]] bool get_is_engine_problem() const {
            return m_is_engine_problem;
        }
        [[nodiscard]] utl::Probability get_engine_problem_chance() const {
            return m_engine_problem_chance;
        }
        [[nodiscard]] utl::usize get_max_engine_problem_years() const {
            return m_max_engine_problem_years;
        }
        [[nodiscard]] bool get_is_production_problem() const {
            return m_is_production_problem;
        }
        [[nodiscard]] utl::Probability get_production_problem_chance() const {
            return m_production_problem_chance;
        }
        [[nodiscard]] utl::usize get_max_production_problem_years() const {
            return m_max_production_problem_years;
        }

         void set_is_min_event_year(bool const value) {
            m_is_min_event_year = value;
        }
         void set_min_event_year(utl::usize const value) {
            m_min_event_year = value;
        }
         void set_is_event_on_home_world(bool const value) {
            m_is_event_on_home_world = value;
        }
         void set_global_chance(utl::Probability const value) {
            m_global_chance = value;
        }
         void set_is_pirates(bool const value) {
            m_is_pirates = value;
        }
         void set_pirate_chance(utl::Probability const value) {
            m_pirate_chance = value;
        }
         void set_min_pirate_ships(utl::usize const value) {
            m_min_pirate_ships = value;
        }
         void set_max_pirate_ships(utl::usize const value) {
            m_max_pirate_ships = value;
        }
         void set_is_revolts(bool const value) {
            m_is_revolts = value;
        }
         void set_revolts_chance(utl::Probability const value) {
            m_revolts_chance = value;
        }
         void set_is_renegade_ships(bool const value) {
            m_is_renegade_ships = value;
        }
         void set_renegade_ships_chance(utl::Probability const value) {
            m_renegade_ships_chance = value;
        }
         void set_is_supernova(bool const value) {
            m_is_supernova = value;
        }
         void set_supernova_chance(utl::Probability const value) {
            m_supernova_chance = value;
        }
         void set_min_black_hole_range_factor(float const value) {
            m_min_black_hole_range_factor = value;
        }
         void set_max_black_hole_range_factor(float const value) {
            m_max_black_hole_range_factor = value;
        }
         void set_is_max_black_hole_range_factor(bool const value) {
            m_is_max_black_hole_range_factor = value;
        }
         void set_is_engine_problem(bool const value) {
            m_is_engine_problem = value;
        }
         void set_engine_problem_chance(utl::Probability const value) {
            m_engine_problem_chance = value;
        }
         void set_max_engine_problem_years(utl::usize const value) {
            m_max_engine_problem_years = value;
        }
         void set_is_production_problem(bool const value) {
            m_is_production_problem = value;
        }
         void set_production_problem_chance(utl::Probability const value) {
            m_production_problem_chance = value;
        }
         void set_max_production_problem_years(utl::usize const value) {
            m_max_production_problem_years = value;
        }
    };

} // namespace cst
