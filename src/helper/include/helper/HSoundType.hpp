//
// Purpur Tentakel
// 24.08.2022
//

#pragma once

/**
 * provides the sound types for the sound manager.
 * the first types are casted while loading.
 * you really need to keep them in order.
 */
enum class SoundType {
	ACCEPTED,
	CLICKED_PRESS_STD,
	CLICKED_RELEASE_STD,
	CLICKED_DISABLED_STD,
	HOVER_STD,
	TEXT,
};
