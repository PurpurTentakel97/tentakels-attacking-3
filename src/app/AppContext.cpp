//
// Purpur Tentakel
// 04.09.2022
//

#include "AppContext.hpp"
#include <constants/G_Config_IO.hpp>
#include <event/EventGeneral.hpp>
#include <helper/HPrint.hpp>


namespace app {
    AppContext_ty AppContext::GetInstance() {
        static AppContext appContext;
        return appContext;
    }

    void AppContext::LoadLanguages() {
        languageManager.Initialize();
    }

    void AppContext::LoadConfig() const {
        cst::G_Config_IO::LoadConfig();
        if (constants.sound.muteVolume) {
            SetMasterVolume(0.0f);
        } else {
            SetMasterVolume(constants.sound.masterVolume / 100);
        }

        eve::SetTargetFPSEvent const event{ constants.window.FPS };
        eventManager.InvokeEvent(event);
    }

    void AppContext::SaveConfig() {
        cst::G_Config_IO::SaveConfig();
    }

    void AppContext::ValidateConfig() {
        // Global
        ValidateMinMax<utl::usize>(
                constants.g_global.m_min_rounds, constants.g_global.m_max_rounds, "Min Game Rounds", "Max Game Rounds");
        ValidateMinCurrentMax<utl::usize>(constants.g_global.m_min_rounds,
                                          constants.g_global.m_current_target_round,
                                          constants.g_global.m_max_rounds);

        // Game Events
        ValidateLowerEqual<float>(
                constants.g_game_events.m_min_black_hole_range_factor, 1.0f, "Min Black Hole Range Factor");
        ValidateLowerEqual<float>(
                constants.g_game_events.m_max_black_hole_range_factor, 1.0f, "Max Black Hole Range Factor");

        ValidateMinMax<float>(constants.g_game_events.m_min_black_hole_range_factor,
                              constants.g_game_events.m_max_black_hole_range_factor,
                              "Min Black Hole Factor",
                              "Max Black Hole Factor");
        ValidateMinMax<utl::usize>(constants.g_game_events.m_min_pirate_ships,
                                   constants.g_game_events.m_max_pirate_ships,
                                   "Min Pirate Ships count",
                                   "Max Pirate Ship count");

        ValidateLowerEqual<utl::usize>(constants.g_game_events.m_global_chance.value, 10000, "Global Event Chance");
        ValidateLowerEqual<utl::usize>(
                constants.g_game_events.m_engine_problem_chance.value, 10000, "Engine Problem Event Chance");
        ValidateLowerEqual<utl::usize>(constants.g_game_events.m_pirate_chance.value, 10000, "Pirate Event Chance");
        ValidateLowerEqual<utl::usize>(
                constants.g_game_events.m_renegade_ships_chance.value, 10000, "Renegade Ships Event Chance");
        ValidateLowerEqual<utl::usize>(constants.g_game_events.m_revolts_chance.value, 10000, "Revolts Event Chance");
        ValidateLowerEqual<utl::usize>(
                constants.g_game_events.m_supernova_chance.value, 10000, "Supernova Event Chance");

        // Player
        ValidateMinMax<utl::usize>(constants.player.minPlayerCount,
                                   constants.player.maxPlayerCount,
                                   "Min Player Count",
                                   "Max Player Count");

        // World
        ValidateMinMax<utl::usize>(
                constants.world.minPlanetCount, constants.world.maxPlanetCount, "Min Planet Count", "Max Planet Count");
        ValidateMinCurrentMax<utl::usize>(
                constants.world.minPlanetCount, constants.world.currentPlanetCount, constants.world.maxPlanetCount);

        ValidateMinMax<utl::usize>(
                constants.world.minDimensionX, constants.world.maxDimensionX, "Min World Width", "Max World Width");
        ValidateMinCurrentMax<utl::usize>(
                constants.world.minDimensionX, constants.world.currentDimensionX, constants.world.maxDimensionX);

        ValidateMinMax<utl::usize>(
                constants.world.minDimensionY, constants.world.maxDimensionY, "Min World Height", "Max World Height");
        ValidateMinCurrentMax<utl::usize>(
                constants.world.minDimensionY, constants.world.currentDimensionY, constants.world.maxDimensionY);

        // Sound
        ValidateLowerEqual<float>(constants.sound.masterVolume, 100.0f, "Master Volume");
        ValidateGreaterEqual<float>(constants.sound.masterVolume, 0.0f, "Master Volume");

        // Planet
        ValidateLowerEqual<float>(constants.g_planet.m_home_world_spacing, 1.0f, "Homeworld Spacing");
        ValidateGreaterEqual<float>(constants.g_planet.m_home_world_spacing, 0.0f, "Homeworld Spacing");

        ValidateLowerEqual<float>(constants.g_planet.m_global_spacing, 1.0f, "Global Spacing");
        ValidateGreaterEqual<float>(constants.g_planet.m_global_spacing, 0.0f, "Global Spacing");

        // Fleet
        ValidateMinMax<utl::usize>(constants.g_fleet.m_min_fleet_speed,
                                   constants.g_fleet.m_max_fleet_speed,
                                   "Min Fleet Movement",
                                   "Max Fleet Movement");
        ValidateMinCurrentMax<utl::usize>(constants.g_fleet.m_min_fleet_speed,
                                          constants.g_fleet.m_current_fleet_speed,
                                          constants.g_fleet.m_max_fleet_speed);

        hlp::Print(hlp::PrintType::INFO, "Config validated");
    }

    void AppContext::OnEvent(eve::Event const& event) {

        if (auto const LastRoundEvent = dynamic_cast<eve::SetCurrentLastRoundEvent const*>(&event)) {
            constants.g_global.set_current_target_round(LastRoundEvent->GetLastRound());
            return;
        }
    }

    Vector2 AppContext::GetResolution() const {
        return constants.window.currentResolutionVec;
    }

    AppContext::AppContext() {
        eventManager.AddListener(&soundManager);
        eventManager.AddListener(&playerCollection);
        eventManager.AddListener(&languageManager);
        eventManager.AddListener(this);

        hlp::Print(hlp::PrintType::INITIALIZE, "AppContext");
    }

    AppContext::~AppContext() {
        eventManager.RemoveListener(&soundManager);
        eventManager.RemoveListener(&playerCollection);
        eventManager.RemoveListener(&languageManager);
        eventManager.RemoveListener(this);
        hlp::Print(hlp::PrintType::INFO, "AppContext deleted");
    }
    void AppContext::Unload() {
        soundManager.Unload();
        assetManager.Unload();
    }
} // namespace app
