//
// PurpurTentakel
// 10.08.22
//

#pragma once
#include "ManagerGalaxy.hpp"
#include "Player.hpp"
#include <event/EventGenerel.hpp>
#include <event/EventListener.hpp>
#include <event/EventsUI.hpp>
#include <memory>
#include <random>
#include <vector>

/**
 * manage the hole game.
 * that contains players, npc's, game events, galaxy, event communication with the ui.
 */
class GameManager final : public EventListener {
private:
	std::default_random_engine m_random{ std::default_random_engine() }; ///< contains a random engine to shuffle the player each round
	std::unordered_map<PlayerType, Player_ty> m_npcs{ }; ///< contains all npcs to separate them from the player
	std::vector<Player_ty> m_players{ }; ///< contains all player -> this is the main player vector
	std::vector<Player_ty> m_currentRoundPlayers{ }; ///< contains the remaining player of the current round
	
	friend GalaxyManager; ///< need access because of "callbacks"
	GalaxyManager m_galaxyManager; ///< contains all galaxy related stuff

	UpdateResult_ty m_lastUpdateResults{ }; ///< contains the last update result

	// player
	/**
	 * validates if its valid to add an other player.
	 * returns a bool.
	 */
	[[nodiscard]] bool ValidAddPlayer() const;
	/**
	 * returns the next free player ID that is nearest to 0.
	 */
	[[nodiscard]] unsigned int GetNextPlayerID() const;
	/**
	 * returns if the current ID is already existing.
	 */
	[[nodiscard]] bool IsExistingPlayerID(unsigned int ID) const;

	/**
	 * set the next current player.
	 * returns a bool to prove if its valid.
	 */
	[[nodiscard]] bool GetCurrentPlayer(Player_ty& currentPlayer) const;
	/**
	 * set the next next player.
	 * returns a bool to prove if its valid.
	 */
	[[nodiscard]] bool GetNextPlayer(Player_ty& nextPlayer) const;

	/**
	 * adds a new player.
	 * validates the new player bevor adding.
	 * opens a popup and returns if not.
	 * creates new Player id.
	 * calls the ui via event to add it too.
	 */
	void AddPlayer(AddPlayerEvent const* event);
	/**
	 * edit a player by id.
	 * checks if id exists.
	 * opens a popup and returns if not.
	 * calls the ui via event to edits it too.
	 */
	void EditPlayer(EditPlayerEvent const* event) const;
	/**
	 * deletes a player by id.
	 * checks if id exists.
	 * opens a popup and returns if not.
	 * calls the ui via event to delete it too.
	 */
	void DeletePlayer(DeletePlayerEvent const* event);
	/**
	 * deletes all player.
	 * calls the ui via event to delete it too.
	 */
	void ResetPlayer();
	/**
	 * kills the provided player
	 */
	void KillPlayer(Player_ty player);
	/**
	 * checks if the player count is valid.
	 * sends the result via event into the ui.
	 */
	void CheckPlayerCount() const;
	/**
	 * shuffles the current player.
	 * use this an the round start to get some variation every round.
	 */
	void ShuffleCurrentRoundPlayer();
	/**
	 * checks if its currently valid to add or remove a player.
	 * generates a popup if not.
	 */
	[[nodiscard]] bool CheckValidAddRemovePlayer(std::function<void(bool valid)> forPopup) const;

	/** send the current player ID via an event
	 *  will send 0 if no player is active
	 */
	void SendCurrentPlayerID();
	/** send the next player ID via an event
	 *  will send 0 if no next player exists
	 */
	void SendNextPlayerID();

	// rounds
	/** 
	 * next round triggers the Evaluation
	 */
	void NextRound(bool valid);
	/** 
	 * next turn triggers the next player and changes the information that are send to ui 
	 * so that only the current Player is displayed
	 */
	void NextTurn(bool valid);
	/**
	 * gets called from TriggerNextTurnEvent
	 * calls an Popup if the to validate if the current turn should really be over
	 * PopUp automatically calls the provided function
	 */
	void ValidateNextTurn();

	// fleet
	/**
	 * calls validation
	 * add new fleet.
	 */
	void AddFleet(SendFleetInstructionEvent const* event);

	/**
	 * validates the data from the UI.
	 * generates Popups if needed.
	 */
	[[nodiscard]] bool ValidateAddFleetInput(SendFleetInstructionEvent const* event);

	// game
	/**
	 * initializes a new game after every this is set up
	 */
	void StartGame();
	/**
	 * stops the current game
	 */
	void StopGame();
	/**
	 * pauses the current game
	 */
	void PauseGame();
	/**
	 * resumes to the curent game.
	 * only works if a game is running. 
	 */
	void ResumeGame();
	/**
	 * quits the game if the game is saved.
	 */
	void QuitGame();

public:
	/**
	 * default ctor.
	 * sets all game events to true.
	 * prints a initialize to the console.
	 */
	GameManager();

	/**
	 * TODO:: Will update the logic if a round is over.
	 * like moving etc.
	 */
	void Update();

	/**
	 * receives the incoming events and calls the correct functions.
	 */
	void OnEvent(Event const& event) override;
};
