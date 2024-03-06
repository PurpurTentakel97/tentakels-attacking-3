//
// Purpur Tentakel
// 06.03.2024
// This is a generated file. Do not edit this file.
//

#include "G_Config_Enum.hpp"
#include <utility>


namespace cst {
    std::string CToS(G_Config_Enum const value) {
        switch (value) {
            case G_Config_Enum::CONFIG: return "config";

            case G_Config_Enum::G_FIGHT: return "fight";
            case G_Config_Enum::G_VERSION: return "version";
            case G_Config_Enum::G_FLEET: return "fleet";
            case G_Config_Enum::G_GAME_EVENTS: return "game_events";
            case G_Config_Enum::G_GLOBAL: return "global";
            case G_Config_Enum::G_PLANET: return "planet";
            case G_Config_Enum::G_PLAYER: return "player";
            case G_Config_Enum::G_SOUND: return "sound";

            case G_Config_Enum::G_GLOBAL_CONFIG_SECTION_COUNT: return "config_section_count";
            case G_Config_Enum::G_FIGHT_TOTAL_CONFIG_ENTRY_COUNT: return "total_config_entry_count";
            case G_Config_Enum::G_FIGHT_LOAD_CONFIG_ENTRY_COUNT: return "load_config_entry_count";
            case G_Config_Enum::G_FIGHT_HIT_CHANCE: return "hit_chance";
            case G_Config_Enum::G_FIGHT_FLEET_FIGHT_RANGE: return "fleet_fight_range";
            case G_Config_Enum::G_FIGHT_IS_FIGHT_PLANET_FLEET: return "is_fight_planet_fleet";
            case G_Config_Enum::G_FIGHT_IS_FIGHT_TARGET_POINT_FLEET: return "is_fight_target_point_fleet";
            case G_Config_Enum::G_FIGHT_IS_FIGHT_TARGET_POINT_TARGET_POINT: return "is_fight_target_point_target_point";
            case G_Config_Enum::G_FIGHT_IS_FIGHT_PLANET_TARGET_POINT: return "is_fight_planet_target_point";
            case G_Config_Enum::G_VERSION_TOTAL_CONFIG_ENTRY_COUNT: return "total_config_entry_count";
            case G_Config_Enum::G_VERSION_LOAD_CONFIG_ENTRY_COUNT: return "load_config_entry_count";
            case G_Config_Enum::G_VERSION_GAME_VERSION: return "game_version";
            case G_Config_Enum::G_VERSION_CONFIG_VERSION: return "config_version";
            case G_Config_Enum::G_VERSION_LANGUAGE_VERSION: return "language_version";
            case G_Config_Enum::G_FLEET_TOTAL_CONFIG_ENTRY_COUNT: return "total_config_entry_count";
            case G_Config_Enum::G_FLEET_LOAD_CONFIG_ENTRY_COUNT: return "load_config_entry_count";
            case G_Config_Enum::G_FLEET_MIN_FLEET_SPEED: return "min_fleet_speed";
            case G_Config_Enum::G_FLEET_CURRENT_FLEET_SPEED: return "current_fleet_speed";
            case G_Config_Enum::G_FLEET_MAX_FLEET_SPEED: return "max_fleet_speed";
            case G_Config_Enum::G_GAME_EVENTS_TOTAL_CONFIG_ENTRY_COUNT: return "total_config_entry_count";
            case G_Config_Enum::G_GAME_EVENTS_LOAD_CONFIG_ENTRY_COUNT: return "load_config_entry_count";
            case G_Config_Enum::G_GAME_EVENTS_IS_MIN_EVENT_YEAR: return "is_min_event_year";
            case G_Config_Enum::G_GAME_EVENTS_MIN_EVENT_YEAR: return "min_event_year";
            case G_Config_Enum::G_GAME_EVENTS_IS_EVENT_ON_HOME_WORLD: return "is_event_on_home_world";
            case G_Config_Enum::G_GAME_EVENTS_GLOBAL_CHANCE: return "global_chance";
            case G_Config_Enum::G_GAME_EVENTS_IS_PIRATES: return "is_pirates";
            case G_Config_Enum::G_GAME_EVENTS_PIRATE_CHANCE: return "pirate_chance";
            case G_Config_Enum::G_GAME_EVENTS_MIN_PIRATE_SHIPS: return "min_pirate_ships";
            case G_Config_Enum::G_GAME_EVENTS_MAX_PIRATE_SHIPS: return "max_pirate_ships";
            case G_Config_Enum::G_GAME_EVENTS_IS_REVOLTS: return "is_revolts";
            case G_Config_Enum::G_GAME_EVENTS_REVOLTS_CHANCE: return "revolts_chance";
            case G_Config_Enum::G_GAME_EVENTS_IS_RENEGADE_SHIPS: return "is_renegade_ships";
            case G_Config_Enum::G_GAME_EVENTS_RENEGADE_SHIPS_CHANCE: return "renegade_ships_chance";
            case G_Config_Enum::G_GAME_EVENTS_IS_SUPERNOVA: return "is_supernova";
            case G_Config_Enum::G_GAME_EVENTS_SUPERNOVA_CHANCE: return "supernova_chance";
            case G_Config_Enum::G_GAME_EVENTS_MIN_BLACK_HOLE_RANGE_FACTOR: return "min_black_hole_range_factor";
            case G_Config_Enum::G_GAME_EVENTS_MAX_BLACK_HOLE_RANGE_FACTOR: return "max_black_hole_range_factor";
            case G_Config_Enum::G_GAME_EVENTS_IS_MAX_BLACK_HOLE_RANGE_FACTOR: return "is_max_black_hole_range_factor";
            case G_Config_Enum::G_GAME_EVENTS_IS_ENGINE_PROBLEM: return "is_engine_problem";
            case G_Config_Enum::G_GAME_EVENTS_ENGINE_PROBLEM_CHANCE: return "engine_problem_chance";
            case G_Config_Enum::G_GAME_EVENTS_MAX_ENGINE_PROBLEM_YEARS: return "max_engine_problem_years";
            case G_Config_Enum::G_GAME_EVENTS_IS_PRODUCTION_PROBLEM: return "is_production_problem";
            case G_Config_Enum::G_GAME_EVENTS_PRODUCTION_PROBLEM_CHANCE: return "production_problem_chance";
            case G_Config_Enum::G_GAME_EVENTS_MAX_PRODUCTION_PROBLEM_YEARS: return "max_production_problem_years";
            case G_Config_Enum::G_GLOBAL_TOTAL_CONFIG_ENTRY_COUNT: return "total_config_entry_count";
            case G_Config_Enum::G_GLOBAL_LOAD_CONFIG_ENTRY_COUNT: return "load_config_entry_count";
            case G_Config_Enum::G_GLOBAL_COPYRIGHT: return "copyright";
            case G_Config_Enum::G_GLOBAL_CURRENT_LANGUAGE_NAME: return "current_language_name";
            case G_Config_Enum::G_GLOBAL_MIN_ROUNDS: return "min_rounds";
            case G_Config_Enum::G_GLOBAL_MAX_ROUNDS: return "max_rounds";
            case G_Config_Enum::G_GLOBAL_CURRENT_TARGET_ROUND: return "current_target_round";
            case G_Config_Enum::G_GLOBAL_CURRENT_ROUND: return "current_round";
            case G_Config_Enum::G_PLANET_TOTAL_CONFIG_ENTRY_COUNT: return "total_config_entry_count";
            case G_Config_Enum::G_PLANET_LOAD_CONFIG_ENTRY_COUNT: return "load_config_entry_count";
            case G_Config_Enum::G_PLANET_MAX_SHIPS_FACTOR: return "max_ships_factor";
            case G_Config_Enum::G_PLANET_STARTING_HUMAN_SHIPS_MULTIPLIER: return "starting_human_ships_multiplier";
            case G_Config_Enum::G_PLANET_STARTING_GLOBAL_SHIPS_MULTIPLIER: return "starting_global_ships_multiplier";
            case G_Config_Enum::G_PLANET_HOME_WORLD_PRODUCTION: return "home_world_production";
            case G_Config_Enum::G_PLANET_MIN_PRODUCTION: return "min_production";
            case G_Config_Enum::G_PLANET_MAX_PRODUCTION: return "max_production";
            case G_Config_Enum::G_PLANET_HOME_WORLD_SPACING: return "home_world_spacing";
            case G_Config_Enum::G_PLANET_GLOBAL_SPACING: return "global_spacing";
            case G_Config_Enum::G_PLAYER_TOTAL_CONFIG_ENTRY_COUNT: return "total_config_entry_count";
            case G_Config_Enum::G_PLAYER_LOAD_CONFIG_ENTRY_COUNT: return "load_config_entry_count";
            case G_Config_Enum::G_PLAYER_MIN_COUNT: return "min_count";
            case G_Config_Enum::G_PLAYER_MAX_COUNT: return "max_count";
            case G_Config_Enum::G_PLAYER_IS_SHUFFLE: return "is_shuffle";
            case G_Config_Enum::G_SOUND_TOTAL_CONFIG_ENTRY_COUNT: return "total_config_entry_count";
            case G_Config_Enum::G_SOUND_LOAD_CONFIG_ENTRY_COUNT: return "load_config_entry_count";
            case G_Config_Enum::G_SOUND_IS_MUTE: return "is_mute";
            case G_Config_Enum::G_SOUND_MASTER_VOLUME: return "master_volume";
        }
    std::unreachable();
    }

} // namespace cst
