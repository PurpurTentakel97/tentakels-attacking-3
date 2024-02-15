//
// Purpur Tentakel
// 27.10.2022
//

#include "CConfigEnum.hpp"
#include "CConfigIO.hpp"
#include <app/AppContext.hpp>
#include <cassert>
#include <filesystem>
#include <helper/HPrint.hpp>
#include <nlohmann/json.hpp>


namespace cst {
    // string defaults
    static std::string const defaultValuePrefix{ "-> using default value -> overwrite config by save" };
    static utl::usize loadEntryCount{ 0 };
    // print
    auto static const printMissingSection{ [](ConfigTypes const section) {
        hlp::Print(hlp::PrintType::ERROR, "section \"{}\" in config missing {}", CToS(section), defaultValuePrefix);
    } };
    auto static const printMissingEntry{ [](ConfigTypes const entry) {
        hlp::Print(hlp::PrintType::ERROR, "entry \"{}\" in config missing {}", CToS(entry), defaultValuePrefix);
    } };
    auto static const printNotMatchingCount{
        [](ConfigTypes const section, utl::usize const expected, utl::usize const provided) {
            hlp::Print(hlp::PrintType::ERROR,
                       R"(section "{}" entry count in config is not matching -> expected: "{}" -> provided: "{}")",
                       CToS(section),
                       expected,
                       provided);
        }
    };
    auto static const printWrongDatatype{ [](ConfigTypes const entry) {
        hlp::Print(
                hlp::PrintType::ERROR, "entry \"{}\" in config has wrong datatype {}", CToS(entry), defaultValuePrefix);
    } };

    // check
    auto static const isNull{ [](nlohmann::json const& son, ConfigTypes const type) -> bool {
        assert(not son.is_null());
        if (son.is_array()) {
            printMissingSection(type);
            return true;
        }
        return false;
    } };
    auto static const isExistingSection{ [](nlohmann::json const& son, ConfigTypes const type) -> bool {
        assert(son.contains(CToS(type)));
        if (not son.contains(CToS(type))) {
            printMissingSection(type);
            return false;
        }
        return true;
    } };
    auto static const isExistingEntry{ [](nlohmann::json const& son, ConfigTypes const type) -> bool {
        assert(son.contains(CToS(type)));
        if (not son.contains(CToS(type))) {
            printMissingEntry(type);
            return false;
        }
        return true;
    } };
    auto static const isMatchingSize{
        [](nlohmann::json const& son, ConfigTypes const section, utl::usize const count) -> bool {
            assert(son.size() == count);
            if (son.size() != count) {
                printNotMatchingCount(section, count, son.size());
                return false;
            }
            return true;
        }
    };

