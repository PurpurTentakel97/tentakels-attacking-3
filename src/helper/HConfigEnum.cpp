//
// Purpur Tentakel
// 08.06.2023
//

#include "HConfigEnum.h"

std::string CToS(ConfigTypes type) {
    switch (type) {
		case ConfigTypes::CONFIFG:
			return "config";
	
		case ConfigTypes::GAME_EVENTS:
			return "game_events";
		case ConfigTypes::PIRATES:
			return "pirates";
		case ConfigTypes::REVOLTS:
			return "revolts";
		case ConfigTypes::RENEGADE_SHIPS:
			return "renegade_ships";
		case ConfigTypes::BLACK_HOLE:
			return "black_hole";
		case ConfigTypes::SUPERNOVA:
			return "supernova";
		case ConfigTypes::ENGINE_PROBLEM:
			return "engine_problems";
		case ConfigTypes::GLOBAL_EVENT_CHANCE:
			return "global_event_chance";

		case ConfigTypes::FIGHT:
			return "fight";
		case ConfigTypes::HIT_CHANCE:
			return "hit_chance";
		case ConfigTypes::FLEET_FIGHT_RANGE:
			return "fleet_fight_range";
		case ConfigTypes::FIGHT_PLANET_FLEET:
			return "fight_planet_fleet";
		case ConfigTypes::FIGHT_TARGET_POINT_FLEET:
			return "fight_target_point_fleet";
		case ConfigTypes::FIGHT_TARGET_POINT_TARGET_POINT:
			return "fight_target_point_target_point";
		case ConfigTypes::FIGHT_PLANET_TARGET_POINT:
			return "fight_planet_target_point";

		case ConfigTypes::FLEET:
			return "fleet";
		case ConfigTypes::FLEET_SPEED_CURRENT:
			return "fleet_speed_current";
		case ConfigTypes::FLEET_SPEED_MAX:
			return "fleet_speed_max";
		case ConfigTypes::FLEET_SPEED_MIN:
			return "fleet_speed_min";
	
		case ConfigTypes::GLOBAL:
			return "global";
		case ConfigTypes::CURRENT_LANGUAGE_NAME:
			return "current_language_name";
		case ConfigTypes::GAME_ROUNDS_CURRENT:
			return "game_rounds_current";
		case ConfigTypes::GAME_ROUNDS_MAX:
			return "game_rounds_max";
		case ConfigTypes::GAME_ROUNDS_MIN:
			return "game_rounds_min";

		case ConfigTypes::PLANET:
			return "planet";
		case ConfigTypes::PRODUCTION_HOMEWORLD:
			return "production_homeworld";
		case ConfigTypes::PRODUCTION_MAX:
			return "production_max";
		case ConfigTypes::PRODUCTION_MIN:
			return "production_min";
		case ConfigTypes::SHIPS_MAX_FACTOR:
			return "ships_max_factor";
		case ConfigTypes::SPACEING_GLOBAL:
			return "spacing_global";
		case ConfigTypes::SPACEING_HOMEWORLD:
			return "spacing_homeworld";
		case ConfigTypes::STARTING_SHIPS_MULTIPLICATOR_GLOBAL:
			return "starting_ships_multiplicator_global";
		case ConfigTypes::STARTING_SHIPS_MULTIPLICATOR_HUMAN:
			return "starting_ships_multiplicator_human";

		case ConfigTypes::PLAYER:
			return "player";
		case ConfigTypes::PLAYER_COUNT_MAX:
			return "player_count_max";
		case ConfigTypes::PLAYER_COUNT_MIN:
			return "player_count_min";
		case ConfigTypes::Player_SHUFFLE:
			return "player_shuffle";

		case ConfigTypes::SOUND:
			return "sound";
		case ConfigTypes::VOLUME_MASTER:
			return "volume_master";
		case ConfigTypes::VOLUME_MUTE_BOOL:
			return "volume_mute_bool";
			
		case ConfigTypes::VERSION:
			return "version";
		case ConfigTypes::VERSION_CONFIG:
			return "version_config";
		case ConfigTypes::VERSION_GAME:
			return "version_game";

		case ConfigTypes::WINDOW:
			return "window";
		case ConfigTypes::RESOLUTION_AS_ENUM:
			return "resolution_as_enum";
		case ConfigTypes::FULL_SCREEN_BOOL:
			return "full_screen_bool";
		case ConfigTypes::TARGET_FPS:
			return "target_fps";

		case ConfigTypes::WORLD:
			return "world";
		case ConfigTypes::DIMENSION_X_CURRENT:
			return "dimension_x_current";
		case ConfigTypes::DIMENSION_X_MAX:
			return "dimension_x_max";
		case ConfigTypes::DIMENSION_X_MIN:
			return "dimension_x_min";
		case ConfigTypes::DIMENSION_X_SHOW_GALAXY:
			return "dimension_x_show_galaxy";
		case ConfigTypes::DIMENSION_Y_CURRENT:
			return "dimension_y_current";
		case ConfigTypes::DIMENSION_Y_MAX:
			return "dimension_y_max";
		case ConfigTypes::DIMENSION_Y_MIN:
			return "dimension_y_min";
		case ConfigTypes::DIMENSION_Y_SHOW_GALAXY:
			return "dimension_y_show_galaxy";
		case ConfigTypes::DISCOVER_RANGE_FACTOR:
			return "discover_range_factor";
		case ConfigTypes::PLANET_COUNT_CURRENT:
			return "planet_count_current";
		case ConfigTypes::PLANET_COUNT_MAX:
			return "planet_count_max";
		case ConfigTypes::PLANET_COUNT_MIN:
			return "planet_count_min";
		case ConfigTypes::PLANET_COUNT_SHOW_GALAXY:
			return "planet_count_show_galaxy";

		default:
			return "missing_config_type";
    }
}
