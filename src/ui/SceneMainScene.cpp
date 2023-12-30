//
// Purpur Tentakel
// 21.11.2022
//

#include "SceneMainScene.hpp"
#include "HSceneFleetTable.hpp"
#include "HSceneGalaxyAndSlider.hpp"
#include "HScenePlanetTable.hpp"
#include "app/PlayerCollection.hpp"
#include <app/AppContext.hpp>
#include <cassert>
#include <event/EventGeneral.hpp>
#include <logic/Galaxy.hpp>
#include <logic/Player.hpp>
#include <logic/SpaceObject.hpp>
#include <ui_lib/ButtonClassic.hpp>
#include <ui_lib/ButtonExpanding.hpp>
#include <ui_lib/InputLine.hpp>
#include <ui_lib/Text.hpp>
#include <ui_lib/Title.hpp>


namespace ui {
    void MainScene::Initialize() {

        app::AppContext_ty_c appContext{ app::AppContext::GetInstance() };

        // Galaxy and tables are Focus ID 1000+

        // Title
        auto title = std::make_shared<uil::Title>(
                GetElementPosition(0.31f, 0.0f),
                GetElementSize(0.55f, 0.2f),
                uil::Alignment::TOP_MID,
                false
        );
        m_elements.push_back(title);

        // Btn
        auto settingsBtn = std::make_shared<uil::ExpandingButton>(
                203,
                GetElementPosition(0.975f, 0.02f),
                GetElementSize(0.075f, 0.05f),
                uil::Alignment::TOP_RIGHT,
                uil::ExpandingButton::DOWN,
                0.005f,
                10.0f,
                appContext.languageManager.Text("helper_settings")
        );
        m_elements.push_back(settingsBtn);

        auto gameSettingsBtn = std::make_shared<uil::ClassicButton>(
                204,
                Vector2{ 0.0f, 0.0f },
                Vector2{ 0.0f, 0.0f },
                uil::Alignment::DEFAULT,
                appContext.languageManager.Text("helper_game"),
                app::SoundType::CLICKED_RELEASE_STD
        );
        gameSettingsBtn->SetOnClick([]() {
            app::AppContext_ty_c appContext_{ app::AppContext::GetInstance() };

            eve::PauseGameEvent const gameEvent{};
            appContext_.eventManager.InvokeEvent(gameEvent);

            eve::SwitchSceneEvent const sceneEvent{ uil::SceneType::GAME_SETTINGS };
            appContext_.eventManager.InvokeEvent(sceneEvent);
        });
        settingsBtn->Add(gameSettingsBtn, true);

        auto appSettingsBtn = std::make_shared<uil::ClassicButton>(
                205,
                Vector2{ 0.0f, 0.0f },
                Vector2{ 0.0f, 0.0f },
                uil::Alignment::DEFAULT,
                appContext.languageManager.Text("helper_app"),
                app::SoundType::CLICKED_RELEASE_STD
        );
        appSettingsBtn->SetOnClick([]() {
            app::AppContext_ty_c appContext_{ app::AppContext::GetInstance() };

            eve::PauseGameEvent const gameEvent{};
            appContext_.eventManager.InvokeEvent(gameEvent);

            eve::SwitchSceneEvent const sceneEvent{ uil::SceneType::APP_SETTINGS };
            appContext_.eventManager.InvokeEvent(sceneEvent);
        });
        settingsBtn->Add(appSettingsBtn, true);

        auto mainMenuBtn = std::make_shared<uil::ClassicButton>(
                206,
                Vector2{ 0.0f, 0.0f },
                Vector2{ 0.0f, 0.0f },
                uil::Alignment::DEFAULT,
                appContext.languageManager.Text("scene_settings_main_menu_btn"),
                app::SoundType::CLICKED_RELEASE_STD
        );
        mainMenuBtn->SetOnClick([]() {
            app::AppContext_ty_c appContext_{ app::AppContext::GetInstance() };

            eve::PauseGameEvent const gameEvent{};
            appContext_.eventManager.InvokeEvent(gameEvent);

            eve::SwitchSceneEvent const sceneEvent{ uil::SceneType::MAIN_MENU };
            appContext_.eventManager.InvokeEvent(sceneEvent);
        });
        settingsBtn->Add(mainMenuBtn, true);

        auto resignBtn = std::make_shared<uil::ClassicButton>(
                207,
                Vector2{ 0.0f, 0.0f },
                Vector2{ 0.0f, 0.0f },
                uil::Alignment::DEFAULT,
                appContext.languageManager.Text("scene_main_scene_resign_btn"),
                app::SoundType::CLICKED_RELEASE_STD
        );
        resignBtn->SetOnClick([settingsBtn]() {
            settingsBtn->Collapse();
            app::AppContext::GetInstance().eventManager.InvokeEvent(eve::KillCurrentPlayerEvent());
        });
        settingsBtn->Add(resignBtn, true);
        settingsBtn->Update();

        auto galaxyBtn = std::make_shared<uil::ClassicButton>(
                200,
                GetElementPosition(0.7f, 0.02f),
                GetElementSize(0.1f, 0.05f),
                uil::Alignment::TOP_RIGHT,
                appContext.languageManager.Text("scene_main_scene_galaxy_btn"),
                app::SoundType::CLICKED_RELEASE_STD
        );
        galaxyBtn->SetOnClick([this]() { this->Switch(MainSceneType::GALAXY); });
        m_elements.push_back(galaxyBtn);

        auto planetTableBtn = std::make_shared<uil::ClassicButton>(
                201,
                GetElementPosition(0.8f, 0.02f),
                GetElementSize(0.1f, 0.05f),
                uil::Alignment::TOP_RIGHT,
                appContext.languageManager.Text("scene_main_scene_planet_table_btn"),
                app::SoundType::CLICKED_RELEASE_STD
        );
        planetTableBtn->SetOnClick([this]() { this->Switch(MainSceneType::PLANET_TABLE); });
        m_elements.push_back(planetTableBtn);

        auto fleetTableBtn = std::make_shared<uil::ClassicButton>(
                202,
                GetElementPosition(0.9f, 0.02f),
                GetElementSize(0.1f, 0.05f),
                uil::Alignment::TOP_RIGHT,
                appContext.languageManager.Text("scene_main_scene_fleet_point_table_btn"),
                app::SoundType::CLICKED_RELEASE_STD
        );
        fleetTableBtn->SetOnClick([this]() { this->Switch(MainSceneType::FLEET_TABLE); });
        m_elements.push_back(fleetTableBtn);

        m_nextBtn = std::make_shared<uil::ClassicButton>(
                100,
                GetElementPosition(0.99f, 0.95f),
                GetElementSize(0.1f, 0.05f),
                uil::Alignment::BOTTOM_RIGHT,
                appContext.languageManager.Text("scene_main_scene_next_player_btn"),
                app::SoundType::ACCEPTED
        );
        m_nextBtn->SetOnClick([]() {
            app::AppContext::GetInstance().eventManager.InvokeEvent(eve::TriggerNextTurnEvent());
        });
        m_elements.push_back(m_nextBtn);

        // text
        auto currentPlayerLabel = std::make_shared<uil::Text>(
                GetElementPosition(0.7f, 0.08f),
                GetElementSize(0.1f, 0.02f),
                uil::Alignment::TOP_RIGHT,
                uil::Alignment::TOP_RIGHT,
                0.02f,
                appContext.languageManager.Text("scene_main_scene_current_player_text", ":")
        );
        // currentPlayerLabel->RenderRectangle(true);
        m_elements.push_back(currentPlayerLabel);

        m_currentPlayerName = std::make_shared<uil::Text>(
                GetElementPosition(0.71f, 0.08f),
                GetElementSize(0.2f, 0.02f),
                uil::Alignment::TOP_LEFT,
                uil::Alignment::TOP_LEFT,
                0.02f,
                ""
        );
        // m_currentPlayerName->RenderRectangle(true);
        m_elements.push_back(m_currentPlayerName);


        auto currentRoundLabel = std::make_shared<uil::Text>(
                GetElementPosition(0.7f, 0.1f),
                GetElementSize(0.1f, 0.02f),
                uil::Alignment::TOP_RIGHT,
                uil::Alignment::TOP_RIGHT,
                0.02f,
                appContext.languageManager.Text("scene_main_scene_current_round_text", ":")
        );
        // currentRoundLabel->RenderRectangle(true);
        m_elements.push_back(currentRoundLabel);

        m_currentRound = std::make_shared<uil::Text>(
                GetElementPosition(0.71f, 0.1f),
                GetElementSize(0.2f, 0.02f),
                uil::Alignment::TOP_LEFT,
                uil::Alignment::TOP_LEFT,
                0.02f,
                std::to_string(appContext.constants.global.currentRound)
        );
        // m_currentRound->RenderRectangle(true);
        m_elements.push_back(m_currentRound);


        auto currentTargetRoundLabel = std::make_shared<uil::Text>(
                GetElementPosition(0.7f, 0.12f),
                GetElementSize(0.1f, 0.02f),
                uil::Alignment::TOP_RIGHT,
                uil::Alignment::TOP_RIGHT,
                0.02f,
                appContext.languageManager.Text("scene_main_scene_target_round_text", ":")
        );
        // currentTargetRoundLabel->RenderRectangle(true);
        m_elements.push_back(currentTargetRoundLabel);

        m_currentTargetRound = std::make_shared<uil::Text>(
                GetElementPosition(0.71f, 0.12f),
                GetElementSize(0.2f, 0.02f),
                uil::Alignment::TOP_LEFT,
                uil::Alignment::TOP_LEFT,
                0.02f,
                std::to_string(appContext.constants.global.currentTargetRound)
        );
        // m_currentTargetRound->RenderRectangle(true);
        m_elements.push_back(m_currentTargetRound);


        auto nextPlayerNameLabel = std::make_shared<uil::Text>(
                GetElementPosition(0.9f, 0.98f),
                GetElementSize(0.1f, 0.02f),
                uil::Alignment::BOTTOM_RIGHT,
                uil::Alignment::BOTTOM_RIGHT,
                0.02f,
                appContext.languageManager.Text("scene_main_scene_next_player_text", ":")
        );
        // nextPlayerNameLabel->RenderRectangle(true);
        m_elements.push_back(nextPlayerNameLabel);

        m_nextPlayerName = std::make_shared<uil::Text>(
                GetElementPosition(0.91f, 0.98f),
                GetElementSize(0.25f, 0.02f),
                uil::Alignment::BOTTOM_LEFT,
                uil::Alignment::BOTTOM_LEFT,
                0.02f,
                ""
        );
        // m_nextPlayerName->RenderRectangle(true);
        m_elements.push_back(m_nextPlayerName);

        // ship input
        auto ship_x{ 0.35f };
        auto text = std::make_shared<uil::Text>(
                GetElementPosition(0.99f, ship_x),
                GetElementSize(0.2f, 0.05f),
                uil::Alignment::BOTTOM_RIGHT,
                uil::Alignment::BOTTOM_RIGHT,
                0.03f,
                appContext.languageManager.Text("scene_main_scene_origin_text", ":")
        );
        m_elements.push_back(text);

        m_origin = std::make_shared<uil::InputLine<int>>(
                1,
                GetElementPosition(0.99f, ship_x),
                GetElementSize(0.08f, 0.04f),
                uil::Alignment::TOP_RIGHT,
                3
        );
        m_origin->SetOnEnter([this]() { this->SendFleetInstruction(); });
        m_origin->SetOnValueChanced([this]() { SetAcceptButton(); });
        m_origin->SetPlaceholderText(appContext.languageManager.Text("scene_main_scene_id_placeholder_text"));
        m_origin->SetShouldClearByFocus(true);
        m_elements.push_back(m_origin);

        ship_x += 0.08f;

        text = std::make_shared<uil::Text>(
                GetElementPosition(0.99f, ship_x),
                GetElementSize(0.2f, 0.05f),
                uil::Alignment::BOTTOM_RIGHT,
                uil::Alignment::BOTTOM_RIGHT,
                0.03f,
                appContext.languageManager.Text("scene_main_scene_destination_text", ":")
        );
        m_elements.push_back(text);

        m_destination = std::make_shared<uil::InputLine<int>>(
                2,
                GetElementPosition(0.99f, ship_x),
                GetElementSize(0.08f, 0.04f),
                uil::Alignment::TOP_RIGHT,
                3
        );
        m_destination->SetOnEnter([this]() { this->SendFleetInstruction(); });
        m_destination->SetOnValueChanced([this]() {
            this->SetAcceptButton();
            this->UpdateActiveDestination();
        });
        m_destination->SetPlaceholderText(appContext.languageManager.Text("scene_main_scene_id_placeholder_text"));
        m_destination->SetShouldClearByFocus(true);
        m_elements.push_back(m_destination);

        ship_x += 0.05f;

        m_destinationX = std::make_shared<uil::InputLine<int>>(
                3,
                GetElementPosition(0.949f, ship_x),
                GetElementSize(0.039f, 0.04f),
                uil::Alignment::TOP_RIGHT,
                3
        );
        m_destinationX->SetOnEnter([this]() { this->SendFleetInstruction(); });
        m_destinationX->SetOnValueChanced([this]() { SetAcceptButton(); });
        m_destinationX->SetPlaceholderText("X");
        m_destinationX->SetShouldClearByFocus(true);
        m_elements.push_back(m_destinationX);

        m_destinationY = std::make_shared<uil::InputLine<int>>(
                4,
                GetElementPosition(0.99f, ship_x),
                GetElementSize(0.039f, 0.04f),
                uil::Alignment::TOP_RIGHT,
                3
        );
        m_destinationY->SetOnEnter([this]() { this->SendFleetInstruction(); });
        m_destinationY->SetOnValueChanced([this]() { SetAcceptButton(); });
        m_destinationY->SetPlaceholderText("Y");
        m_destinationY->SetShouldClearByFocus(true);
        m_elements.push_back(m_destinationY);

        ship_x += 0.08f;

        text = std::make_shared<uil::Text>(
                GetElementPosition(0.99f, ship_x),
                GetElementSize(0.2f, 0.05f),
                uil::Alignment::BOTTOM_RIGHT,
                uil::Alignment::BOTTOM_RIGHT,
                0.03f,
                appContext.languageManager.Text("scene_main_scene_ship_count_text", ":")
        );
        m_elements.push_back(text);

        m_shipCount = std::make_shared<uil::InputLine<int>>(
                5,
                GetElementPosition(0.99f, ship_x),
                GetElementSize(0.08f, 0.04f),
                uil::Alignment::TOP_RIGHT,
                4
        );
        m_shipCount->SetOnEnter([this]() { this->SendFleetInstruction(); });
        m_shipCount->SetOnValueChanced([this]() { SetAcceptButton(); });
        m_shipCount->SetPlaceholderText(appContext.languageManager.Text("scene_main_scene_ship_count_placeholder_text")
        );
        m_shipCount->SetShouldClearByFocus(true);
        m_elements.push_back(m_shipCount);

        ship_x += 0.07f;

        m_acceptBtn = std::make_shared<uil::ClassicButton>(
                6,
                GetElementPosition(0.99f, ship_x),
                GetElementSize(0.04f, 0.04f),
                uil::Alignment::TOP_RIGHT,
                "+",
                app::SoundType::ACCEPTED
        );
        m_acceptBtn->SetOnClick([this]() { this->SendFleetInstruction(); });
        m_elements.push_back(m_acceptBtn);

        m_resetBtn = std::make_shared<uil::ClassicButton>(
                7,
                GetElementPosition(0.95f, ship_x),
                GetElementSize(0.04f, 0.04f),
                uil::Alignment::TOP_RIGHT,
                "X",
                app::SoundType::ACCEPTED
        );
        m_resetBtn->SetOnClick([this]() { this->ClearInputLines(); });
        m_elements.push_back(m_resetBtn);
    }

