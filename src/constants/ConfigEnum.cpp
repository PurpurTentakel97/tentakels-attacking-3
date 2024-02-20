//
// Purpur Tentakel
// 08.06.2023
//

#include "CConfigEnum.hpp"

namespace cst {
    std::string CToS(ConfigTypes const type) {
        switch (type) {
                // clang-format off
            case ConfigTypes::CONFIG: return "config";

            case ConfigTypes::GAME_EVENTS:                    return "game_events"                    ;
            case ConfigTypes::GLOBAL_EVENT_CHANCE:            return "global_event_chance"            ;
            case ConfigTypes::IS_MIN_EVENT_YEAR:              return "is_min_event_year"              ;
            case ConfigTypes::MIN_EVENT_YEAR:                 return "min_event_year"                 ;
            case ConfigTypes::IS_EVENT_ON_HOME_WORLD:         return "is_event_on_home_world"         ;
            case ConfigTypes::PIRATES:                        return "pirates"                        ;
            case ConfigTypes::PIRATES_CHANCE:                 return "pirates_chance"                 ;
            case ConfigTypes::REVOLTS:                        return "revolts"                        ;
            case ConfigTypes::REVOLTS_CHANCE:                 return "revolts_chance"                 ;
            case ConfigTypes::RENEGADE_SHIPS:                 return "renegade_ships"                 ;
            case ConfigTypes::RENEGADE_SHIPS_CHANCE:          return "renegade_ships_chance"          ;
            case ConfigTypes::SUPERNOVA:                      return "supernova"                      ;
            case ConfigTypes::SUPERNOVA_CHANCE:               return "supernova_chance"               ;
            case ConfigTypes::MIN_BLACK_HOLE_RANGE_FACTOR:    return "min_black_hole_range_factor"    ;
            case ConfigTypes::IS_MAX_BLACK_HOLE_RANGE_FACTOR: return "is_max_black_hole_range_factor" ;
            case ConfigTypes::MAX_BLACK_HOLE_RANGE_FACTOR:    return "max_black_hole_range_factor"    ;
            case ConfigTypes::ENGINE_PROBLEM:                 return "engine_problem"                 ;
            case ConfigTypes::ENGINE_PROBLEM_CHANCE:          return "engine_problem_chance"          ;
            case ConfigTypes::MAX_YEARS_ENGINE_PROBLEM:       return "max_years_engine_problem"       ;

            case ConfigTypes::FIGHT:                           return "fight"                          ;
            case ConfigTypes::HIT_CHANCE:                      return "hit_chance"                     ;
            case ConfigTypes::FLEET_FIGHT_RANGE:               return "fleet_fight_range"              ;
            case ConfigTypes::FIGHT_PLANET_FLEET:              return "fight_planet_fleet"             ;
            case ConfigTypes::FIGHT_TARGET_POINT_FLEET:        return "fight_target_point_fleet"       ;
            case ConfigTypes::FIGHT_TARGET_POINT_TARGET_POINT: return "fight_target_point_target_point";
            case ConfigTypes::FIGHT_PLANET_TARGET_POINT:       return "fight_planet_target_point"      ;

            case ConfigTypes::FLEET:               return "fleet"              ;
            case ConfigTypes::FLEET_SPEED_CURRENT: return "fleet_speed_current";
            case ConfigTypes::FLEET_SPEED_MAX:     return "fleet_speed_max"    ;
            case ConfigTypes::FLEET_SPEED_MIN:     return "fleet_speed_min"    ;

            case ConfigTypes::GLOBAL:                return "global"               ;
            case ConfigTypes::CURRENT_LANGUAGE_NAME: return "current_language_name";
            case ConfigTypes::GAME_ROUNDS_CURRENT:   return "game_rounds_current"  ;
            case ConfigTypes::GAME_ROUNDS_MAX:       return "game_rounds_max"      ;
            case ConfigTypes::GAME_ROUNDS_MIN:       return "game_rounds_min"      ;

            case ConfigTypes::PLANET:                           return "planet"                          ;
            case ConfigTypes::PRODUCTION_HOME_WORLD:            return "production_home_world"           ;
            case ConfigTypes::PRODUCTION_MAX:                   return "production_max"                  ;
            case ConfigTypes::PRODUCTION_MIN:                   return "production_min"                  ;
            case ConfigTypes::SHIPS_MAX_FACTOR:                 return "ships_max_factor"                ;
            case ConfigTypes::SPACING_GLOBAL:                   return "spacing_global"                  ;
            case ConfigTypes::SPACING_HOME_WORLD:               return "spacing_home_world"              ;
            case ConfigTypes::STARTING_SHIPS_MULTIPLIER_GLOBAL: return "starting_ships_multiplier_global";
            case ConfigTypes::STARTING_SHIPS_MULTIPLIER_HUMAN:  return "starting_ships_multiplier_human" ;

            case ConfigTypes::PLAYER:           return "player"          ;
            case ConfigTypes::PLAYER_COUNT_MAX: return "player_count_max";
            case ConfigTypes::PLAYER_COUNT_MIN: return "player_count_min";
            case ConfigTypes::Player_SHUFFLE:   return "player_shuffle"  ;

            case ConfigTypes::SOUND:            return "sound"           ;
            case ConfigTypes::VOLUME_MASTER:    return "volume_master"   ;
            case ConfigTypes::VOLUME_MUTE_BOOL: return "volume_mute_bool";

            case ConfigTypes::VERSION:        return "version"       ;
            case ConfigTypes::VERSION_CONFIG: return "version_config";
            case ConfigTypes::VERSION_GAME:   return "version_game"  ;

            case ConfigTypes::WINDOW:             return "window"            ;
            case ConfigTypes::RESOLUTION_AS_ENUM: return "resolution_as_enum";
            case ConfigTypes::FULL_SCREEN_BOOL:   return "full_screen_bool"  ;
            case ConfigTypes::TARGET_FPS:         return "target_fps"        ;

            case ConfigTypes::WORLD:                    return "world"                   ;
            case ConfigTypes::DIMENSION_X_CURRENT:      return "dimension_x_current"     ;
            case ConfigTypes::DIMENSION_X_MAX:          return "dimension_x_max"         ;
            case ConfigTypes::DIMENSION_X_MIN:          return "dimension_x_min"         ;
            case ConfigTypes::DIMENSION_X_SHOW_GALAXY:  return "dimension_x_show_galaxy" ;
            case ConfigTypes::DIMENSION_Y_CURRENT:      return "dimension_y_current"     ;
            case ConfigTypes::DIMENSION_Y_MAX:          return "dimension_y_max"         ;
            case ConfigTypes::DIMENSION_Y_MIN:          return "dimension_y_min"         ;
            case ConfigTypes::DIMENSION_Y_SHOW_GALAXY:  return "dimension_y_show_galaxy" ;
            case ConfigTypes::DISCOVER_RANGE_FACTOR:    return "discover_range_factor"   ;
            case ConfigTypes::PLANET_COUNT_CURRENT:     return "planet_count_current"    ;
            case ConfigTypes::PLANET_COUNT_MAX:         return "planet_count_max"        ;
            case ConfigTypes::PLANET_COUNT_MIN:         return "planet_count_min"        ;
            case ConfigTypes::PLANET_COUNT_SHOW_GALAXY: return "planet_count_show_galaxy";

            default: return "missing_config_type";
                // clang-format on
        }
    }
} // namespace cst
