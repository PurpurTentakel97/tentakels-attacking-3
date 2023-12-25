//
// Purpur Tentakel
// 28.10.2022
//

#pragma once

/**
 * contains all sound constants
 */
struct CSound final {
	static inline int const configEntryCount{ 2 }; ///< config load checks if the count is idetical to the loaded entry count

	bool muteVolume{ false }; ///< contains if the game is muted (override by config, true == mute)
	float masterVolume{ 50.0f }; ///< contains the current master volume (override by config)
};