    void MainScene::InitializeGalaxy() {
        app::AppContext_ty_c appContext{ app::AppContext::GetInstance() };
        if (m_galaxy) {
            m_galaxy->SetActive(false, appContext);
            m_elements.erase(std::remove(m_elements.begin(), m_elements.end(), m_galaxy), m_elements.end());
            m_galaxy = nullptr;
        }

        m_galaxy = std::make_shared<GalaxyScene>(
                GetElementPosition(0.01f, 0.99f),
                GetElementSize(0.8f, 0.8f),
                uil::Alignment::BOTTOM_LEFT,
                false,
                true
        );
        m_galaxy->FilterByCurrentPlayer(m_currentPlayer);
        m_elements.push_back(m_galaxy);
    }
    void MainScene::InitializePlanetTable() {

        app::AppContext_ty_c appContext = app::AppContext::GetInstance();
        if (m_planetTable) {
            m_planetTable->SetActive(false, appContext);
            m_elements.erase(std::remove(m_elements.begin(), m_elements.end(), m_planetTable), m_elements.end());
            m_planetTable = nullptr;
        }

        m_planetTable = std::make_shared<PlanetTable>(
                GetElementPosition(0.01f, 0.95f),
                GetElementSize(0.85f, 0.78f),
                uil::Alignment::BOTTOM_LEFT,
                m_galaxy->GetGalaxy()
        );
        m_elements.push_back(m_planetTable);
    }

