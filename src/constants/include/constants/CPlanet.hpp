//
// Purpur Tentakel
// 07.11.2022
//

#pragma once

/**
 * contains the planet constants
 */
struct CPlanet final {
	static inline int const configEntryCount{ 8 }; ///< config load checks if the count is idetical to the loaded entry count

	size_t maxShipsFactor{ 25 }; ///< defines the max ships Facor (multiply by production) a non human player can have on one planet. (override by config)
	size_t startingHumanShipsMultiplicator{ 30 }; ///< defines the multiplicator to calculate the starting ships of human player. (override by config)
	size_t startingGlobalShipsMultiplicator{ 5 }; ///< defines the multiplicator to calculate the starting ships of npc player. (override by config)

	size_t homeworldProduction{ 10 }; ///< defines the production of a homeworld. (override by config)
	size_t minProduction{ 3 }; ///< defines the min production of a regular world. (override by config)
	size_t maxProduction{ 7 }; ///< defines the max production of a regular world. (override by config)

	float homeworldSpacing{ 0.15f }; ///< defines the min spacing between Homeworld. (override by config)
	float globalSpacing{ 0.02f }; ///< defines the min spacing between regular worlds. (override by config)
};
