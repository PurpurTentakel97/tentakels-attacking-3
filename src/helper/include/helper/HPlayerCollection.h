//
// Purpur Tentakel
// 11.10.2022
//

#pragma once
#include "event/EventListener.hpp"
#include "HGeneral.h"
#include "HPlayerData.h"
#include <string>
#include <array>
#include <vector>

/**
 * contains and manage all the non logic player data.
 */
class PlayerCollection final : public EventListener {
private:
	std::vector<PlayerData> m_playerData; ///< contains player data
	std::vector<PlayerData> m_npcData{ ///< contains the player data for the npcs
		{ 100, "", WHITE , "helper_player_collection_npc_neutral_player"}
	};
	PlayerData m_defaultPlayer{ 0,"", WHITE, "helper_player_collection_npc_no_player"}; ///< contains default player witch is return if no other player is found.

	/**
	 * checks if name already exists
	 */
	[[nodiscard]] bool ContainsName(std::string const& name) const;
	/**
	 * checks if color already exists
	 */
	[[nodiscard]] bool ContainsColor(Color color) const;

	/**
	 * checks if color is valid.
	 * if not: valid color is deployed and an popup is generated.
	 */
	void CheckValidColor(Color& color);
	/**
	 * checks if color is still free.
	 * if no: color free is deployed and an popup is generated.
	 */
	void CheckRemainingColor(Color& color);
	/**
	 * checks if name is still free and not empty.
	 * if not: a default name in deployed and an popup is generated.
	 */
	void CheckRemainingName(std::string& name);

	/**
	 * returns the player by id mutable.
	 */
	[[nodiscard]] PlayerData& GetPlayerByIDmut(unsigned int ID);
	/**
	 * sorts the player by is ASC.
	 */
	void SortPlayers();

	/**
	 * should only be called by event.
	 * adds a new player after validation.
	 */
	void AddPlayer(unsigned int ID,
		std::string name, Color color);
	/**
	 * should only be called by event.
	 * edits a new player after validation.
	 */
	void EditPlayer(unsigned int ID, std::string name, Color color);
	/**
	 * should only be called by event.
	 * deletes a new player after validation.
	 */
	void DeletePlayer(unsigned int ID);
	/**
	 * should only be called by event.
	 * clears all player except the default player.
	 */
	void ResetPlayer();

public:
	/**
	 * return a vector with the colors that are still free.
	 */
	[[nodiscard]] Color GetPossibleColor() const;
	/**
	 * returns a vector with all players except the default player.
	 */
	[[nodiscard]] std::vector<PlayerData> GetPlayerData() const;

	/**
	 * returns a player by id.
	 * if the id is 0 the default player will be returned.
	 */
	[[nodiscard]] PlayerData GetPlayerByID(unsigned int ID) const;
	/**
	 * returns a player or npc by id.
	 * if the id is 0 the default player will be returned.
	 */
	[[nodiscard]] PlayerData GetPlayerOrNpcByID(unsigned int ID) const;
	/**
	 * returns a player by id.
	 * if no matching player was found, the default player gets returned.
	 */
	[[nodiscard]] PlayerData GetPlayerByIDOrDefaultPlayer(unsigned int ID) const;
	/**
	 * returns a player by name.
	 */
	[[nodiscard]] PlayerData GetPlayerByName(std::string const& name) const;
	/**
	 * returns a player by color.
	 */
	[[nodiscard]] PlayerData GetPlayerByColor(Color color) const;

	/**
	 * returns the color by id.
	 * if the id is not existing white will be returned.
	 */
	[[nodiscard]] Color GetColorByID(unsigned int ID) const;

	/**
	 * returns the current player count.
	 */
	[[nodiscard]] size_t GetPlayerCount() const;

	/**
	 * received all events an calls the function within this object.
	 */
	void OnEvent(Event const& event) override;
};