    void MainScene::InitializeFleetTable() {

        app::AppContext_ty appContext{ app::AppContext::GetInstance() };
        if (m_fleetTable) {
            m_fleetTable->SetActive(false, appContext);
            m_elements.erase(std::remove(m_elements.begin(), m_elements.end(), m_fleetTable), m_elements.end());
            m_fleetTable = nullptr;
        }

        m_fleetTable = std::make_shared<FleetAndTargetPointTable>(
                GetElementPosition(0.01f, 0.95f),
                GetElementSize(0.85f, 0.78f),
                uil::Alignment::BOTTOM_LEFT,
                m_galaxy->GetGalaxy(),
                m_currentPlayer
        );
        m_elements.push_back(m_fleetTable);
    }

    void MainScene::NextTurn() {
        Switch(MainSceneType::CLEAR);
        SetPlayerText();
        InitializeGalaxy();
        InitializePlanetTable();
        InitializeFleetTable();
        ClearInputLines();
    }

    void MainScene::NextTurnPopup(bool const skip) {
        app::AppContext_ty_c appContext{ app::AppContext::GetInstance() };
        if (skip) {
            eve::ShowMessagePopUpEvent event{
                appContext.languageManager.Text("scene_main_scene_popup_text_skip_turn_title"),
                appContext.languageManager
                        .Text("scene_main_scene_popup_text_skip_turn_subtitle", m_currentPlayer.GetName(), '\n'),
                [this]() {
                    this->Switch(MainSceneType::GALAXY);
                    app::AppContext::GetInstance().eventManager.InvokeEvent(eve::TriggerNextTurnEvent());
                }
            };
            appContext.eventManager.InvokeEvent(event);
        } else {
            eve::ShowMessagePopUpEvent event{ appContext.languageManager.Text("scene_main_scene_popup_text_turn_title"),
                                              appContext.languageManager.Text(
                                                      "scene_main_scene_popup_text_turn_text",
                                                      m_currentPlayer.GetName(),
                                                      "\n"
                                              ),
                                              [this]() { this->Switch(MainSceneType::GALAXY); } };
            appContext.eventManager.InvokeEvent(event);
        }
    }

