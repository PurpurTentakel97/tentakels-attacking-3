//
// Purpur Tentakel
// 27.10.2022
//


#include "HelperConfigIO.hpp"

namespace cst {
    void LoadConfig() {
        // load file
        loadEntryCount = 0;
        nlohmann::json load;
        auto& constants = app::AppContext::GetInstance().constants;
        if (not LoadAndValidateConfigJson(load)) {
            return;
        }

        // fight
        if (nlohmann::json fight; LoadSection(load, fight, ConfigTypes::FIGHT, Fight::configEntryCount)) {
            // clang-format off
        if (float      out; LoadFloat(fight, out, ConfigTypes::HIT_CHANCE                     )) { constants.fight.hitChance                     = out; }
        if (utl::usize out; LoadUSize(fight, out, ConfigTypes::FLEET_FIGHT_RANGE              )) { constants.fight.fleetFightRange               = out; }
        if (bool       out; LoadBool (fight, out, ConfigTypes::FIGHT_PLANET_FLEET             )) { constants.fight.isFightPlanetFleet            = out; }
        if (bool       out; LoadBool (fight, out, ConfigTypes::FIGHT_PLANET_TARGET_POINT      )) { constants.fight.isFightPlanetTargetPoint      = out; }
        if (bool       out; LoadBool (fight, out, ConfigTypes::FIGHT_TARGET_POINT_FLEET       )) { constants.fight.isFightTargetPointFleet       = out; }
        if (bool       out; LoadBool (fight, out, ConfigTypes::FIGHT_TARGET_POINT_TARGET_POINT)) { constants.fight.isFightTargetPointTargetPoint = out; }
            // clang-format on
        }
        // game events
        // add one because of doc entry. error would rise without this
        if (nlohmann::json events;
            LoadSection(load, events, ConfigTypes::GAME_EVENTS, GameEvents::configEntryCount + 1)) {
            // clang-format off
        if (utl::usize out; LoadUSize(events, out, ConfigTypes::GLOBAL_EVENT_CHANCE           )) { constants.gameEvents.globalChance.value                             = out ; }
        if (bool       out; LoadBool (events, out, ConfigTypes::IS_MIN_EVENT_YEAR             )) { constants.gameEvents.isMinEventYear                                 = out ; }
        if (utl::usize out; LoadUSize(events, out, ConfigTypes::MIN_EVENT_YEAR                )) { constants.gameEvents.minEventYear                                   = out ; }
        if (bool       out; LoadBool (events, out, ConfigTypes::IS_EVENT_ON_HOME_WORLD        )) { constants.gameEvents.isEventOnHomeWorld                             = out ; }
        if (bool       out; LoadBool (events, out, ConfigTypes::PIRATES                       )) { constants.gameEvents.SetFlag(utl::GameEventType::PIRATES,             out); }
        if (utl::usize out; LoadUSize(events, out, ConfigTypes::PIRATES_CHANCE                )) { constants.gameEvents.pirateChance.value                             = out ; }
        if (utl::usize out; LoadUSize(events, out, ConfigTypes::MIN_PIRATE_SHIPS              )) { constants.gameEvents.minPirateShips                                 = out ; }
        if (utl::usize out; LoadUSize(events, out, ConfigTypes::MAX_PIRATE_SHIPS              )) { constants.gameEvents.maxPirateShips                                 = out ; }
        if (bool       out; LoadBool (events, out, ConfigTypes::REVOLTS                       )) { constants.gameEvents.SetFlag(utl::GameEventType::REVOLTS,             out); }
        if (utl::usize out; LoadUSize(events, out, ConfigTypes::REVOLTS_CHANCE                )) { constants.gameEvents.revoltChance.value                             = out ; }
        if (bool       out; LoadBool (events, out, ConfigTypes::RENEGADE_SHIPS                )) { constants.gameEvents.SetFlag(utl::GameEventType::RENEGADE_SHIPS,      out); }
        if (utl::usize out; LoadUSize(events, out, ConfigTypes::RENEGADE_SHIPS_CHANCE         )) { constants.gameEvents.renegadeShipsChance.value                      = out ; }
        if (bool       out; LoadBool (events, out, ConfigTypes::SUPERNOVA                     )) { constants.gameEvents.SetFlag(utl::GameEventType::SUPERNOVA,           out); }
        if (utl::usize out; LoadUSize(events, out, ConfigTypes::SUPERNOVA_CHANCE              )) { constants.gameEvents.supernovaChance.value                          = out ; }
        if (float      out; LoadFloat(events, out, ConfigTypes::MIN_BLACK_HOLE_RANGE_FACTOR   )) { constants.gameEvents.minBlackHoleRangeFactor                        = out ; }
        if (bool       out; LoadBool (events, out, ConfigTypes::IS_MAX_BLACK_HOLE_RANGE_FACTOR)) { constants.gameEvents.isMaxBlackHoleRangeFactor                      = out ; }
        if (float      out; LoadFloat(events, out, ConfigTypes::MAX_BLACK_HOLE_RANGE_FACTOR   )) { constants.gameEvents.maxBlackHoleRangeFactor                        = out ; }
        if (bool       out; LoadBool (events, out, ConfigTypes::ENGINE_PROBLEM                )) { constants.gameEvents.SetFlag(utl::GameEventType::ENGINE_PROBLEM,      out); }
        if (utl::usize out; LoadUSize(events, out, ConfigTypes::ENGINE_PROBLEM_CHANCE         )) { constants.gameEvents.engineProblemChance.value                      = out ; }
        if (utl::usize out; LoadUSize(events, out, ConfigTypes::MAX_YEARS_ENGINE_PROBLEM      )) { constants.gameEvents.maxYearsEngineProblem                          = out ; }
        if (bool       out; LoadBool (events, out, ConfigTypes::PRODUCTION_PROBLEM            )) { constants.gameEvents.SetFlag(utl::GameEventType::PRODUCTION_PROBLEM,  out); }
        if (utl::usize out; LoadUSize(events, out, ConfigTypes::PRODUCTION_PROBLEM_CHANCE     )) { constants.gameEvents.productionProblemChance.value                  = out ; }
        if (utl::usize out; LoadUSize(events, out, ConfigTypes::MAX_YEARS_PRODUCTION_PROBLEM  )) { constants.gameEvents.maxYearsProductionProblem                      = out ; }
            // clang-format on
        }
        // fleet
        if (nlohmann::json fleet; LoadSection(load, fleet, ConfigTypes::FLEET, Fleet::configEntryCount)) {
            // clang-format off
        if (utl::usize out; LoadUSize(fleet, out, ConfigTypes::FLEET_SPEED_CURRENT)) { constants.fleet.currentFleetSpeed = out; }
        if (utl::usize out; LoadUSize(fleet, out, ConfigTypes::FLEET_SPEED_MAX    )) { constants.fleet.maxFleetSpeed     = out; }
        if (utl::usize out; LoadUSize(fleet, out, ConfigTypes::FLEET_SPEED_MIN    )) { constants.fleet.minFleetSpeed     = out; }
            // clang-format on
        }
        // global
        if (nlohmann::json global; LoadSection(load, global, ConfigTypes::GLOBAL, Global::configEntryCount)) {
            // clang-format off
        if (std::string out; LoadString(global, out, ConfigTypes::CURRENT_LANGUAGE_NAME)) {constants.global.currentLanguageName =                         out ; }
        if (utl::usize  out; LoadUSize (global, out, ConfigTypes::GAME_ROUNDS_CURRENT))   { constants.global.currentTargetRound = static_cast<utl::usize>(out); }
        if (utl::usize  out; LoadUSize (global, out, ConfigTypes::GAME_ROUNDS_MAX))       { constants.global.maxRounds          = static_cast<utl::usize>(out); }
        if (utl::usize  out; LoadUSize (global, out, ConfigTypes::GAME_ROUNDS_MIN))       { constants.global.minRounds          = static_cast<utl::usize>(out); }
            // clang-format on
        }
        // planet
        if (nlohmann::json planet; LoadSection(load, planet, ConfigTypes::PLANET, Planet::configEntryCount)) {
            // clang-format off
        if (utl::usize out; LoadUSize(planet, out, ConfigTypes::PRODUCTION_HOME_WORLD           )) { constants.planet.homeworldProduction              = static_cast<utl::usize>(out); }
        if (utl::usize out; LoadUSize(planet, out, ConfigTypes::PRODUCTION_MAX                  )) { constants.planet.maxProduction                    = static_cast<utl::usize>(out); }
        if (utl::usize out; LoadUSize(planet, out, ConfigTypes::PRODUCTION_MIN                  )) { constants.planet.minProduction                    = static_cast<utl::usize>(out); }
        if (utl::usize out; LoadUSize(planet, out, ConfigTypes::SHIPS_MAX_FACTOR                )) { constants.planet.maxShipsFactor                   = static_cast<utl::usize>(out); }
        if (float      out; LoadFloat(planet, out, ConfigTypes::SPACING_GLOBAL                  )) { constants.planet.globalSpacing                    =                         out ; }
        if (float      out; LoadFloat(planet, out, ConfigTypes::SPACING_HOME_WORLD              )) { constants.planet.homeworldSpacing                 =                         out ; }
        if (utl::usize out; LoadUSize(planet, out, ConfigTypes::STARTING_SHIPS_MULTIPLIER_GLOBAL)) { constants.planet.startingGlobalShipsMultiplicator = static_cast<utl::usize>(out); }
        if (utl::usize out; LoadUSize(planet, out, ConfigTypes::STARTING_SHIPS_MULTIPLIER_HUMAN )) { constants.planet.startingHumanShipsMultiplicator  = static_cast<utl::usize>(out); }
            // clang-format on
        }
        // player
        if (nlohmann::json player; LoadSection(load, player, ConfigTypes::PLAYER, Player::configEntryCount)) {
            // clang-format off
        if (utl::usize out; LoadUSize(player, out, ConfigTypes::PLAYER_COUNT_MAX)) { constants.player.maxPlayerCount = static_cast<utl::usize>(out); }
        if (utl::usize out; LoadUSize(player, out, ConfigTypes::PLAYER_COUNT_MIN)) { constants.player.minPlayerCount = static_cast<utl::usize>(out); }
        if (bool       out;  LoadBool(player, out, ConfigTypes::Player_SHUFFLE  )) { constants.player.shuffle        =                         out ; }
            // clang-format on
        }
        // sound
        if (nlohmann::json sound; LoadSection(load, sound, ConfigTypes::SOUND, Sound::configEntryCount)) {
            // clang-format off
        if (float out; LoadFloat(sound, out, ConfigTypes::VOLUME_MASTER   )) { constants.sound.masterVolume = out; }
        if (bool  out;  LoadBool(sound, out, ConfigTypes::VOLUME_MUTE_BOOL)) { constants.sound.muteVolume   = out; }
            // clang-format on
        }
        // window
        if (nlohmann::json window; LoadSection(load, window, ConfigTypes::WINDOW, Window::configEntryCount)) {
            // clang-format off
        if (utl::usize out; LoadUSize(window, out, ConfigTypes::RESOLUTION_AS_ENUM)) { constants.window.currentResolutionEnum = static_cast<Resolution>(out); }
        if (bool       out;  LoadBool(window, out, ConfigTypes::FULL_SCREEN_BOOL  )) { constants.window.isFullScreen          =                         out ; }
        if (utl::usize out; LoadUSize(window, out, ConfigTypes::TARGET_FPS        )) { constants.window.FPS                   = static_cast<utl::usize>(out); }
            // clang-format on
        }
        // world
        if (nlohmann::json world; LoadSection(load, world, ConfigTypes::WORLD, World::configEntryCount)) {
            // clang-format off
        if (utl::usize out; LoadUSize(world, out, ConfigTypes::DIMENSION_X_CURRENT     )) { constants.world.currentDimensionX   =                         out ; }
        if (utl::usize out; LoadUSize(world, out, ConfigTypes::DIMENSION_X_MAX         )) { constants.world.maxDimensionX       =                         out ; }
        if (utl::usize out; LoadUSize(world, out, ConfigTypes::DIMENSION_X_MIN         )) { constants.world.minDimensionX       =                         out ; }
        if (utl::usize out; LoadUSize(world, out, ConfigTypes::DIMENSION_X_SHOW_GALAXY )) { constants.world.showDimensionX      =                         out ; }
        if (utl::usize out; LoadUSize(world, out, ConfigTypes::DIMENSION_Y_CURRENT     )) { constants.world.currentDimensionY   =                         out ; }
        if (utl::usize out; LoadUSize(world, out, ConfigTypes::DIMENSION_Y_MAX         )) { constants.world.maxDimensionY       =                         out ; }
        if (utl::usize out; LoadUSize(world, out, ConfigTypes::DIMENSION_Y_MIN         )) { constants.world.minDimensionY       =                         out ; }
        if (utl::usize out; LoadUSize(world, out, ConfigTypes::DIMENSION_Y_SHOW_GALAXY )) { constants.world.showDimensionY      =                         out ; }
        if (utl::usize out; LoadUSize(world, out, ConfigTypes::DISCOVER_RANGE_FACTOR   )) { constants.world.discoverRangeFactor =                         out ; }
        if (utl::usize out; LoadUSize(world, out, ConfigTypes::PLANET_COUNT_CURRENT    )) { constants.world.currentPlanetCount  = static_cast<utl::usize>(out); }
        if (utl::usize out; LoadUSize(world, out, ConfigTypes::PLANET_COUNT_MAX        )) { constants.world.maxPlanetCount      = static_cast<utl::usize>(out); }
        if (utl::usize out; LoadUSize(world, out, ConfigTypes::PLANET_COUNT_MIN        )) { constants.world.minPlanetCount      = static_cast<utl::usize>(out); }
        if (utl::usize out; LoadUSize(world, out, ConfigTypes::PLANET_COUNT_SHOW_GALAXY)) { constants.world.showPlanetCount     = static_cast<utl::usize>(out); }
            // clang-format on
        }

        CheckLoadEntryCount();

        hlp::Print(hlp::PrintType::INFO, "config loaded");
    }


