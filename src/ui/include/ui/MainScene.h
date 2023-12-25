//
// Purpur Tentakel
// 21.11.2022
//

#pragma once
#include "ui_lib/Scene.h"
#include "ui_lib/SceneType.h"
#include "event/EventListener.hpp"
#include "helper/HPlayerData.h"
#include <memory>

class GalaxyScene;
class PlanetTable;
class FleetAndTargetPointTable;

/**
 * provides the main scene.
 */
class MainScene : public Scene, public EventListener {
private:
	enum class MainSceneType { ///< provides the types for the support scenes in that scene
		GALAXY,
		PLANET_TABLE,
		FLEET_TABLE,
		CLEAR,
	};
	MainSceneType m_currentMainSceneType{ MainSceneType::GALAXY }; ///< contains witch scenetype is currently loaded

	std::shared_ptr<GalaxyScene> m_galaxy; ///< contains the current ui galaxy
	std::shared_ptr<PlanetTable> m_planetTable; ///< contains the current planet table
	std::shared_ptr<FleetAndTargetPointTable> m_fleetTable; ///< contains the current fleet table
	ClassicButton_ty m_nextBtn; ///< contains the next turn / round button
	Text_ty m_currentPlayerName; ///< contains the current player name
	Text_ty m_nextPlayerName; ///< contains the next player name
	Text_ty m_currentRound;  ///< contains the current round count
	Text_ty m_currentTargetRound;  ///< contains the current target round count
	PlayerData m_currentPlayer{ 0,"",WHITE }; ///< contains the data of the current player
	PlayerData m_nextPlayer{ 0,"",WHITE }; ///< contains the data of the next player

	InputLine_int_ty m_origin; ///< provides the origin planet ID
	InputLine_int_ty m_destination; ///< provides the destination planet ID
	InputLine_int_ty m_destinationX; ///< provides the destination planet X
	InputLine_int_ty m_destinationY; ///< provides the destination planet Y
	InputLine_int_ty m_shipCount; ///< provides the ship count

	ClassicButton_ty m_acceptBtn; ///< sends the fleet event into the logic
	ClassicButton_ty m_resetBtn; ///< clears the input lines

	/**
	 * initializes all ui elements.
	 * connects the actions.
	 */
	void Initialize();
	/**
	 * removes old ui galaxy if one exists.
	 * initializes a new ui galaxy.
	 */
	void InitializeGalaxy();
	/**
	 * removes old planet table if one exists.
	 * initializes a new planet table.
	 */
	void InitializePlanetTable();

	/**
	 * removes old fleet table if one exists.
	 * initializes a new fleet table.
	 */
	void InitializeFleetTable();

	/**
	 * stitches the support scene to clear.
	 * updates player text and initializes a new galaxy.
	 * generates an popup.
	 */
	void NextTurn();

	/**
	 * handles the next turn popup.
	 */
	void NextTurnPopup(bool skip);

	/**
	 * updates player text and color.
	 */
	void SetPlayerText();

	/**
	 * sets all scene inactive.
	 * sets the provided scene active.
	 */
	void Switch(MainSceneType sceneType);

	/**
	 * return if any input line in in focus.
	 */
	bool HasAnyInputLineFocus();

	/**
	 * sets the accept button active or inactive.
	 */
	void SetAcceptButton();
	/**
	 * enables or disables the destination x and y when the input in destination changes
	 */
	void UpdateActiveDestination();

	/**
	 * sends the ship instruction event.
	 */
	void SendFleetInstruction();
	/**
	 * resets the input lines
	 */
	void ClearInputLines();

	/**
	 * handles the galaxy drag line input
	 */
	void HandleGalaxyDragLineInput(DragLineFleetInstructionEvent const* event);
	/**
	 * tries to return a space object fom a ID
	 */
	[[nodiscard]] SpaceObject_ty GetSpaceObjectFromID(unsigned int ID) const;

public:
	/**
	 * ctor.
	 * add an event listener.
	 */
	MainScene();
	/**
	 * removes the event listener.
	 */
	~MainScene();

	/**
	 * receives all events and calls the member functions.
	 */
	void OnEvent(Event const& event) override;

	/**
	 * updates all elements in elements.
	 * calls the CheckAndUpdate from the Scene.
	 */
	void CheckAndUpdate(Vector2 const& mousePosition, AppContext_ty_c appContext) override;
};
