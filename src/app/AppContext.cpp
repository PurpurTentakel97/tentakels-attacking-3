//
// Purpur Tentakel
// 04.09.2022
//

#include "AppContext.hpp"
#include <constants/G_Config_IO.hpp>
#include <event/EventGeneral.hpp>
#include <helper/HPrint.hpp>
#include <utils/SaveState.hpp>


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
        if (constants.g_sound.get_is_mute()) {
            SetMasterVolume(0.0f);
        } else {
            SetMasterVolume(constants.g_sound.get_master_volume() / 100);
        }

        eve::SetTargetFPSEvent const event{ constants.g_window.get_fps() };
        eventManager.InvokeEvent(event);
    }

    void AppContext::SaveConfig() {
        cst::G_Config_IO::SaveConfig();
    }

    void AppContext::LoadGame() {
        utl::SaveState saveState{};
        constants.LoadGame(saveState);
    }

    void AppContext::SaveGame() const {
        utl::SaveState saveState{};
        constants.SaveGame(saveState);
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
        ValidateMinMax<utl::usize>(
                constants.g_player.m_min_count, constants.g_player.m_max_count, "Min Player Count", "Max Player Count");

        // World
        ValidateMinMax<utl::usize>(constants.g_world.m_min_planet_count,
                                   constants.g_world.m_max_planet_count,
                                   "Min Planet Count",
                                   "Max Planet Count");
        ValidateMinCurrentMax<utl::usize>(constants.g_world.m_min_planet_count,
                                          constants.g_world.m_current_planet_count,
                                          constants.g_world.m_max_planet_count);

        ValidateMinMax<utl::usize>(constants.g_world.m_min_dimension_x,
                                   constants.g_world.m_max_dimension_x,
                                   "Min World Width",
                                   "Max World Width");
        ValidateMinCurrentMax<utl::usize>(constants.g_world.m_min_dimension_x,
                                          constants.g_world.m_current_dimension_x,
                                          constants.g_world.m_max_dimension_x);

        ValidateMinMax<utl::usize>(constants.g_world.m_min_dimension_y,
                                   constants.g_world.m_max_dimension_y,
                                   "Min World Height",
                                   "Max World Height");
        ValidateMinCurrentMax<utl::usize>(constants.g_world.m_min_dimension_y,
                                          constants.g_world.m_current_dimension_y,
                                          constants.g_world.m_max_dimension_y);

        // Sound
        ValidateLowerEqual<float>(constants.g_sound.m_master_volume, 100.0f, "Master Volume");
        ValidateGreaterEqual<float>(constants.g_sound.m_master_volume, 0.0f, "Master Volume");

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
        return constants.currentResolutionVec;
    }

    AppContext::AppContext() {
        eventManager.AddListener(&soundManager);
        eventManager.AddListener(&playerCollection);
        eventManager.AddListener(&languageManager);
        eventManager.AddListener(&gameManager);
        eventManager.AddListener(this);

        hlp::Print(hlp::PrintType::INITIALIZE, "AppContext");
    }

    AppContext::~AppContext() {
        eventManager.RemoveListener(&soundManager);
        eventManager.RemoveListener(&playerCollection);
        eventManager.RemoveListener(&languageManager);
        eventManager.RemoveListener(&gameManager);
        eventManager.RemoveListener(this);
        hlp::Print(hlp::PrintType::INFO, "AppContext deleted");
    }
    void AppContext::Unload() {
        soundManager.Unload();
        assetManager.Unload();
    }
} // namespace app
