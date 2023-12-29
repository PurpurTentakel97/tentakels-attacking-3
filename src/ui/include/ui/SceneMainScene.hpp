//
// Purpur Tentakel
// 21.11.2022
//

#pragma once
#include "app/PlayerData.hpp"
#include <event/EventListener.hpp>
#include <memory>
#include <ui_lib/Scene.hpp>
#include <ui_lib/SceneType.hpp>

class GalaxyScene;
class PlanetTable;
class FleetAndTargetPointTable;

class MainScene : public Scene, public eve::EventListener {
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
    ClassicButton_ty m_nextBtn;
    Text_ty m_currentPlayerName;
    Text_ty m_nextPlayerName;
    Text_ty m_currentRound;
    Text_ty m_currentTargetRound;
    app::PlayerData m_currentPlayer{ 0, "", WHITE };
    app::PlayerData m_nextPlayer{ 0, "", WHITE };

    InputLine_int_ty m_origin;
    InputLine_int_ty m_destination;
    InputLine_int_ty m_destinationX;
    InputLine_int_ty m_destinationY;
    InputLine_int_ty m_shipCount;

    ClassicButton_ty m_acceptBtn;
    ClassicButton_ty m_resetBtn;

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

    [[nodiscard]] SpaceObject_ty GetSpaceObjectFromID(unsigned int ID) const;

public:
    MainScene();

    ~MainScene() override;

    void OnEvent(eve::Event const& event) override;

    void CheckAndUpdate(Vector2 const& mousePosition, app::AppContext_ty_c appContext) override;
};