    // load
    auto static const loadSection{
        [](nlohmann::json const& son, nlohmann::json& out, ConfigTypes const section, utl::usize const count) -> bool {
            if (not isExistingSection(son, section)) {
                return false;
            }
            son.at(CToS(section)).get_to(out);

            if (isNull(out, section)) {
                return false;
            }
            isMatchingSize(out, section, count);

            return true;
        }
    };
    auto static const loadString{ [](nlohmann::json const& son, std::string& out, ConfigTypes const entry) -> bool {
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
    /*
    auto static const loadInt{ [](nlohmann::json const& son, int& out, ConfigTypes const entry) -> bool {
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
*/
    auto static const loadUSize([](nlohmann::json const& son, utl::usize& out, ConfigTypes const entry) -> bool {
        ++loadEntryCount;
        if (not isExistingEntry(son, entry)) {
            return false;
        }
        assert(son.at(CToS(entry)).is_number_unsigned());
        if (not son.at(CToS(entry)).is_number_unsigned()) {
            printWrongDatatype(entry);
            return false;
        }

        son.at(CToS(entry)).get_to(out);
        return true;
    });
    auto static const loadFloat{ [](nlohmann::json const& son, float& out, ConfigTypes const entry) -> bool {
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
    auto static const loadBool{ [](nlohmann::json const& son, bool& out, ConfigTypes const entry) -> bool {
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
        loadEntryCount  = { 0 };
        auto& constants = app::AppContext::GetInstance().constants;
        std::ifstream file;

        if (!std::filesystem::exists(Files::configFile())) {
            hlp::Print(hlp::PrintType::EXPECTED_ERROR, "no config existing");
            SaveConfig();
            return;
        }

        file.open(Files::configFile());
        if (!file.is_open()) {
            hlp::Print(hlp::PrintType::INFO, "cant open config");
            return;
        }

        nlohmann::json load;
        file >> load;
        file.close();

        // from json
        // config
        if (isNull(load, ConfigTypes::CONFIG)) {
            hlp::Print(hlp::PrintType::ERROR, "provided config is null {}", defaultValuePrefix);
            return;
        }
        if (not isMatchingSize(load, ConfigTypes::CONFIG, Global::configSectionCount)) {
            hlp::Print(hlp::PrintType::ERROR,
                       "config section count is not matching {} -> expected: {} -> provided: {}",
                       defaultValuePrefix,
                       Global::configSectionCount,
                       load.size());
        }
        // version
        if (nlohmann::json version; loadSection(load, version, ConfigTypes::VERSION, Global::configVersionCount)) {
            if (std::string versionConfig; loadString(version, versionConfig, ConfigTypes::VERSION_CONFIG)) {
                if (versionConfig != Global::configVersion) {
                    hlp::Print(hlp::PrintType::ERROR,
                               "config version in config is not matching -> expected: {} -> provided: {} -> overwrite "
                               "config by "
                               "save",
                               Global::configVersion,
                               versionConfig);
                } else {
                    hlp::Print(hlp::PrintType::INFO, "config versions matching -> version: {}", versionConfig);
                }
            } else {
                hlp::Print(hlp::PrintType::ERROR, "unable to check if config version is matching");
            }
            if (std::string versionGame; loadString(version, versionGame, ConfigTypes::VERSION_GAME)) {
                if (versionGame != Global::gameVersion) {
                    hlp::Print(hlp::PrintType::ERROR,
                               "game version is not matching -> expected: {} -> provided: {} -> overwrite by "
                               "save",
                               Global::gameVersion,
                               versionGame);
                } else {
                    hlp::Print(hlp::PrintType::INFO, "game versions matching -> version: {}", versionGame);
                }
            } else {
                hlp::Print(hlp::PrintType::ERROR, "unable to check if config version is matching");
            }
        } else {
            hlp::Print(hlp::PrintType::ERROR, "not able to check if config and game versions match");
        }

        // fight
        if (nlohmann::json fight; loadSection(load, fight, ConfigTypes::FIGHT, Fight::configEntryCount)) {
            // clang-format off
        if (float      out; loadFloat(fight, out, ConfigTypes::HIT_CHANCE                     )) { constants.fight.hitChance                     = out; }
        if (utl::usize out; loadUSize(fight, out, ConfigTypes::FLEET_FIGHT_RANGE              )) { constants.fight.fleetFightRange               = out; }
        if (bool       out; loadBool (fight, out, ConfigTypes::FIGHT_PLANET_FLEET             )) { constants.fight.isFightPlanetFleet            = out; }
        if (bool       out; loadBool (fight, out, ConfigTypes::FIGHT_PLANET_TARGET_POINT      )) { constants.fight.isFightPlanetTargetPoint      = out; }
        if (bool       out; loadBool (fight, out, ConfigTypes::FIGHT_TARGET_POINT_FLEET       )) { constants.fight.isFightTargetPointFleet       = out; }
        if (bool       out; loadBool (fight, out, ConfigTypes::FIGHT_TARGET_POINT_TARGET_POINT)) { constants.fight.isFightTargetPointTargetPoint = out; }
            // clang-format on
        }
        // game events
        // add one because of doc entry. error would rise without this
        if (nlohmann::json events;
            loadSection(load, events, ConfigTypes::GAME_EVENTS, GameEvents::configEntryCount + 1)) {
            // clang-format off
        if (bool       out; loadBool (events, out, ConfigTypes::PIRATES                 )) { constants.gameEvents.SetFlag(utl::GameEventType::PIRATES,          out); }
        if (bool       out; loadBool (events, out, ConfigTypes::REVOLTS                 )) { constants.gameEvents.SetFlag(utl::GameEventType::REVOLTS,          out); }
        if (bool       out; loadBool (events, out, ConfigTypes::RENEGADE_SHIPS          )) { constants.gameEvents.SetFlag(utl::GameEventType::RENEGADE_SHIPS,   out); }
        if (bool       out; loadBool (events, out, ConfigTypes::BLACK_HOLE              )) { constants.gameEvents.SetFlag(utl::GameEventType::BLACK_HOLE,       out); }
        if (bool       out; loadBool (events, out, ConfigTypes::SUPERNOVA               )) { constants.gameEvents.SetFlag(utl::GameEventType::SUPERNOVA,        out); }
        if (bool       out; loadBool (events, out, ConfigTypes::ENGINE_PROBLEM          )) { constants.gameEvents.SetFlag(utl::GameEventType::ENGINE_PROBLEM,   out); }
        if (utl::usize out; loadUSize(events, out, ConfigTypes::GLOBAL_EVENT_CHANCE     )) { constants.gameEvents.globalChance.value                          = out ; }
        if (utl::usize out; loadUSize(events, out, ConfigTypes::PIRATES_CHANCE          )) { constants.gameEvents.pirateChance.value                          = out ; }
        if (utl::usize out; loadUSize(events, out, ConfigTypes::REVOLTS_CHANCE          )) { constants.gameEvents.revoltChance.value                          = out ; }
        if (utl::usize out; loadUSize(events, out, ConfigTypes::RENEGADE_SHIPS_CHANCE   )) { constants.gameEvents.renegadeShipsChance.value                   = out ; }
        if (utl::usize out; loadUSize(events, out, ConfigTypes::BLACK_HOLE_CHANCE       )) { constants.gameEvents.blackHoleChance.value                       = out ; }
        if (utl::usize out; loadUSize(events, out, ConfigTypes::SUPERNOVA_CHANCE        )) { constants.gameEvents.supernovaChance.value                       = out ; }
        if (utl::usize out; loadUSize(events, out, ConfigTypes::ENGINE_PROBLEM_CHANCE   )) { constants.gameEvents.engineProblemChance.value                   = out ; }
        if (utl::usize out; loadUSize(events, out, ConfigTypes::MAX_YEARS_ENGINE_PROBLEM)) { constants.gameEvents.maxYearsEngineProblem                       = out ; }
        if (bool       out; loadBool (events, out, ConfigTypes::IS_MIN_EVENT_YEAR       )) { constants.gameEvents.isMinEventYear                              = out ; }
        if (utl::usize out; loadUSize(events, out, ConfigTypes::MIN_EVENT_YEAR          )) { constants.gameEvents.minEventYear                                = out ; }
            // clang-format on
        }
        // fleet
        if (nlohmann::json fleet; loadSection(load, fleet, ConfigTypes::FLEET, Fleet::configEntryCount)) {
            // clang-format off
        if (utl::usize out; loadUSize(fleet, out, ConfigTypes::FLEET_SPEED_CURRENT)) { constants.fleet.currentFleetSpeed = out; }
        if (utl::usize out; loadUSize(fleet, out, ConfigTypes::FLEET_SPEED_MAX    )) { constants.fleet.maxFleetSpeed     = out; }
        if (utl::usize out; loadUSize(fleet, out, ConfigTypes::FLEET_SPEED_MIN    )) { constants.fleet.minFleetSpeed     = out; }
            // clang-format on
        }
        // global
        if (nlohmann::json global; loadSection(load, global, ConfigTypes::GLOBAL, Global::configEntryCount)) {
            // clang-format off
        if (std::string out; loadString(global, out, ConfigTypes::CURRENT_LANGUAGE_NAME)) {constants.global.currentLanguageName =                         out ; }
        if (utl::usize  out; loadUSize (global, out, ConfigTypes::GAME_ROUNDS_CURRENT))   { constants.global.currentTargetRound = static_cast<utl::usize>(out); }
        if (utl::usize  out; loadUSize (global, out, ConfigTypes::GAME_ROUNDS_MAX))       { constants.global.maxRounds          = static_cast<utl::usize>(out); }
        if (utl::usize  out; loadUSize (global, out, ConfigTypes::GAME_ROUNDS_MIN))       { constants.global.minRounds          = static_cast<utl::usize>(out); }
            // clang-format on
        }
        // planet
        if (nlohmann::json planet; loadSection(load, planet, ConfigTypes::PLANET, Planet::configEntryCount)) {
            // clang-format off
        if (utl::usize out; loadUSize(planet, out, ConfigTypes::PRODUCTION_HOME_WORLD           )) { constants.planet.homeworldProduction              = static_cast<utl::usize>(out); }
        if (utl::usize out; loadUSize(planet, out, ConfigTypes::PRODUCTION_MAX                  )) { constants.planet.maxProduction                    = static_cast<utl::usize>(out); }
        if (utl::usize out; loadUSize(planet, out, ConfigTypes::PRODUCTION_MIN                  )) { constants.planet.minProduction                    = static_cast<utl::usize>(out); }
        if (utl::usize out; loadUSize(planet, out, ConfigTypes::SHIPS_MAX_FACTOR                )) { constants.planet.maxShipsFactor                   = static_cast<utl::usize>(out); }
        if (float      out; loadFloat(planet, out, ConfigTypes::SPACING_GLOBAL                  )) { constants.planet.globalSpacing                    =                         out ; }
        if (float      out; loadFloat(planet, out, ConfigTypes::SPACING_HOME_WORLD              )) { constants.planet.homeworldSpacing                 =                         out ; }
        if (utl::usize out; loadUSize(planet, out, ConfigTypes::STARTING_SHIPS_MULTIPLIER_GLOBAL)) { constants.planet.startingGlobalShipsMultiplicator = static_cast<utl::usize>(out); }
        if (utl::usize out; loadUSize(planet, out, ConfigTypes::STARTING_SHIPS_MULTIPLIER_HUMAN )) { constants.planet.startingHumanShipsMultiplicator  = static_cast<utl::usize>(out); }
            // clang-format on
        }
        // player
        if (nlohmann::json player; loadSection(load, player, ConfigTypes::PLAYER, Player::configEntryCount)) {
            // clang-format off
        if (utl::usize out; loadUSize(player, out, ConfigTypes::PLAYER_COUNT_MAX)) { constants.player.maxPlayerCount = static_cast<utl::usize>(out); }
        if (utl::usize out; loadUSize(player, out, ConfigTypes::PLAYER_COUNT_MIN)) { constants.player.minPlayerCount = static_cast<utl::usize>(out); }
        if (bool       out;  loadBool(player, out, ConfigTypes::Player_SHUFFLE  )) { constants.player.shuffle        =                         out ; }
            // clang-format on
        }
        // sound
        if (nlohmann::json sound; loadSection(load, sound, ConfigTypes::SOUND, Sound::configEntryCount)) {
            // clang-format off
        if (float out; loadFloat(sound, out, ConfigTypes::VOLUME_MASTER   )) { constants.sound.masterVolume = out; }
        if (bool  out;  loadBool(sound, out, ConfigTypes::VOLUME_MUTE_BOOL)) { constants.sound.muteVolume   = out; }
            // clang-format on
        }
        // window
        if (nlohmann::json window; loadSection(load, window, ConfigTypes::WINDOW, Window::configEntryCount)) {
            // clang-format off
        if (utl::usize out; loadUSize(window, out, ConfigTypes::RESOLUTION_AS_ENUM)) { constants.window.currentResolutionEnum = static_cast<Resolution>(out); }
        if (bool       out;  loadBool(window, out, ConfigTypes::FULL_SCREEN_BOOL  )) { constants.window.isFullScreen          =                         out ; }
        if (utl::usize out; loadUSize(window, out, ConfigTypes::TARGET_FPS        )) { constants.window.FPS                   = static_cast<utl::usize>(out); }
            // clang-format on
        }
        // world
        if (nlohmann::json world; loadSection(load, world, ConfigTypes::WORLD, World::configEntryCount)) {
            // clang-format off
        if (utl::usize out; loadUSize(world, out, ConfigTypes::DIMENSION_X_CURRENT     )) { constants.world.currentDimensionX   =                         out ; }
        if (utl::usize out; loadUSize(world, out, ConfigTypes::DIMENSION_X_MAX         )) { constants.world.maxDimensionX       =                         out ; }
        if (utl::usize out; loadUSize(world, out, ConfigTypes::DIMENSION_X_MIN         )) { constants.world.minDimensionX       =                         out ; }
        if (utl::usize out; loadUSize(world, out, ConfigTypes::DIMENSION_X_SHOW_GALAXY )) { constants.world.showDimensionX      =                         out ; }
        if (utl::usize out; loadUSize(world, out, ConfigTypes::DIMENSION_Y_CURRENT     )) { constants.world.currentDimensionY   =                         out ; }
        if (utl::usize out; loadUSize(world, out, ConfigTypes::DIMENSION_Y_MAX         )) { constants.world.maxDimensionY       =                         out ; }
        if (utl::usize out; loadUSize(world, out, ConfigTypes::DIMENSION_Y_MIN         )) { constants.world.minDimensionY       =                         out ; }
        if (utl::usize out; loadUSize(world, out, ConfigTypes::DIMENSION_Y_SHOW_GALAXY )) { constants.world.showDimensionY      =                         out ; }
        if (utl::usize out; loadUSize(world, out, ConfigTypes::DISCOVER_RANGE_FACTOR   )) { constants.world.discoverRangeFactor =                         out ; }
        if (utl::usize out; loadUSize(world, out, ConfigTypes::PLANET_COUNT_CURRENT    )) { constants.world.currentPlanetCount  = static_cast<utl::usize>(out); }
        if (utl::usize out; loadUSize(world, out, ConfigTypes::PLANET_COUNT_MAX        )) { constants.world.maxPlanetCount      = static_cast<utl::usize>(out); }
        if (utl::usize out; loadUSize(world, out, ConfigTypes::PLANET_COUNT_MIN        )) { constants.world.minPlanetCount      = static_cast<utl::usize>(out); }
        if (utl::usize out; loadUSize(world, out, ConfigTypes::PLANET_COUNT_SHOW_GALAXY)) { constants.world.showPlanetCount     = static_cast<utl::usize>(out); }
            // clang-format on
        }


        // check if all values are loaded
        assert(loadEntryCount == Constants::GetConfigValueCount());
        if (auto count = Constants::GetConfigValueCount(); loadEntryCount != count) {
            hlp::Print(
                    hlp::PrintType::ERROR,
                    "Entry count in config is not matching -> expected: {} -> provided: {} -> some values will use the "
                    "default value",
                    count,
                    loadEntryCount);
        } else {
            hlp::Print(hlp::PrintType::INFO, "Entry count in config is matching -> count {}", loadEntryCount);
        }

#ifdef _DEBUG
        constants.window.isFullScreen = false;
        hlp::Print(hlp::PrintType::DEBUG, "set full screen to false");
        constants.window.currentResolutionEnum = Resolution::HD;
        hlp::Print(hlp::PrintType::DEBUG, "set resolution to HD");
#endif // _DEBUG

        hlp::Print(hlp::PrintType::INFO, "config loaded");
    }
    void SaveConfig() {

        // to json
        auto const& constants{ app::AppContext::GetInstance().constants };
        nlohmann::json save;
        save[CToS(ConfigTypes::GAME_EVENTS)] = {
  // clang-format off
                {"_doc", "chances are displayed between 0 and 10000. 0 = 0.00%; 100 = 1.00%; 10000 = 100.00%"},
                { CToS(ConfigTypes::PIRATES                 ), constants.gameEvents.IsFlag(utl::GameEventType::PIRATES)        },
                { CToS(ConfigTypes::REVOLTS                 ), constants.gameEvents.IsFlag(utl::GameEventType::REVOLTS)        },
                { CToS(ConfigTypes::RENEGADE_SHIPS          ), constants.gameEvents.IsFlag(utl::GameEventType::RENEGADE_SHIPS) },
                { CToS(ConfigTypes::BLACK_HOLE              ), constants.gameEvents.IsFlag(utl::GameEventType::BLACK_HOLE)     },
                { CToS(ConfigTypes::SUPERNOVA               ), constants.gameEvents.IsFlag(utl::GameEventType::SUPERNOVA)      },
                { CToS(ConfigTypes::ENGINE_PROBLEM          ), constants.gameEvents.IsFlag(utl::GameEventType::ENGINE_PROBLEM) },
                { CToS(ConfigTypes::GLOBAL_EVENT_CHANCE     ), constants.gameEvents.globalChance.value                         },
                { CToS(ConfigTypes::PIRATES_CHANCE          ), constants.gameEvents.pirateChance.value                         },
                { CToS(ConfigTypes::REVOLTS_CHANCE          ), constants.gameEvents.revoltChance.value                         },
                { CToS(ConfigTypes::RENEGADE_SHIPS_CHANCE   ), constants.gameEvents.renegadeShipsChance.value                  },
                { CToS(ConfigTypes::BLACK_HOLE_CHANCE       ), constants.gameEvents.blackHoleChance.value                      },
                { CToS(ConfigTypes::SUPERNOVA_CHANCE        ), constants.gameEvents.supernovaChance.value                      },
                { CToS(ConfigTypes::ENGINE_PROBLEM_CHANCE   ), constants.gameEvents.engineProblemChance.value                  },
                { CToS(ConfigTypes::MAX_YEARS_ENGINE_PROBLEM), constants.gameEvents.maxYearsEngineProblem                      },
                { CToS(ConfigTypes::IS_MIN_EVENT_YEAR       ), constants.gameEvents.isMinEventYear                             },
                { CToS(ConfigTypes::MIN_EVENT_YEAR          ), constants.gameEvents.minEventYear                               },
  // clang-format on
        };

        save[CToS(ConfigTypes::FIGHT)] = {
  // clang-format off
        { CToS(ConfigTypes::HIT_CHANCE                     ), constants.fight.hitChance                     },
        { CToS(ConfigTypes::FLEET_FIGHT_RANGE              ), constants.fight.fleetFightRange               },
        { CToS(ConfigTypes::FIGHT_PLANET_FLEET             ), constants.fight.isFightPlanetFleet            },
        { CToS(ConfigTypes::FIGHT_PLANET_TARGET_POINT      ), constants.fight.isFightPlanetTargetPoint      },
        { CToS(ConfigTypes::FIGHT_TARGET_POINT_FLEET       ), constants.fight.isFightTargetPointFleet       },
        { CToS(ConfigTypes::FIGHT_TARGET_POINT_TARGET_POINT), constants.fight.isFightTargetPointTargetPoint },
  // clang-format on
        };
        save[CToS(ConfigTypes::FLEET)] = {
  // clang-format off
        { CToS(ConfigTypes::FLEET_SPEED_CURRENT), constants.fleet.currentFleetSpeed },
        { CToS(ConfigTypes::FLEET_SPEED_MAX    ), constants.fleet.maxFleetSpeed     },
        { CToS(ConfigTypes::FLEET_SPEED_MIN    ), constants.fleet.minFleetSpeed     },
  // clang-format on
        };
        save[CToS(ConfigTypes::GLOBAL)] = {
  // clang-format off
        { CToS(ConfigTypes::CURRENT_LANGUAGE_NAME), constants.global.currentLanguageName },
        { CToS(ConfigTypes::GAME_ROUNDS_CURRENT  ), constants.global.currentTargetRound  },
        { CToS(ConfigTypes::GAME_ROUNDS_MAX      ), constants.global.maxRounds           },
        { CToS(ConfigTypes::GAME_ROUNDS_MIN      ), constants.global.minRounds           },
  // clang-format on
        };
        save[CToS(ConfigTypes::PLANET)] = {
  // clang-format off
        { CToS(ConfigTypes::PRODUCTION_HOME_WORLD           ), constants.planet.homeworldProduction              },
        { CToS(ConfigTypes::PRODUCTION_MAX                  ), constants.planet.maxProduction                    },
        { CToS(ConfigTypes::PRODUCTION_MIN                  ), constants.planet.minProduction                    },
        { CToS(ConfigTypes::SHIPS_MAX_FACTOR                ), constants.planet.maxShipsFactor                   },
        { CToS(ConfigTypes::SPACING_GLOBAL                  ), constants.planet.globalSpacing                    },
        { CToS(ConfigTypes::SPACING_HOME_WORLD              ), constants.planet.homeworldSpacing                 },
        { CToS(ConfigTypes::STARTING_SHIPS_MULTIPLIER_GLOBAL), constants.planet.startingGlobalShipsMultiplicator },
        { CToS(ConfigTypes::STARTING_SHIPS_MULTIPLIER_HUMAN ), constants.planet.startingHumanShipsMultiplicator  },
  // clang-format on
        };
        save[CToS(ConfigTypes::PLAYER)] = {
  // clang-format off
        { CToS(ConfigTypes::PLAYER_COUNT_MAX), constants.player.maxPlayerCount },
        { CToS(ConfigTypes::PLAYER_COUNT_MIN), constants.player.minPlayerCount },
        { CToS(ConfigTypes::Player_SHUFFLE  ), constants.player.shuffle        },
  // clang-format on
        };
        save[CToS(ConfigTypes::SOUND)] = {
  // clang-format off
        { CToS(ConfigTypes::VOLUME_MASTER   ), constants.sound.masterVolume },
        { CToS(ConfigTypes::VOLUME_MUTE_BOOL), constants.sound.muteVolume   },
  // clang-format on
        };
        save[CToS(ConfigTypes::VERSION)] = {
  // clang-format off
        { CToS(ConfigTypes::VERSION_CONFIG), Global::configVersion },
        { CToS(ConfigTypes::VERSION_GAME  ), Global::gameVersion   },
  // clang-format on
        };
        save[CToS(ConfigTypes::WINDOW)] = {
  // clang-format off
        { CToS(ConfigTypes::RESOLUTION_AS_ENUM), static_cast<utl::usize>(constants.window.currentResolutionEnum) },
        { CToS(ConfigTypes::FULL_SCREEN_BOOL  ),                         constants.window.isFullScreen           },
        { CToS(ConfigTypes::TARGET_FPS        ),                         constants.window.FPS                    },
  // clang-format on
        };
        save[CToS(ConfigTypes::WORLD)] = {
  // clang-format off
        { CToS(ConfigTypes::DIMENSION_X_CURRENT     ), constants.world.currentDimensionX   },
        { CToS(ConfigTypes::DIMENSION_X_MAX         ), constants.world.maxDimensionX       },
        { CToS(ConfigTypes::DIMENSION_X_MIN         ), constants.world.minDimensionX       },
        { CToS(ConfigTypes::DIMENSION_X_SHOW_GALAXY ), constants.world.showDimensionX      },
        { CToS(ConfigTypes::DIMENSION_Y_CURRENT     ), constants.world.currentDimensionY   },
        { CToS(ConfigTypes::DIMENSION_Y_MAX         ), constants.world.maxDimensionY       },
        { CToS(ConfigTypes::DIMENSION_Y_MIN         ), constants.world.minDimensionY       },
        { CToS(ConfigTypes::DIMENSION_Y_SHOW_GALAXY ), constants.world.showDimensionY      },
        { CToS(ConfigTypes::DISCOVER_RANGE_FACTOR   ), constants.world.discoverRangeFactor },
        { CToS(ConfigTypes::PLANET_COUNT_CURRENT    ), constants.world.currentPlanetCount  },
        { CToS(ConfigTypes::PLANET_COUNT_MAX        ), constants.world.maxPlanetCount      },
        { CToS(ConfigTypes::PLANET_COUNT_MIN        ), constants.world.minPlanetCount      },
        { CToS(ConfigTypes::PLANET_COUNT_SHOW_GALAXY), constants.world.showPlanetCount     },
  // clang-format on
        };

        // saving
        std::ofstream file{};

        if (!std::filesystem::exists(Files::savesDir)) {
            hlp::Print(hlp::PrintType::EXPECTED_ERROR, "saves dir does not exists");
            std::filesystem::create_directory(Files::savesDir);
            hlp::Print(hlp::PrintType::INFO, "saves dir generated");
        }

        if (!std::filesystem::exists(Files::configFile())) {
            hlp::Print(hlp::PrintType::INFO, "config generated");
        }

        file.open(Files::configFile());

        file << save.dump(4);
        file.close();

        hlp::Print(hlp::PrintType::INFO, "config saved");
    }
} // namespace cst
