//
// Purpur Tentakel
// 04.06.2023
//

#pragma once

struct CFight final {
	static inline int const configEntryCount{ 6 }; ///< config load checks if the count is idetical to the loaded entry count
	float hitChance{ 0.3f }; ///< contains the change a single ship will hit. gets overwritten by config
	int fleetFightRange{ 4 }; ///< contains the range 2 fleets will fight. get ovberwritten by config.

	bool isFightPlanetFleet{ true }; ///< contains if a planet will attack a nearbay fleet automaticly.
	bool isFightTargetPointFleet{ true }; ///< contains if a target point will attack a nearby fleet automaticly.
	bool isFightTargetPointTargetPoint{ true }; ///< contains if a target point will attack a nearby target point automaticly. 
	bool isFightPlanetTargetPoint{ true }; ///< contains if a planet will attack a nearby target point automaticly.
};