//
// Purpur Tentakel
// 24.05.2023
//


struct CFleet final {
	static inline int const configEntryCount{ 3 }; ///< config load checks if the count is idetical to the loaded entry count

	int minFleetSpeed{ 1 }; ///< contains the minimum speed of a fleet
	int currentFleetSpeed{ 5 }; ///< contains the current speed of a fleet
	int maxFleetSpeed{ 20 }; ///< contains the maximum speed of a fleet
};