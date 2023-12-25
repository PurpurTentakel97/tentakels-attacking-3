//
// Purpur Tentakel
// 19.10.2022
//

#pragma once
#include "CustomRaylib.h"
#include <string>

/**
 * contains all non logic player data
 */
struct PlayerData final {
	unsigned int ID{ 0 }; ///< contains the id -> matches the id in the logic
	Color color{ WHITE }; ///< contains the color
	PlayerData(unsigned int id, std::string const& name, Color col, std::string const& key = "");

	void SetName(std::string const& name);
	[[nodiscard]] std::string GetName() const;

private:
	std::string m_name{ "" }; ///< contains the name
	std::string m_nameKey{ " " }; ///< contains the key for the language system

};

/**
 * returns if player lhs has a smaller id than player rhs.
 */
[[nodiscard]] inline bool SortPlayerByID_ASC(
	PlayerData const& lhs, PlayerData const& rhs) {
	return {
		lhs.ID < rhs.ID 
	};
}
/**
 * returns if player lhs has a higher id than player rhs.
 */
[[nodiscard]] inline bool SortPlayerByID_DSC(
	PlayerData const& lhs, PlayerData const& rhs) {
	return {
		lhs.ID > rhs.ID
	};
}

/**
 * checks if two players are equal by id.
 */
[[nodiscard]] inline bool operator==(
	PlayerData const& lhs, PlayerData const& rhs) {
	return {
		lhs.ID == rhs.ID 
	};
}
/**
 * checks if two player are unequal by id.
 */
[[nodiscard]] inline bool operator!=(
	PlayerData const& lhs, PlayerData const& rhs) {
	return {
		!(lhs == rhs) 
	};
}
