//
// Purpur Tentakel
// 08.06.2023
//

#pragma once

#include <string>

namespace cst {
    enum class ConfigTypes {
        CONFIG,

        GAME_EVENTS,
        PIRATES,
        REVOLTS,
        RENEGADE_SHIPS,
        BLACK_HOLE,
        SUPERNOVA,
        ENGINE_PROBLEM,
        GLOBAL_EVENT_CHANCE,
        PIRATES_CHANCE,
        REVOLTS_CHANCE,
        RENEGADE_SHIPS_CHANCE,
        BLACK_HOLE_CHANCE,
        SUPERNOVA_CHANCE,
        ENGINE_PROBLEM_CHANCE,
        MAX_YEARS_ENGINE_PROBLEM,
        MIN_EVENT_YEAR,
        IS_MIN_EVENT_YEAR,

        FIGHT,
        HIT_CHANCE,
        FLEET_FIGHT_RANGE,
        FIGHT_PLANET_FLEET,
        FIGHT_TARGET_POINT_FLEET,
        FIGHT_TARGET_POINT_TARGET_POINT,
        FIGHT_PLANET_TARGET_POINT,

        FLEET,
        FLEET_SPEED_CURRENT,
        FLEET_SPEED_MAX,
        FLEET_SPEED_MIN,

        GLOBAL,
        CURRENT_LANGUAGE_NAME,
        GAME_ROUNDS_CURRENT,
        GAME_ROUNDS_MAX,
        GAME_ROUNDS_MIN,

        PLANET,
        PRODUCTION_HOME_WORLD,
        PRODUCTION_MAX,
        PRODUCTION_MIN,
        SHIPS_MAX_FACTOR,
        SPACING_GLOBAL,
        SPACING_HOME_WORLD,
        STARTING_SHIPS_MULTIPLIER_GLOBAL,
        STARTING_SHIPS_MULTIPLIER_HUMAN,

        PLAYER,
        PLAYER_COUNT_MAX,
        PLAYER_COUNT_MIN,
        Player_SHUFFLE,

        SOUND,
        VOLUME_MASTER,
        VOLUME_MUTE_BOOL,

        VERSION,
        VERSION_CONFIG,
        VERSION_GAME,

        WINDOW,
        RESOLUTION_AS_ENUM,
        FULL_SCREEN_BOOL,
        TARGET_FPS,

        WORLD,
        DIMENSION_X_CURRENT,
        DIMENSION_X_MAX,
        DIMENSION_X_MIN,
        DIMENSION_X_SHOW_GALAXY,
        DIMENSION_Y_CURRENT,
        DIMENSION_Y_MAX,
        DIMENSION_Y_MIN,
        DIMENSION_Y_SHOW_GALAXY,
        DISCOVER_RANGE_FACTOR,
        PLANET_COUNT_CURRENT,
        PLANET_COUNT_MAX,
        PLANET_COUNT_MIN,
        PLANET_COUNT_SHOW_GALAXY,
    };

    [[nodiscard]] std::string CToS(ConfigTypes type);
} // namespace cst
