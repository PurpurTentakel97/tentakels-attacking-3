//
// Purpur Tentakel
// 06.03.2024
// This is a generated file. Do not edit this file.
//

#include "G_ConfigEnum.hpp"
#include <utility>

namespace cst {
    std::string CToS(G_ConfigEnum const value) {
        switch (value) {
            case G_ConfigEnum::CONFIG: return "config";

            case G_ConfigEnum::G_FIGHT: return "fight";
            case G_ConfigEnum::G_VERSION: return "version";
            case G_ConfigEnum::G_FLEET: return "fleet";

            case G_ConfigEnum::G_FIGHT_TOTAL_CONFIG_ENTRY_COUNT: return "total_config_entry_count";
            case G_ConfigEnum::G_FIGHT_LOAD_CONFIG_ENTRY_COUNT: return "load_config_entry_count";
            case G_ConfigEnum::G_FIGHT_HIT_CHANCE: return "hit_chance";
            case G_ConfigEnum::G_FIGHT_FLEET_FIGHT_RANGE: return "fleet_fight_range";
            case G_ConfigEnum::G_FIGHT_IS_FIGHT_PLANET_FLEET: return "is_fight_planet_fleet";
            case G_ConfigEnum::G_FIGHT_IS_FIGHT_TARGET_POINT_FLEET: return "is_fight_target_point_fleet";
            case G_ConfigEnum::G_FIGHT_IS_FIGHT_TARGET_POINT_TARGET_POINT: return "is_fight_target_point_target_point";
            case G_ConfigEnum::G_FIGHT_IS_FIGHT_PLANET_TARGET_POINT: return "is_fight_planet_target_point";
            case G_ConfigEnum::G_VERSION_TOTAL_CONFIG_ENTRY_COUNT: return "total_config_entry_count";
            case G_ConfigEnum::G_VERSION_LOAD_CONFIG_ENTRY_COUNT: return "load_config_entry_count";
            case G_ConfigEnum::G_VERSION_GAME_VERSION: return "game_version";
            case G_ConfigEnum::G_VERSION_CONFIG_VERSION: return "config_version";
            case G_ConfigEnum::G_VERSION_LANGUAGE_VERSION: return "language_version";
            case G_ConfigEnum::G_FLEET_TOTAL_CONFIG_ENTRY_COUNT: return "total_config_entry_count";
            case G_ConfigEnum::G_FLEET_LOAD_CONFIG_ENTRY_COUNT: return "load_config_entry_count";
            case G_ConfigEnum::G_FLEET_MIN_FLEET_SPEED: return "min_fleet_speed";
            case G_ConfigEnum::G_FLEET_CURRENT_FLEET_SPEED: return "current_fleet_speed";
            case G_ConfigEnum::G_FLEET_MAX_FLEET_SPEED: return "max_fleet_speed";
        }
    std::unreachable();
    }

} // namespace cst
