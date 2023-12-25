//
// Purpur Tentakel
// 27.10.2022
//

#include "ConfigIO.h"
#include "AppContext.h"
#include "helper/HPrint.h"
#include "helper/HConfigEnum.h"
#include <filesystem>
#include <nlohmann/json.hpp>
#include <cassert>

// string defaults
static std::string const defaultValuePrefix{ "-> using default value -> overwrite config by save" };
static int loadEntryCount{ 0 };
// print
auto static const printMissingSection{ [](ConfigTypes section) {
	Print(
		PrintType::ERROR,
		"section \"{}\" in config missing {}",
		CToS(section),
		defaultValuePrefix
	);
} };
auto static const printMissingEntry{ [](ConfigTypes entry) {
	Print(
		PrintType::ERROR,
		"entry \"{}\" in config missing {}",
		CToS(entry),
		defaultValuePrefix
	);
} };
auto static const printNotMatchingCount{ [](ConfigTypes section, size_t expected, size_t provided) {
    Print(
		PrintType::ERROR,
		"section \"{}\" entry count in config is not matching -> expected: \"{}\" -> provided: \"{}\"",
		CToS(section),
		expected,
		provided
		);
} };
auto static const printWrongDatatype{ [](ConfigTypes entry) {
	Print(
		PrintType::ERROR,
		"entry \"{}\" in config has wrong datatype {}",
		CToS(entry),
		defaultValuePrefix
		);
} };

// check
auto static const isNull{ [](nlohmann::json const& son, ConfigTypes type) ->bool {
	assert(not son.is_null());
	if (son.is_array()) {
		printMissingSection(type);
		return true;
	}
	return false;
} };
auto static const isExistingSection{ [](nlohmann::json const& son, ConfigTypes type) ->bool {
	assert(son.contains(CToS(type)));
	if (not son.contains(CToS(type))) {
		printMissingSection(type);
		return false;
	}
	return true;
} };
auto static const isExistingEntry{ [](nlohmann::json const& son, ConfigTypes type) ->bool {
	assert(son.contains(CToS(type)));
	if (not son.contains(CToS(type))) {
		printMissingEntry(type);
		return false;
	}
	return true;
} };
auto static const isMatchingSize{ [](nlohmann::json const& son, ConfigTypes section, size_t count) -> bool {
    assert(son.size() == count);
	if (son.size() != count) {
		printNotMatchingCount(section, count, son.size());
		return false;
	}
	return true;
} };

// load
auto static const loadSection{ [](nlohmann::json const& son, nlohmann::json& out, ConfigTypes section, size_t count
                               ) -> bool {
    if (not isExistingSection(son, section)) {
		return false;
	}
	son.at(CToS(section)).get_to(out);

	if (isNull(out, section)) { return false; }
	isMatchingSize(out, section, count);

	return true;
} };
auto static const loadString{ [](nlohmann::json const& son, std::string& out, ConfigTypes entry) -> bool  {
	++loadEntryCount;
	if (not isExistingEntry(son, entry)) {
		return false;
    }
	assert(son.at(CToS(entry)).is_string());
	if (not son.at(CToS(entry)).is_string()) {
		printWrongDatatype(entry);
		return false;
	}

	son.at(CToS(entry)).get_to(out);
	return true;
} };
auto static const loadInt{ [](nlohmann::json const& son, int& out, ConfigTypes entry) -> bool {
	++loadEntryCount;
	if (not isExistingEntry(son, entry)) {
		return false;

	}
	assert(son.at(CToS(entry)).is_number_integer());
	if (not son.at(CToS(entry)).is_number_integer()) {
		printWrongDatatype(entry);
		return false;
	}

	son.at(CToS(entry)).get_to(out);
	return true;
} };
auto static const loadFloat{ [](nlohmann::json const& son, float& out, ConfigTypes entry) -> bool {
	++loadEntryCount;
	if (not isExistingEntry(son, entry)) {
		return false;

	}
	assert(son.at(CToS(entry)).is_number_float());
	if (not son.at(CToS(entry)).is_number_float()) {
		printWrongDatatype(entry);
		return false;
	}

	son.at(CToS(entry)).get_to(out);
	return true;
} };
auto static const loadBool{ [](nlohmann::json const& son, bool& out, ConfigTypes entry) -> bool {
	++loadEntryCount;
	if (not isExistingEntry(son, entry)) {
		return false;

	}
	assert(son.at(CToS(entry)).is_boolean());
	if (not son.at(CToS(entry)).is_boolean()) {
		printWrongDatatype(entry);
		return false;
	}

	son.at(CToS(entry)).get_to(out);
	return true;
} };

