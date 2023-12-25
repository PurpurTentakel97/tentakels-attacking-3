//
// Purpur Tentakel
// 12.07.2023
//

#pragma once
#include "helper/HGameEventTypes.hpp"
#include <array>

/**
 * contains the constants for the game events.
 */
struct CGameEvents {
    static inline size_t const configEntryCount{
        7
    }; ///< config load checks if the count is idetical to the loaded entry count

    HGameEventType events{ 0b11111111 }; ///< contains the bismask for the events --> get overwritten by config
	float globalEventChance{ 25.0f }; ///< contains the chance a event is happening --> get overwritten by config

	/**
	 * sets the bitflag for a specific game event type.
	 */
	void SetFlag(HGameEventType const type, bool const active);
	/**
	 * return if the flag for a specific game event type is set.
	 */
	[[nodiscard]] bool IsFlag(HGameEventType const type) const;
};
