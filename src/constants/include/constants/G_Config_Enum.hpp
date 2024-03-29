//
// Purpur Tentakel
// 06.03.2024
// This is a generated file. Do not edit this file.
//

#pragma once

#include <string>


namespace cst {
    enum class G_Config_Enum {
        CONFIG,

        G_FIGHT,
        G_VERSION,
        G_FLEET,
        G_GAME_EVENTS,
        G_GLOBAL,
        G_PLANET,
        G_PLAYER,
        G_SOUND,
        G_WINDOW,
        G_WORLD,

        G_GLOBAL_CONFIG_SECTION_COUNT,
        G_VERSION_TOTAL_CONFIG_ENTRY_COUNT,
        G_VERSION_LOAD_CONFIG_ENTRY_COUNT,
        G_VERSION_GAME_VERSION,
        G_VERSION_CONFIG_VERSION,
        G_VERSION_LANGUAGE_VERSION,
        G_FIGHT_TOTAL_CONFIG_ENTRY_COUNT,
        G_FIGHT_LOAD_CONFIG_ENTRY_COUNT,
        G_FIGHT_HIT_CHANCE,
        G_FIGHT_FLEET_FIGHT_RANGE,
        G_FIGHT_IS_FIGHT_PLANET_FLEET,
        G_FIGHT_IS_FIGHT_TARGET_POINT_FLEET,
        G_FIGHT_IS_FIGHT_TARGET_POINT_TARGET_POINT,
        G_FIGHT_IS_FIGHT_PLANET_TARGET_POINT,
        G_FLEET_TOTAL_CONFIG_ENTRY_COUNT,
        G_FLEET_LOAD_CONFIG_ENTRY_COUNT,
        G_FLEET_MIN_FLEET_SPEED,
        G_FLEET_CURRENT_FLEET_SPEED,
        G_FLEET_MAX_FLEET_SPEED,
        G_GAME_EVENTS_TOTAL_CONFIG_ENTRY_COUNT,
        G_GAME_EVENTS_LOAD_CONFIG_ENTRY_COUNT,
        G_GAME_EVENTS_IS_MIN_EVENT_YEAR,
        G_GAME_EVENTS_MIN_EVENT_YEAR,
        G_GAME_EVENTS_IS_EVENT_ON_HOME_WORLD,
        G_GAME_EVENTS_GLOBAL_CHANCE,
        G_GAME_EVENTS_IS_PIRATES,
        G_GAME_EVENTS_PIRATE_CHANCE,
        G_GAME_EVENTS_MIN_PIRATE_SHIPS,
        G_GAME_EVENTS_MAX_PIRATE_SHIPS,
        G_GAME_EVENTS_IS_REVOLTS,
        G_GAME_EVENTS_REVOLTS_CHANCE,
        G_GAME_EVENTS_IS_RENEGADE_SHIPS,
        G_GAME_EVENTS_RENEGADE_SHIPS_CHANCE,
        G_GAME_EVENTS_IS_SUPERNOVA,
        G_GAME_EVENTS_SUPERNOVA_CHANCE,
        G_GAME_EVENTS_MIN_BLACK_HOLE_RANGE_FACTOR,
        G_GAME_EVENTS_MAX_BLACK_HOLE_RANGE_FACTOR,
        G_GAME_EVENTS_IS_MAX_BLACK_HOLE_RANGE_FACTOR,
        G_GAME_EVENTS_IS_ENGINE_PROBLEM,
        G_GAME_EVENTS_ENGINE_PROBLEM_CHANCE,
        G_GAME_EVENTS_MAX_ENGINE_PROBLEM_YEARS,
        G_GAME_EVENTS_IS_PRODUCTION_PROBLEM,
        G_GAME_EVENTS_PRODUCTION_PROBLEM_CHANCE,
        G_GAME_EVENTS_MAX_PRODUCTION_PROBLEM_YEARS,
        G_GLOBAL_TOTAL_CONFIG_ENTRY_COUNT,
        G_GLOBAL_LOAD_CONFIG_ENTRY_COUNT,
        G_GLOBAL_COPYRIGHT,
        G_GLOBAL_CURRENT_LANGUAGE_NAME,
        G_GLOBAL_MIN_ROUNDS,
        G_GLOBAL_MAX_ROUNDS,
        G_GLOBAL_CURRENT_TARGET_ROUND,
        G_GLOBAL_CURRENT_ROUND,
        G_PLANET_TOTAL_CONFIG_ENTRY_COUNT,
        G_PLANET_LOAD_CONFIG_ENTRY_COUNT,
        G_PLANET_MAX_SHIPS_FACTOR,
        G_PLANET_STARTING_HUMAN_SHIPS_MULTIPLIER,
        G_PLANET_STARTING_GLOBAL_SHIPS_MULTIPLIER,
        G_PLANET_HOME_WORLD_PRODUCTION,
        G_PLANET_MIN_PRODUCTION,
        G_PLANET_MAX_PRODUCTION,
        G_PLANET_HOME_WORLD_SPACING,
        G_PLANET_GLOBAL_SPACING,
        G_PLAYER_TOTAL_CONFIG_ENTRY_COUNT,
        G_PLAYER_LOAD_CONFIG_ENTRY_COUNT,
        G_PLAYER_MIN_COUNT,
        G_PLAYER_MAX_COUNT,
        G_PLAYER_IS_SHUFFLE,
        G_SOUND_TOTAL_CONFIG_ENTRY_COUNT,
        G_SOUND_LOAD_CONFIG_ENTRY_COUNT,
        G_SOUND_IS_MUTE,
        G_SOUND_MASTER_VOLUME,
        G_WINDOW_TOTAL_CONFIG_ENTRY_COUNT,
        G_WINDOW_LOAD_CONFIG_ENTRY_COUNT,
        G_WINDOW_CURRENT_RESOLUTION_ENUM,
        G_WINDOW_IS_FULL_SCREEN,
        G_WINDOW_FPS,
        G_WORLD_TOTAL_CONFIG_ENTRY_COUNT,
        G_WORLD_LOAD_CONFIG_ENTRY_COUNT,
        G_WORLD_MIN_PLANET_COUNT,
        G_WORLD_CURRENT_PLANET_COUNT,
        G_WORLD_MAX_PLANET_COUNT,
        G_WORLD_SHOW_PLANET_COUNT,
        G_WORLD_MIN_DIMENSION_X,
        G_WORLD_CURRENT_DIMENSION_X,
        G_WORLD_MAX_DIMENSION_X,
        G_WORLD_MIN_DIMENSION_Y,
        G_WORLD_CURRENT_DIMENSION_Y,
        G_WORLD_MAX_DIMENSION_Y,
        G_WORLD_SHOW_DIMENSION_X,
        G_WORLD_SHOW_DIMENSION_Y,
        G_WORLD_DISCOVER_RANGE_FACTOR,
    };

    [[nodiscard]] std::string CToS(G_Config_Enum value);

} // namespace cst