void LoadConfig() {
	// load file
	loadEntryCount = { 0 };
	auto& constants = AppContext::GetInstance().constants;
	std::ifstream file;

	if (!std::filesystem::exists(constants.files.configFile())) {
		Print(PrintType::EXPECTED_ERROR, "no config existing");
		SaveConfig();
		return;
	}

	file.open(constants.files.configFile());
	if (!file.is_open()) {
		Print(PrintType::INFO, "cant open config");
		return;
	}

	nlohmann::json load;
	file >> load;
	file.close();

	// from json
	// config
    if (isNull(load, ConfigTypes::CONFIFG)) {
        Print(
			PrintType::ERROR,
			"provided config is null {}",
			defaultValuePrefix
		);
		return;
	}
	if (not isMatchingSize(load, ConfigTypes::CONFIFG, constants.global.configSectionCount)) {
		Print(
			PrintType::ERROR,
			"config section count is not matching {} -> expected: {} -> provided: {}",
			defaultValuePrefix,
			constants.global.configSectionCount,
			load.size()
		);
	};
	// version
	if (nlohmann::json version; loadSection(load, version, ConfigTypes::VERSION, constants.global.configVersionCount)) {
		if (std::string versionConfig; loadString(version, versionConfig, ConfigTypes::VERSION_CONFIG)) {
			if (versionConfig != constants.global.configVersion) {
				Print(
					PrintType::ERROR,
					"config version in config is not matching -> expected: {} -> provided: {} -> overwrite config by save",
					constants.global.configVersion,
					versionConfig
				);
			}
			else {
				Print(
					PrintType::INFO,
					"config versions matching -> version: {}",
					versionConfig
				);
			}
		}
		else {
			Print(PrintType::ERROR, "unable to check if config version is matching");
		}
		if (std::string versionGame; loadString(version, versionGame, ConfigTypes::VERSION_GAME)) {
			if (versionGame != constants.global.gameVersion) {
				Print(
					PrintType::ERROR,
					"game version in config is not matching -> expected: {} -> provided: {} -> overwrite by save",
					constants.global.gameVersion,
					versionGame
				);
			}
			else {
				Print(
					PrintType::INFO,
					"game versions matching -> version: {}",
					versionGame
				);
			}
		}
		else {
			Print(PrintType::ERROR, "unable to check if config version is matching");
		}
	}
	else {
		Print(PrintType::ERROR, "not able to check if config and game versions match");
	}
    // @formatter:off
    // fight
	if (nlohmann::json fight; loadSection(load, fight, ConfigTypes::FIGHT, constants.fight.configEntryCount)) {
		if (float out; loadFloat(fight, out, ConfigTypes::HIT_CHANCE))                      { constants.fight.hitChance                     = out; }
		if (int   out;   loadInt(fight, out, ConfigTypes::FLEET_FIGHT_RANGE))               { constants.fight.fleetFightRange               = out; }
		if (bool  out;  loadBool(fight, out, ConfigTypes::FIGHT_PLANET_FLEET))              { constants.fight.isFightPlanetFleet            = out; }
		if (bool  out;  loadBool(fight, out, ConfigTypes::FIGHT_PLANET_TARGET_POINT))       { constants.fight.isFightPlanetTargetPoint      = out; }
		if (bool  out;  loadBool(fight, out, ConfigTypes::FIGHT_TARGET_POINT_FLEET))        { constants.fight.isFightTargetPointFleet       = out; }
		if (bool  out;  loadBool(fight, out, ConfigTypes::FIGHT_TARGET_POINT_TARGET_POINT)) { constants.fight.isFightTargetPointTargetPoint = out; }
	}
	// fleet
	if (nlohmann::json events; loadSection(load, events, ConfigTypes::GAME_EVENTS, constants.gameEvents.configEntryCount)) {
		if (bool  out;  loadBool(events, out, ConfigTypes::PIRATES))             { constants.gameEvents.SetFlag(HGameEventType::PIRATES,        out); }
		if (bool  out;  loadBool(events, out, ConfigTypes::REVOLTS))             { constants.gameEvents.SetFlag(HGameEventType::REVOLTS,        out); }
		if (bool  out;  loadBool(events, out, ConfigTypes::RENEGADE_SHIPS))      { constants.gameEvents.SetFlag(HGameEventType::RENEGADE_SHIPS, out); }
		if (bool  out;  loadBool(events, out, ConfigTypes::BLACK_HOLE))          { constants.gameEvents.SetFlag(HGameEventType::BLACK_HOLE,     out); }
		if (bool  out;  loadBool(events, out, ConfigTypes::SUPERNOVA))           { constants.gameEvents.SetFlag(HGameEventType::SUPERNOVA,      out); }
		if (bool  out;  loadBool(events, out, ConfigTypes::ENGINE_PROBLEM))      { constants.gameEvents.SetFlag(HGameEventType::ENGINE_PROBLEM, out); }
		if (float out; loadFloat(events, out, ConfigTypes::GLOBAL_EVENT_CHANCE)) { constants.gameEvents.globalEventChance = out; }
	}
	// game events
	if (nlohmann::json fleet; loadSection(load, fleet, ConfigTypes::FLEET, constants.fleet.configEntryCount)) {
		if (int out; loadInt(fleet, out, ConfigTypes::FLEET_SPEED_CURRENT)) { constants.fleet.currentFleetSpeed = out; }
		if (int out; loadInt(fleet, out, ConfigTypes::FLEET_SPEED_MAX))     { constants.fleet.maxFleetSpeed     = out; }
		if (int out; loadInt(fleet, out, ConfigTypes::FLEET_SPEED_MIN))     { constants.fleet.minFleetSpeed     = out; }
	}
	// global
	if (nlohmann::json global; loadSection(load, global, ConfigTypes::GLOBAL, constants.global.configEntryCount)) {
		if (std::string out; loadString(global, out, ConfigTypes::CURRENT_LANGUAGE_NAME)) { constants.global.currentLanguageName = out; }
        if (int out; loadInt(global, out, ConfigTypes::GAME_ROUNDS_CURRENT)) {
            constants.global.currentTargetRound = static_cast<size_t>(out);
        }
        if (int out; loadInt(global, out, ConfigTypes::GAME_ROUNDS_MAX)) {
            constants.global.maxRounds = static_cast<size_t>(out);
        }
        if (int out; loadInt(global, out, ConfigTypes::GAME_ROUNDS_MIN)) {
            constants.global.minRounds = static_cast<size_t>(out);
        }
    }
	// planet
	if (nlohmann::json planet; loadSection(load, planet, ConfigTypes::PLANET, constants.planet.configEntryCount)) {
        if (int out; loadInt(planet, out, ConfigTypes::PRODUCTION_HOMEWORLD)) {
            constants.planet.homeworldProduction = static_cast<size_t>(out);
        }
        if (int out; loadInt(planet, out, ConfigTypes::PRODUCTION_MAX)) {
            constants.planet.maxProduction = static_cast<size_t>(out);
        }
        if (int out; loadInt(planet, out, ConfigTypes::PRODUCTION_MIN)) {
            constants.planet.minProduction = static_cast<size_t>(out);
        }
        if (int out; loadInt(planet, out, ConfigTypes::SHIPS_MAX_FACTOR)) {
            constants.planet.maxShipsFactor = static_cast<size_t>(out);
        }
        if (float out; loadFloat(planet, out, ConfigTypes::SPACEING_GLOBAL)) {
            constants.planet.globalSpacing = out;
        }
        if (float out; loadFloat(planet, out, ConfigTypes::SPACEING_HOMEWORLD)) {
            constants.planet.homeworldSpacing = out;
        }
        if (int out; loadInt(planet, out, ConfigTypes::STARTING_SHIPS_MULTIPLICATOR_GLOBAL)) {
            constants.planet.startingGlobalShipsMultiplicator = static_cast<size_t>(out);
        }
        if (int out; loadInt(planet, out, ConfigTypes::STARTING_SHIPS_MULTIPLICATOR_HUMAN)) {
            constants.planet.startingHumanShipsMultiplicator = static_cast<size_t>(out);
        }
    }
	// player
	if (nlohmann::json player; loadSection(load, player, ConfigTypes::PLAYER, constants.player.configEntryCount)) {
        if (int out; loadInt(player, out, ConfigTypes::PLAYER_COUNT_MAX)) {
            constants.player.maxPlayerCount = static_cast<size_t>(out);
        }
        if (int out; loadInt(player, out, ConfigTypes::PLAYER_COUNT_MIN)) {
            constants.player.minPlayerCount = static_cast<size_t>(out);
        }
        if (bool out; loadBool(player, out, ConfigTypes::Player_SHUFFLE)) {
            constants.player.shuffle = out;
        }
    }
	// sound
	if (nlohmann::json sound; loadSection(load, sound, ConfigTypes::SOUND, constants.sound.configEntryCount)) {
		if (float out; loadFloat(sound, out, ConfigTypes::VOLUME_MASTER))    { constants.sound.masterVolume = out; }
		if (bool  out;  loadBool(sound, out, ConfigTypes::VOLUME_MUTE_BOOL)) { constants.sound.muteVolume   = out; }
	}
	// window
	if (nlohmann::json window; loadSection(load, window, ConfigTypes::WINDOW, constants.window.configEntryCount)) {
        if (int out; loadInt(window, out, ConfigTypes::RESOLUTION_AS_ENUM)) {
            constants.window.currentResolutionEnum = static_cast<Resolution>(out);
        }
        if (bool out; loadBool(window, out, ConfigTypes::FULL_SCREEN_BOOL)) {
            constants.window.isFullScreen = out;
        }
        if (int out; loadInt(window, out, ConfigTypes::TARGET_FPS)) {
            constants.window.FPS = static_cast<size_t>(out);
        }
    }
	// world
	if (nlohmann::json world; loadSection(load, world, ConfigTypes::WORLD, constants.world.configEntryCount)) {
        if (int out; loadInt(world, out, ConfigTypes::DIMENSION_X_CURRENT)) {
            constants.world.currentDimensionX = out;
        }
        if (int out; loadInt(world, out, ConfigTypes::DIMENSION_X_MAX)) {
            constants.world.maxDimensionX = out;
        }
        if (int out; loadInt(world, out, ConfigTypes::DIMENSION_X_MIN)) {
            constants.world.minDimensionX = out;
        }
        if (int out; loadInt(world, out, ConfigTypes::DIMENSION_X_SHOW_GALAXY)) {
            constants.world.showDimensionX = out;
        }
        if (int out; loadInt(world, out, ConfigTypes::DIMENSION_Y_CURRENT)) {
            constants.world.currentDimensionY = out;
        }
        if (int out; loadInt(world, out, ConfigTypes::DIMENSION_Y_MAX)) {
            constants.world.maxDimensionY = out;
        }
        if (int out; loadInt(world, out, ConfigTypes::DIMENSION_Y_MIN)) {
            constants.world.minDimensionY = out;
        }
        if (int out; loadInt(world, out, ConfigTypes::DIMENSION_Y_SHOW_GALAXY)) {
            constants.world.showDimensionY = out;
        }
        if (int out; loadInt(world, out, ConfigTypes::DISCOVER_RANGE_FACTOR)) {
            constants.world.discoverRangeFactor = out;
        }
        if (int out; loadInt(world, out, ConfigTypes::PLANET_COUNT_CURRENT)) {
            constants.world.currentPlanetCount = static_cast<size_t>(out);
        }
        if (int out; loadInt(world, out, ConfigTypes::PLANET_COUNT_MAX)) {
            constants.world.maxPlanetCount = static_cast<size_t>(out);
        }
        if (int out; loadInt(world, out, ConfigTypes::PLANET_COUNT_MIN)) {
            constants.world.minPlanetCount = static_cast<size_t>(out);
        }
        if (int out; loadInt(world, out, ConfigTypes::PLANET_COUNT_SHOW_GALAXY)) {
            constants.world.showPlanetCount = static_cast<size_t>(out);
        }
    }
    // @formatter:on


    // check if all values are loaded
	AppContext_ty_c appContext = AppContext::GetInstance();
	assert(loadEntryCount == appContext.constants.GetConfigValueCount());
	if (int count = appContext.constants.GetConfigValueCount();  loadEntryCount != count) {
		Print(
			PrintType::ERROR,
			"Entry count in config is not matching -> expected: {} -> provided: {} -> some values will use the default value",
			count,
			loadEntryCount
		);
	} else {
		Print(
			PrintType::INFO,
			"Entry count in config is matching -> count {}",
			loadEntryCount
		);
	}

#ifdef _DEBUG
	constants.window.isFullScreen = false;
	Print(PrintType::DEBUG, "set full screen to false");
	constants.window.currentResolutionEnum = Resolution::HD;
	Print(PrintType::DEBUG, "set resolution ro HD");
#endif // _DEBUG

	Print(PrintType::INFO, "config loaded");
}
void SaveConfig() {

    // to json
	auto const& constants{ AppContext::GetInstance().constants };
	nlohmann::json save;

    // @formatter:off
    save[CToS(ConfigTypes::GAME_EVENTS)] = {
		{ CToS(ConfigTypes::PIRATES),             constants.gameEvents.IsFlag(HGameEventType::PIRATES)        },
		{ CToS(ConfigTypes::REVOLTS),             constants.gameEvents.IsFlag(HGameEventType::REVOLTS)        },
		{ CToS(ConfigTypes::RENEGADE_SHIPS),      constants.gameEvents.IsFlag(HGameEventType::RENEGADE_SHIPS) },
		{ CToS(ConfigTypes::BLACK_HOLE),          constants.gameEvents.IsFlag(HGameEventType::BLACK_HOLE)     },
		{ CToS(ConfigTypes::SUPERNOVA),           constants.gameEvents.IsFlag(HGameEventType::SUPERNOVA)      },
		{ CToS(ConfigTypes::ENGINE_PROBLEM),      constants.gameEvents.IsFlag(HGameEventType::ENGINE_PROBLEM) },
        { CToS(ConfigTypes::GLOBAL_EVENT_CHANCE),                      constants.gameEvents.globalEventChance },
    };
	save[CToS(ConfigTypes::FIGHT)] = {
		{ CToS(ConfigTypes::HIT_CHANCE),                      constants.fight.hitChance                     },
		{ CToS(ConfigTypes::FLEET_FIGHT_RANGE),               constants.fight.fleetFightRange               },
		{ CToS(ConfigTypes::FIGHT_PLANET_FLEET),              constants.fight.isFightPlanetFleet            },
		{ CToS(ConfigTypes::FIGHT_PLANET_TARGET_POINT),       constants.fight.isFightPlanetTargetPoint      },
		{ CToS(ConfigTypes::FIGHT_TARGET_POINT_FLEET),        constants.fight.isFightTargetPointFleet       },
		{ CToS(ConfigTypes::FIGHT_TARGET_POINT_TARGET_POINT), constants.fight.isFightTargetPointTargetPoint },
	};
	save[CToS(ConfigTypes::FLEET)] = {
		{ CToS(ConfigTypes::FLEET_SPEED_CURRENT), constants.fleet.currentFleetSpeed },
		{ CToS(ConfigTypes::FLEET_SPEED_MAX),     constants.fleet.maxFleetSpeed     },
		{ CToS(ConfigTypes::FLEET_SPEED_MIN),     constants.fleet.minFleetSpeed     },
	};
	save[CToS(ConfigTypes::GLOBAL)] = {
		{ CToS(ConfigTypes::CURRENT_LANGUAGE_NAME), constants.global.currentLanguageName },
        {   CToS(ConfigTypes::GAME_ROUNDS_CURRENT),  constants.global.currentTargetRound },
        {       CToS(ConfigTypes::GAME_ROUNDS_MAX),           constants.global.maxRounds },
        {       CToS(ConfigTypes::GAME_ROUNDS_MIN),           constants.global.minRounds },
    };
	save[CToS(ConfigTypes::PLANET)] = {
		{ CToS(ConfigTypes::PRODUCTION_HOMEWORLD),                constants.planet.homeworldProduction              },
		{ CToS(ConfigTypes::PRODUCTION_MAX),                      constants.planet.maxProduction                    },
		{ CToS(ConfigTypes::PRODUCTION_MIN),                      constants.planet.minProduction                    },
		{ CToS(ConfigTypes::SHIPS_MAX_FACTOR),                    constants.planet.maxShipsFactor                   },
		{ CToS(ConfigTypes::SPACEING_GLOBAL),                     constants.planet.globalSpacing                    },
		{ CToS(ConfigTypes::SPACEING_HOMEWORLD),                  constants.planet.homeworldSpacing                 },
		{ CToS(ConfigTypes::STARTING_SHIPS_MULTIPLICATOR_GLOBAL), constants.planet.startingGlobalShipsMultiplicator },
		{ CToS(ConfigTypes::STARTING_SHIPS_MULTIPLICATOR_HUMAN),  constants.planet.startingHumanShipsMultiplicator  },
	};
	save[CToS(ConfigTypes::PLAYER)] = {
		{ CToS(ConfigTypes::PLAYER_COUNT_MAX), constants.player.maxPlayerCount },
		{ CToS(ConfigTypes::PLAYER_COUNT_MIN), constants.player.minPlayerCount },
		{ CToS(ConfigTypes::Player_SHUFFLE),   constants.player.shuffle        },
	};
	save[CToS(ConfigTypes::SOUND)] = {
		{ CToS(ConfigTypes::VOLUME_MASTER),    constants.sound.masterVolume },
		{ CToS(ConfigTypes::VOLUME_MUTE_BOOL), constants.sound.muteVolume   },
	};
	save[CToS(ConfigTypes::VERSION)] = {
        { CToS(ConfigTypes::VERSION_CONFIG), constants.global.configVersion },
        {   CToS(ConfigTypes::VERSION_GAME),   constants.global.gameVersion },
    };
	save[CToS(ConfigTypes::WINDOW)] = {
        { CToS(ConfigTypes::RESOLUTION_AS_ENUM), static_cast<size_t>(constants.window.currentResolutionEnum) },
        {   CToS(ConfigTypes::FULL_SCREEN_BOOL),                               constants.window.isFullScreen },
        {         CToS(ConfigTypes::TARGET_FPS),                                        constants.window.FPS },
    };
	save[CToS(ConfigTypes::WORLD)] = {
		{ CToS(ConfigTypes::DIMENSION_X_CURRENT),      constants.world.currentDimensionX  },
		{ CToS(ConfigTypes::DIMENSION_X_MAX),          constants.world.maxDimensionX      },
		{ CToS(ConfigTypes::DIMENSION_X_MIN),          constants.world.minDimensionX      },
		{ CToS(ConfigTypes::DIMENSION_X_SHOW_GALAXY),  constants.world.showDimensionX     },
		{ CToS(ConfigTypes::DIMENSION_Y_CURRENT),      constants.world.currentDimensionY  },
		{ CToS(ConfigTypes::DIMENSION_Y_MAX),          constants.world.maxDimensionY      },
		{ CToS(ConfigTypes::DIMENSION_Y_MIN),          constants.world.minDimensionY      },
		{ CToS(ConfigTypes::DIMENSION_Y_SHOW_GALAXY),  constants.world.showDimensionY     },
        {    CToS(ConfigTypes::DISCOVER_RANGE_FACTOR), constants.world.discoverRangeFactor },
        { CToS(ConfigTypes::PLANET_COUNT_CURRENT),     constants.world.currentPlanetCount },
		{ CToS(ConfigTypes::PLANET_COUNT_MAX),         constants.world.maxPlanetCount     },
		{ CToS(ConfigTypes::PLANET_COUNT_MIN),         constants.world.minPlanetCount     },
		{ CToS(ConfigTypes::PLANET_COUNT_SHOW_GALAXY), constants.world.showPlanetCount    },
	};
    // @formatter:on

    // saving
	std::ofstream file{ };

	if (!std::filesystem::exists(constants.files.savesDir)) {
		Print(PrintType::EXPECTED_ERROR, "saves dir does not exists");
		std::filesystem::create_directory(constants.files.savesDir);
		Print(PrintType::INFO, "saves dir generated");
	}

	if (!std::filesystem::exists(constants.files.configFile())) {
		Print(PrintType::INFO, "config generated");
	}

	file.open(constants.files.configFile());

	file << save.dump(4);
	file.close();

	Print(PrintType::INFO, "config saved");
}