    void SaveConfig() {

        // to json
        auto const& constants{ app::AppContext::GetInstance().constants };
        nlohmann::json save;
        save[CToS(ConfigTypes::GAME_EVENTS)] = {
  // clang-format off
                {"_doc", "chances are displayed between 0 and 10000. 0 = 0.00%; 100 = 1.00%; 10000 = 100.00%"},
                { CToS(ConfigTypes::GLOBAL_EVENT_CHANCE           ), constants.gameEvents.globalChance.value                            },
                { CToS(ConfigTypes::IS_MIN_EVENT_YEAR             ), constants.gameEvents.isMinEventYear                                },
                { CToS(ConfigTypes::MIN_EVENT_YEAR                ), constants.gameEvents.minEventYear                                  },
                { CToS(ConfigTypes::IS_EVENT_ON_HOME_WORLD        ), constants.gameEvents.isEventOnHomeWorld                            },
                { CToS(ConfigTypes::PIRATES                       ), constants.gameEvents.IsFlag(utl::GameEventType::PIRATES)           },
                { CToS(ConfigTypes::PIRATES_CHANCE                ), constants.gameEvents.pirateChance.value                            },
                { CToS(ConfigTypes::MIN_PIRATE_SHIPS              ), constants.gameEvents.minPirateShips                                },
                { CToS(ConfigTypes::MAX_PIRATE_SHIPS              ), constants.gameEvents.maxPirateShips                                },
                { CToS(ConfigTypes::REVOLTS                       ), constants.gameEvents.IsFlag(utl::GameEventType::REVOLTS)           },
                { CToS(ConfigTypes::REVOLTS_CHANCE                ), constants.gameEvents.revoltChance.value                            },
                { CToS(ConfigTypes::RENEGADE_SHIPS                ), constants.gameEvents.IsFlag(utl::GameEventType::RENEGADE_SHIPS)    },
                { CToS(ConfigTypes::RENEGADE_SHIPS_CHANCE         ), constants.gameEvents.renegadeShipsChance.value                     },
                { CToS(ConfigTypes::SUPERNOVA                     ), constants.gameEvents.IsFlag(utl::GameEventType::SUPERNOVA)         },
                { CToS(ConfigTypes::SUPERNOVA_CHANCE              ), constants.gameEvents.supernovaChance.value                         },
                { CToS(ConfigTypes::MIN_BLACK_HOLE_RANGE_FACTOR   ), constants.gameEvents.minBlackHoleRangeFactor                       },
                { CToS(ConfigTypes::IS_MAX_BLACK_HOLE_RANGE_FACTOR), constants.gameEvents.isMaxBlackHoleRangeFactor                     },
                { CToS(ConfigTypes::MAX_BLACK_HOLE_RANGE_FACTOR   ), constants.gameEvents.maxBlackHoleRangeFactor                       },
                { CToS(ConfigTypes::ENGINE_PROBLEM                ), constants.gameEvents.IsFlag(utl::GameEventType::ENGINE_PROBLEM)    },
                { CToS(ConfigTypes::ENGINE_PROBLEM_CHANCE         ), constants.gameEvents.engineProblemChance.value                     },
                { CToS(ConfigTypes::MAX_YEARS_ENGINE_PROBLEM      ), constants.gameEvents.maxYearsEngineProblem                         },
                { CToS(ConfigTypes::PRODUCTION_PROBLEM            ), constants.gameEvents.IsFlag(utl::GameEventType::PRODUCTION_PROBLEM)},
                { CToS(ConfigTypes::PRODUCTION_PROBLEM_CHANCE     ), constants.gameEvents.productionProblemChance.value                 },
                { CToS(ConfigTypes::MAX_YEARS_PRODUCTION_PROBLEM  ), constants.gameEvents.maxYearsProductionProblem                     },
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
        hlp::SaveFile(Files::s_savesDir, Files::s_configFile, save.dump(4));
        hlp::Print(hlp::PrintType::INFO, "config saved");
    }
} // namespace cst