    void MainScene::SetPlayerText() {

        m_currentPlayerName->SetText(m_currentPlayer.GetName());
        m_currentPlayerName->SetColor(m_currentPlayer.color);

        m_nextPlayerName->SetText(m_nextPlayer.GetName());
        m_nextPlayerName->SetColor(m_nextPlayer.color);
    }

    void MainScene::Switch(MainSceneType sceneType) {
        app::AppContext_ty_c appContext{ app::AppContext::GetInstance() };

        assert(m_galaxy);
        assert(m_planetTable);
        assert(m_fleetTable);

        if (m_currentMainSceneType == sceneType) {
            sceneType = MainSceneType::GALAXY;
        }

        m_galaxy->SetActive(false, appContext);
        m_planetTable->SetActive(false, appContext);
        m_fleetTable->SetActive(false, appContext);

        m_galaxy->SetActive(sceneType == MainSceneType::GALAXY, appContext);
        m_planetTable->SetActive(sceneType == MainSceneType::PLANET_TABLE, appContext);
        m_fleetTable->SetActive(sceneType == MainSceneType::FLEET_TABLE, appContext);

        m_currentMainSceneType = sceneType;
    }

    bool MainScene::HasAnyInputLineFocus() {

        if (m_origin->IsFocused()) {
            return true;
        }
        if (m_destination->IsFocused()) {
            return true;
        }
        if (m_destinationX->IsFocused()) {
            return true;
        }
        if (m_destinationY->IsFocused()) {
            return true;
        }
        if (m_shipCount->IsFocused()) {
            return true;
        }

        return false;
    }

