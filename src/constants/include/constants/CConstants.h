//
// Purpur Tentakel
// 27.10.2022
//

#pragma once
#include "CGlobal.hpp"
#include "CTextProcessing.hpp"
#include "CPlayer.hpp"
#include "CWorld.hpp"
#include "CFiles.hpp"
#include "CSound.hpp"
#include "CPlanet.hpp"
#include "CFleet.hpp"
#include "CWindow.h"
#include "CFight.hpp"
#include "CGameEvents.h"

/**
 * contains all constants.
 */
struct Constants final {
	// config related
	CGameEvents gameEvents; ///< contains the game events constants
	CFight fight; ///< contains the fight constants
	CFleet fleet; ///< contains the fleet constants
	CGlobal global; ///< contains the global constants
	CPlanet planet; ///< contains the planet constants
	CPlayer player; ///< contains the player constants
	CSound sound; ///< contains the sound constants
	CWindow window; ///< contains the window constants
	CWorld world; ///< contains the world constants

	// non config related
	CTextProcessing textProcessing; ///< contains the text processing constants
	CFiles files; ///< contains the file constants

	/**
	 * calculates the sum of all config values.
	 */
	[[nodiscard]] int GetConfigValueCount() const;
};
