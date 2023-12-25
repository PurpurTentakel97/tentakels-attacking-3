//
// Purpur Tentakel
// 27.10.2022
//

#pragma once

/**
 * contains all world constants
 */
struct CWorld final {
	static inline int const configEntryCount{ 13 }; ///< config load checks if the count is idetical to the loaded entry count

	size_t minPlanetCount{ 20 }; ///< defines the min count of planet the unser can set (override by config)
	size_t currentPlanetCount{ 50 }; ///< contains the current count of planets the player has set (override by config)
	size_t maxPlanetCount{ 100 }; ///< defines the max count of planet the unser can set (override by config)
	size_t showPlanetCount{ 25 }; ///< defines the count of planet that are displayed in the show galaxy (override by config)

	int minDimensionX{ 60 }; ///< defines the min width of the galaxy the unser can set (override by config)
	int currentDimensionX{ 150 }; ///< contains the current width of the galaxy the player has set (override by config)
	int maxDimensionX{ 300 }; ///< defines the max width of the galaxy the unser can set (override by config)

	int minDimensionY{ 20 }; ///< defines the min height of the galaxy the unser can set (override by config)
	int currentDimensionY{ 80 }; ///< contains the current height of the galaxy the player has set (override by config)
	int maxDimensionY{ 160 }; ///< defines the max height of the galaxy the unser can set (override by config)

	int showDimensionX{ 200 }; ///< defines the width of the show galaxy (override by config)
	int showDimensionY{ 150 }; ///< defines the height of the show galaxy (override by config)

	int discoverRangeFactor{ 3 }; ///< defines the factor of the fleet speed a SpaceObject discovers a nother (override by config)
};
