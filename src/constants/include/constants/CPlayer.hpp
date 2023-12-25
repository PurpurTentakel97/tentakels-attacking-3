//
// Purpur Tentakel
// 27.10.2022
//

#pragma once

/**
 * contains the player constants
 */
struct CPlayer final {
	static inline int const configEntryCount{ 3 }; ///< config load checks if the count is idetical to the loaded entry count

	size_t minPlayerCount{ 2 }; ///< defines the min player needed for a game (overwride by config)
	size_t maxPlayerCount{ 7 }; ///< defines the max player slots available for one game (overwride by config)
	bool shuffle{ false }; ///< contains if the player gets shuffled at the begin of each round (overwride by condig)
};