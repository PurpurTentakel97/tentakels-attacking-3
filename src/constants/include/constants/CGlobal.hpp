//
// Purpur Tentakel
// 28.10.2022
//

#pragma once
#include <string>

/**
 * contains the global constants
 */
struct CGlobal final {
	// config counts
	static inline int const configEntryCount{ 4 }; ///< config load checks if the count is idetical to the loaded entry count
	static inline int const configVersionCount{ 2 }; ///< config load checks if the count is idetical to the loaded version count
	static inline int const configSectionCount{ 10 }; ///< config load checks if the count is idetical to the loaded section count

	// versions
	static inline std::string const languageVersion{ "v0.1.5.4" }; ///< contains the language version string
	static inline std::string const configVersion{ "v0.1.5.0" }; ///< contains the config version string
	// gameVersion will be extracted with regex in the GitHub CI. Don't chance the following line. see CMakeList.txt
	static inline std::string const gameVersion{ "v0.1.5" }; ///< current gameVersion string
	static inline std::string const copyRight{ "(c) Purpur Tentakel" }; ///< copy right string

	// language string
	std::string currentLanguageName{ "english" }; ///< contains the current language name (override by config)

	// game rounds
	size_t minRounds{ 20 }; ///< defines the min of rounds the player can set (override by config)
	size_t currentTargetRound{ 50 }; ///< contains the current target round that the player has set (override by config)
	size_t maxRounds{ 100 }; ///< defines the max of rounds the player can set (override by config)
	size_t currentRound{ 0 }; ///< contains the current round of the game

	// game bools
	bool isGameRunning{ false }; ///< contains if a game is currently running.
	bool isGamePaused{ true }; ///< contains if current game is paused
	bool isGameSaved{ true }; ///< contains if the game is currently saved -> automatic saves will not be included

	// input bools
	bool acceptInputTriggered{ false }; ///< contains if the aaccept input was triggerd in this tick
};