    void MainScene::SetAcceptButton() {

        bool const valid{ m_origin->HasValue()
                          and (m_destination->HasValue() or (m_destinationX->HasValue() and m_destinationY->HasValue()))
                          and m_shipCount->HasValue() };

        m_acceptBtn->SetEnabled(valid);
    }
    void MainScene::UpdateActiveDestination() {
        bool const hasEntry{ m_destination->HasValue() };
        m_destinationX->SetEnabled(!hasEntry);
        m_destinationY->SetEnabled(!hasEntry);
    }

    void MainScene::SendFleetInstruction() {

        eve::SendFleetInstructionEvent event{ static_cast<unsigned int>(m_origin->GetValue()),
                                              static_cast<unsigned int>(m_destination->GetValue()),
                                              m_destinationX->IsEnabled() ? m_destinationX->GetValue() : -1,
                                              m_destinationY->IsEnabled() ? m_destinationY->GetValue() : -1,
                                              static_cast<size_t>(m_shipCount->GetValue()) };
        app::AppContext::GetInstance().eventManager.InvokeEvent(event);
    }

    void MainScene::ClearInputLines() {

        m_origin->Clear();
        m_destination->Clear();
        m_destinationX->Clear();
        m_destinationY->Clear();
        m_shipCount->Clear();

        eve::SelectFocusElementEvent event{ m_origin.get() };
        app::AppContext::GetInstance().eventManager.InvokeEvent(event);
    }

