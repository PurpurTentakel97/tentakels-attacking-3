//
// Purpur Tentakel
// 18.07.2023
//

#include "SceneSettingsGame.hpp"
#include "HSceneGameEventSettings.hpp"
#include "HSceneSliderAndInputLine.hpp"
#include <alias/AliasUtils.hpp>
#include <event/EventGeneral.hpp>
#include <ui_lib/ButtonClassic.hpp>
#include <ui_lib/CheckBox.hpp>
#include <ui_lib/Text.hpp>


namespace ui {
    void GameSettingsScene::Initialize() {

        app::AppContext_ty_c appContext{ app::AppContext::GetInstance() };

        // headline
        auto settingsText = std::make_shared<uil::Text>(
                GetElementPosition(0.5f, 0.2f),
                GetElementSize(0.3f, 0.1f),
                uil::Alignment::TOP_MID,
                uil::Alignment::TOP_MID,
                0.07f,
                appContext.languageManager.Text("helper_game_settings")
        );
        m_elements.push_back(settingsText);

        auto finishBtn = std::make_shared<uil::ClassicButton>(
                999,
                GetElementPosition(0.25f, 0.81f),
                GetElementSize(0.15f, 0.1f),
                uil::Alignment::BOTTOM_MID,
                appContext.languageManager.Text("scene_settings_end_game_btn"),
                app::SoundType::CLICKED_RELEASE_STD
        );
        finishBtn->SetEnabled(false);
        m_elements.push_back(finishBtn);

        // constants
        auto id{ 1 };
        auto y{ 0.32f };
        // auto     constexpr lx     { 0.05f   };
        auto constexpr rx{ 0.55f };
        auto constexpr rx2{ 0.75f };
        auto constexpr width{ 0.40f };
        auto constexpr heightS{ 0.025f };
        auto constexpr height{ 0.05f };
        auto constexpr offset{ height + 0.005f };
        auto constexpr offsetS{ heightS + 0.005f };
        auto constexpr rxwoS{ rx + heightS };
        auto constexpr rx2woS{ rx2 + heightS };
        auto constexpr rxwo{ rx + height };
        // auto     constexpr rx2wo  { rx2 + height     };
        // auto     constexpr lxwoS  { lx + heightS     };
        // auto     constexpr lxwo   { lx + height      };
        auto constexpr a{ uil::Alignment::MID_LEFT };

        // increase
        auto const incFIDS{ [&]() { ++id; } };
        auto const incFIDB{ [&]() { id += 100; } };
        auto const incPosS{ [&]() { y += offsetS; } };
        auto const incPosB{ [&]() { y += offset; } };

        // first
        auto eventSettings = std::make_shared<GameEventSettings>(
                id,
                GetElementPosition(0.25f, y),
                GetElementSize(width, 0.5f),
                uil::Alignment::TOP_MID
        );
        eventSettings->SetActive(true, appContext);
        m_elements.push_back(eventSettings);

        incFIDB(); // big because event settings could increase

        auto fleetSpeedText = std::make_shared<uil::Text>(
                GetElementPosition(rx, y),
                GetElementSize(width, height),
                a,
                a,
                height,
                appContext.languageManager.Text("scene_settings_fleet_speed_subheadline", ":")
        );
        m_elements.push_back(fleetSpeedText);

        incPosB();

        auto fleetSpeed = std::make_shared<SliderAndInputLine>(
                id,
                GetElementPosition(rx, y),
                GetElementSize(width, height),
                a,
                static_cast<int>(appContext.constants.fleet.minFleetSpeed),
                static_cast<int>(appContext.constants.fleet.maxFleetSpeed),
                static_cast<int>(appContext.constants.fleet.currentFleetSpeed)
        );
        fleetSpeed->SetActive(true, appContext);
        fleetSpeed->SetOnSave([](utl::usize value) {
            app::AppContext::GetInstance().constants.fleet.currentFleetSpeed = value;
        });
        m_elements.push_back(fleetSpeed);

        incFIDS(); // two because slider and input line needs two ids
        incFIDS();
        incPosB();

        // last round ->
        auto lastRoundText = std::make_shared<uil::Text>(
                GetElementPosition(rx, y),
                GetElementSize(width, height),
                a,
                a,
                height,
                appContext.languageManager.Text("scene_settings_last_round_subheadline", ":")
        );
        m_elements.push_back(lastRoundText);

        incPosB();

        auto lastRound = std::make_shared<SliderAndInputLine>(
                id,
                GetElementPosition(rx, y),
                GetElementSize(width, height),
                a,
                static_cast<int>(appContext.constants.global.minRounds),
                static_cast<int>(appContext.constants.global.maxRounds),
                static_cast<int>(appContext.constants.global.currentTargetRound)
        );
        lastRound->SetActive(true, appContext);
        lastRound->SetOnSave([](utl::usize value) {
            eve::SetCurrentLastRoundEvent const event{ value };
            app::AppContext::GetInstance().eventManager.InvokeEvent(event);
        });
        m_elements.push_back(lastRound);

        incFIDS(); // two because slider and input line needs two ids
        incFIDS();
        incPosB();
        incPosS();

        auto playerShuffleCB = std::make_shared<uil::CheckBox>(
                id,
                GetElementPosition(rx, y),
                GetElementSize(0.0f, height).y,
                uil::Alignment::MID_LEFT,
                1
        );
        playerShuffleCB->SetChecked(appContext.constants.player.shuffle);
        playerShuffleCB->SetOnCheck([](utl::usize, bool isChecked) {
            app::AppContext::GetInstance().constants.player.shuffle = isChecked;
        });
        m_elements.push_back(playerShuffleCB);

        incFIDS();

        auto shuffleCBText = std::make_shared<uil::Text>(
                GetElementPosition(rxwo, y),
                GetElementSize(width, height),
                a,
                a,
                height,
                appContext.languageManager.Text("helper_shuffle_players")
        );
        m_elements.push_back(shuffleCBText);

        incPosB();
        incPosS();

        auto fightTx = std::make_shared<uil::Text>(
                GetElementPosition(rx, y),
                GetElementSize(width, height),
                a,
                a,
                height,
                appContext.languageManager.Text("ui_game_settings_fights", ':')
        );
        m_elements.push_back(fightTx);

        incPosB();

        auto fightPlanetFleetCB = std::make_shared<uil::CheckBox>(
                id,
                GetElementPosition(rx, y),
                GetElementSize(0.0f, heightS).y,
                uil::Alignment::MID_LEFT,
                1
        );
        fightPlanetFleetCB->SetChecked(appContext.constants.fight.isFightPlanetFleet);
        fightPlanetFleetCB->SetOnCheck([](utl::usize, bool isChecked) {
            app::AppContext::GetInstance().constants.fight.isFightPlanetFleet = isChecked;
        });
        m_elements.push_back(fightPlanetFleetCB);

        incFIDS();

        auto fightPlanetFleetCBText = std::make_shared<uil::Text>(
                GetElementPosition(rxwoS, y),
                GetElementSize(width, heightS),
                a,
                a,
                heightS,
                appContext.languageManager.Text("ui_game_settings_fight_planet_fleet", ':')
        );
        m_elements.push_back(fightPlanetFleetCBText);

        auto fightPlanetTargetPointCB = std::make_shared<uil::CheckBox>(
                id,
                GetElementPosition(rx2, y),
                GetElementSize(0.0f, heightS).y,
                uil::Alignment::MID_LEFT,
                1
        );
        fightPlanetTargetPointCB->SetChecked(appContext.constants.fight.isFightPlanetTargetPoint);
        fightPlanetTargetPointCB->SetOnCheck([](utl::usize, bool isChecked) {
            app::AppContext::GetInstance().constants.fight.isFightPlanetTargetPoint = isChecked;
        });
        m_elements.push_back(fightPlanetTargetPointCB);

        incFIDS();

        auto fightPlanetTargetPointCBText = std::make_shared<uil::Text>(
                GetElementPosition(rx2woS, y),
                GetElementSize(width, heightS),
                a,
                a,
                heightS,
                appContext.languageManager.Text("ui_game_settings_planet_target_point", ':')
        );
        m_elements.push_back(fightPlanetTargetPointCBText);

        incPosS();

        auto fightTargetPointFleetCB = std::make_shared<uil::CheckBox>(
                id,
                GetElementPosition(rx, y),
                GetElementSize(0.0f, heightS).y,
                uil::Alignment::MID_LEFT,
                1
        );
        fightTargetPointFleetCB->SetChecked(appContext.constants.fight.isFightTargetPointFleet);
        fightTargetPointFleetCB->SetOnCheck([](utl::usize, bool isChecked) {
            app::AppContext::GetInstance().constants.fight.isFightTargetPointFleet = isChecked;
        });
        m_elements.push_back(fightTargetPointFleetCB);

        incFIDS();

        auto fightTargetPointFleetCBText = std::make_shared<uil::Text>(
                GetElementPosition(rxwoS, y),
                GetElementSize(width, heightS),
                a,
                a,
                heightS,
                appContext.languageManager.Text("ui_game_settings_target_point_fleet", ':')
        );
        m_elements.push_back(fightTargetPointFleetCBText);

        auto fightTargetPointTargetPointCB = std::make_shared<uil::CheckBox>(
                id,
                GetElementPosition(rx2, y),
                GetElementSize(0.0f, heightS).y,
                uil::Alignment::MID_LEFT,
                1
        );
        fightTargetPointTargetPointCB->SetChecked(appContext.constants.fight.isFightTargetPointTargetPoint);
        fightTargetPointTargetPointCB->SetOnCheck([](utl::usize, bool isChecked) {
            app::AppContext::GetInstance().constants.fight.isFightTargetPointTargetPoint = isChecked;
        });
        m_elements.push_back(fightTargetPointTargetPointCB);

        incFIDS();

        auto fightTargetPointTargetPointCBText = std::make_shared<uil::Text>(
                GetElementPosition(rx2woS, y),
                GetElementSize(width, heightS),
                a,
                a,
                heightS,
                appContext.languageManager.Text("ui_game_settings_target_point_target_point", ':')
        );
        m_elements.push_back(fightTargetPointTargetPointCBText);
    }

    GameSettingsScene::GameSettingsScene() : SettingsScene{} {

        Initialize();
    }
} // namespace ui
