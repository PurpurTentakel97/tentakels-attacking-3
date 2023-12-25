//
// Purpur Tentakel
// 10.12.2022
//

#pragma once
#include "CustomRaylib.h"
#include "helper/HResolution.hpp"
#include "helper/Vec2.hpp"
#include <cstddef>
#include <string>
#include <vector>

struct CWindow final {
    static inline size_t const configEntryCount{
        3
    }; ///< config load checks if the count is idetical to the loaded entry count

    Resolution currentResolutionEnum{ Resolution::LAST }; ///< contains the current resolution Enum (override by config)
	Vector2 currentResolutionVec{ 800.0f, 600.0f }; ///< contains the current resolution Vector
	Vec2<int> nativeResolutionVec{ 800, 600 }; ///< contains the native resolution of the the screen

	bool isFullScreen{ true }; ///< defines if the game is starting in fullscreen mode (override by config)

	size_t FPS{ 60 }; ///< contains the target FPS (override by config)

	/**
	 * checks if the provided resolution would fit onto the screen
	 */
	[[nodiscard]] bool IsPossibleResolution(Resolution toProove) const;
	/**
	 * returns all resolutions as pair of resolution and string
	 */
	[[nodiscard]] std::vector<std::pair<Resolution, std::string>> GetAllResolutionsAsString() const;
	/** 
	 * returns a string for the provided resolution.
	 */
	[[nodiscard]] std::string GetStringFromResolution(Resolution resolution) const;
	/**
	 * returns the provided resolution as int.
	 */
	[[nodiscard]] Vec2<int> GetIntFromResolution(Resolution resolution) const;
};