    void MainScene::HandleGalaxyDragLineInput(eve::DragLineFleetInstructionEvent const* const event) {
        m_origin->Clear();
        m_destination->Clear();
        m_destinationX->Clear();
        m_destinationY->Clear();

        if (event->GetOriginID() > 0) {
            m_origin->SetValue(static_cast<int>(event->GetOriginID()));
        }
        if (event->GetDestID() > 0) {
            m_destination->SetValue(static_cast<int>(event->GetDestID()));
        } else {
            auto const& co{ event->GetDestCoordinates() };
            if (co.x >= 0 and co.y >= 0) {
                m_destinationX->SetValue(co.x);
                m_destinationY->SetValue(co.y);
            }
        }

        if (auto const& spaceObject = GetSpaceObjectFromID(event->GetOriginID())) {
            if (spaceObject->GetPlayer()->GetID() == m_currentPlayer.ID) {
                m_shipCount->SetValue(static_cast<int>(spaceObject->GetShipCount()));
                m_shipCount->ClearByNextInput();
            } else {
                m_shipCount->Clear();
            }
        } else {
            m_shipCount->Clear();
        }


        eve::SelectFocusElementEvent const focusEvent{ m_shipCount.get() };
        app::AppContext::GetInstance().eventManager.InvokeEvent(focusEvent);
    }

