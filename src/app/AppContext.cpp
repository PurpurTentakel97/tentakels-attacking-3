//
// Purpur Tentakel
// 04.09.2022
//

#include "AppContext.hpp"
#include <constants/CConfigIO.hpp>
#include <event/EventGenerel.hpp>
#include <event/EventsUI.hpp>
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
        cst::LoadConfig();
        if (constants.sound.muteVolume) {
            SetMasterVolume(0.0f);
        } else {
            SetMasterVolume(constants.sound.masterVolume / 100);
        }

        eve::SetTargetFPSEvent const event{ constants.window.FPS };
        eventManager.InvokeEvent(event);
    }

    void AppContext::SaveConfig() {
        cst::SaveConfig();
    }

    void AppContext::ValidateConfig() {
        // Global
        ValidateMinMax<size_t>(
                constants.global.minRounds,
                constants.global.maxRounds,
                "Min Game Rounds",
                "Max Game Rounds"
        );
        ValidateMinCurrentMax<size_t>(
                constants.global.minRounds,
                constants.global.currentTargetRound,
                constants.global.maxRounds
        );

        // Player
        ValidateMinMax<size_t>(
                constants.player.minPlayerCount,
                constants.player.maxPlayerCount,
                "Min Player Count",
                "Max Player Count"
        );

        // World
        ValidateMinMax<size_t>(
                constants.world.minPlanetCount,
                constants.world.maxPlanetCount,
                "Min Planet Count",
                "Max Planet Count"
        );
        ValidateMinCurrentMax<size_t>(
                constants.world.minPlanetCount,
                constants.world.currentPlanetCount,
                constants.world.maxPlanetCount
        );

        ValidateMinMax<int>(
                constants.world.minDimensionX,
                constants.world.maxDimensionX,
                "Min World Width",
                "Max World Width"
        );
        ValidateMinCurrentMax<int>(
                constants.world.minDimensionX,
                constants.world.currentDimensionX,
                constants.world.maxDimensionX
        );

        ValidateMinMax<int>(
                constants.world.minDimensionY,
                constants.world.maxDimensionY,
                "Min World Height",
                "Max World Height"
        );
        ValidateMinCurrentMax<int>(
                constants.world.minDimensionY,
                constants.world.currentDimensionY,
                constants.world.maxDimensionY
        );

        // Sound
        ValidateLowerEqual<float>(constants.sound.masterVolume, 100.0f, "Master Volume");
        ValidateGreaterEqual<float>(constants.sound.masterVolume, 0.0f, "Master Volume");

        // Planet
        ValidateLowerEqual<float>(constants.planet.homeworldSpacing, 1.0f, "Homeworld Spacing");
        ValidateGreaterEqual<float>(constants.planet.homeworldSpacing, 0.0f, "Homeworld Spacing");

        ValidateLowerEqual<float>(constants.planet.globalSpacing, 1.0f, "Global Spacing");
        ValidateGreaterEqual<float>(constants.planet.globalSpacing, 0.0f, "Global Spacing");

        // Fleet
        ValidateMinMax<int>(
                constants.fleet.minFleetSpeed,
                constants.fleet.maxFleetSpeed,
                "Min Fleet Movement",
                "Max Fleet Movement"
        );
        ValidateMinCurrentMax<int>(
                constants.fleet.minFleetSpeed,
                constants.fleet.currentFleetSpeed,
                constants.fleet.maxFleetSpeed
        );

        hlp::Print(hlp::PrintType::INFO, "Config validated");
    }

    void AppContext::OnEvent(eve::Event const& event) {

        if (auto const LastRoundEvent = dynamic_cast<eve::SetCurrentLastRoundEvent const*>(&event)) {
            constants.global.currentTargetRound = LastRoundEvent->GetLastRound();
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
} // namespace app
