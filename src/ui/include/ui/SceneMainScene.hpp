//
// Purpur Tentakel
// 21.11.2022
//

#pragma once

#include "app/PlayerData.hpp"
#include <alias/AliasUi.hpp>
#include <event/EventListener.hpp>
#include <memory>
#include <ui_lib/Scene.hpp>
#include <ui_lib/SceneType.hpp>
#include <utils/SpaceObjectRepresentation.hpp>


namespace ui {
    class MainScene : public uil::Scene, public eve::EventListener {
    private:
        enum class MainSceneType {
            GALAXY,
            PLANET_TABLE,
            FLEET_TABLE,
            CLEAR,
        };
        MainSceneType m_currentMainSceneType{ MainSceneType::GALAXY };
        std::shared_ptr<GalaxyScene> m_galaxy;
        std::shared_ptr<PlanetTable> m_planetTable;
        std::shared_ptr<FleetAndTargetPointTable> m_fleetTable;
        uil::ClassicButton_ty m_nextBtn;
        uil::Text_ty m_currentPlayerName;
        uil::Text_ty m_nextPlayerName;
        uil::Text_ty m_currentRound;
        uil::Text_ty m_currentTargetRound;
        app::PlayerData m_currentPlayer{ 0, "", WHITE };
        app::PlayerData m_nextPlayer{ 0, "", WHITE };

        uil::InputLine_ty m_origin;
        uil::InputLine_ty m_destination;
        uil::InputLine_ty m_destinationX;
        uil::InputLine_ty m_destinationY;
        uil::InputLine_ty m_shipCount;

        uil::ClassicButton_ty m_acceptBtn;
        uil::ClassicButton_ty m_resetBtn;

        void Initialize();

        void InitializeGalaxy();

        void InitializePlanetTable();

        void InitializeFleetTable();

        void NextTurn();

        void NextTurnPopup(bool skip);

        void SetPlayerText();

        void Switch(MainSceneType sceneType);

        bool HasAnyInputLineFocus();

        void SetAcceptButton();

        void UpdateActiveDestination();

        void SendFleetInstruction();

        void ClearInputLines();

        void HandleGalaxyDragLineInput(eve::DragLineFleetInstructionEvent const* event);

        [[nodiscard]] utl::SpaceObjectRepresentation GetSpaceObjectFromID(utl::usize ID) const;

    public:
        MainScene();

        ~MainScene() override;

        void OnEvent(eve::Event const& event) override;

        void CheckAndUpdate(Vector2 const& mousePosition, app::AppContext_ty_c appContext) override;
    };
} // namespace ui