    lgk::SpaceObject_ty MainScene::GetSpaceObjectFromID(unsigned int const ID) const {
        auto const& planetData{ m_galaxy->GetGalaxy()->GetPlanets() };
        for (auto const& planet : planetData) {
            if (planet->GetID() == ID) {
                return planet;
            }
        }
        auto const& fleetData{ m_galaxy->GetGalaxy()->GetFleets() };
        for (auto const& fleet : fleetData) {
            if (fleet->GetID() == ID) {
                return fleet;
            }
        }
        auto const& targetData{ m_galaxy->GetGalaxy()->GetTargetPoints() };
        for (auto const& target : targetData) {
            if (target->GetID() == ID) {
                return target;
            }
        }

        return nullptr;
    }

    MainScene::MainScene()
        : Scene{
              { 0.0f, 0.0f },
              { 1.0f, 1.0f },
              uil::Alignment::DEFAULT
    } {

        app::AppContext_ty appContext{ app::AppContext::GetInstance() };
        appContext.eventManager.AddListener(this);
        appContext.eventManager.InvokeEvent(eve::LoadCurrentPlayerEvent{});

        Initialize();
        InitializeGalaxy();
        InitializePlanetTable();
        InitializeFleetTable();
        NextTurn();
        SetAcceptButton();
        NextTurnPopup(false);
    }

    MainScene::~MainScene() {
        app::AppContext::GetInstance().eventManager.RemoveListener(this);
    }

    void MainScene::OnEvent(eve::Event const& event) {
        app::AppContext_ty_c appContext{ app::AppContext::GetInstance() };

        // player
        if (auto const* playerEvent = dynamic_cast<eve::UpdateCurrentPlayerIDEvent const*>(&event)) {
            m_currentPlayer = appContext.playerCollection.GetPlayerByID(playerEvent->GetID());
            return;
        }
        if (auto const* playerEvent = dynamic_cast<eve::UpdateNextPlayerIDEvent const*>(&event)) {
            m_nextPlayer = appContext.playerCollection.GetPlayerByID(playerEvent->GetID());
            return;
        }

        // turns and rounds
        if ([[maybe_unused]] auto const* playerEvent = dynamic_cast<eve::ShowNextTurnEvent const*>(&event)) {
            NextTurn();
            NextTurnPopup(false);
            return;
        }
        if ([[maybe_unused]] auto const* playerEvent = dynamic_cast<eve::ShowSkipTurnEvent const*>(&event)) {
            NextTurn();
            NextTurnPopup(true);
            return;
        }
        if ([[maybe_unused]] auto const* playerEvent = dynamic_cast<eve::ShowEvaluationEvent const*>(&event)) {
            eve::SwitchSceneEvent sendEvent{ uil::SceneType::UPDATE_EVALUATION };
            app::AppContext::GetInstance().eventManager.InvokeEvent(sendEvent);
            return;
        }

        // Fleet Instruction
        if (auto const* fleetEvent = dynamic_cast<eve::ReturnFleetInstructionEvent const*>(&event)) {
            if (fleetEvent->IsValidFleet()) {
                ClearInputLines();
                InitializeGalaxy();
                InitializePlanetTable();
                InitializeFleetTable();
                Switch(m_currentMainSceneType);
            }
            return;
        }
        if (auto const* dragLineEvent = dynamic_cast<eve::DragLineFleetInstructionEvent const*>(&event)) {
            HandleGalaxyDragLineInput(dragLineEvent);
            return;
        }
    }

    void MainScene::CheckAndUpdate(Vector2 const& mousePosition, app::AppContext_ty_c appContext) {

        if (!HasAnyInputLineFocus()) {

            bool setFocus{ false };
            auto const input{ GetKeyPressed() };
            if (input != 0) {

                if (48 <= input && input <= 57) {
                    setFocus = true;
                }
                if (320 <= input && input <= 329) {
                    setFocus = true;
                }
            }

            if (setFocus) {
                eve::SelectFocusElementEvent const event{ m_origin.get() };
                appContext.eventManager.InvokeEvent(event);
            }
        }


        Scene::CheckAndUpdate(mousePosition, appContext);
    }
} // namespace ui
