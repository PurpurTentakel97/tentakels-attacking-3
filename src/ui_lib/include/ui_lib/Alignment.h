//
// Purpur Tentakel
// 18.09.2022
//

#pragma once
#include "CustomRaylib.h"

/**
 * provides the over all alignment.
 */
enum class Alignment {
	TOP_LEFT,
	TOP_MID,
	TOP_RIGHT,
	MID_LEFT,
	MID_MID,
	MID_RIGHT,
	BOTTOM_LEFT,
	BOTTOM_MID,
	BOTTOM_RIGHT,
	DEFAULT,
};
/**
 * provides the text alignment.
 */
enum class TextAlignment {
	TOP,
	MID,
	BOTTOM,
	LEFT,
	RIGHT,
};

/**
 * recalculates the position witch the size and alignment.
 */
Rectangle GetAlignedCollider(Vector2& pos, Vector2 size,
	Alignment allignment);
/**
 * recalculates the provided position witch the provided collider and alignment.
 */
[[nodiscard]] Vector2 GetAlignedPosition(Alignment allignment, Vector2 position, Vector2 size);
/**
 * recalculates the provided position witch the provided collider and alignment.
 */
[[nodiscard]] Vector2 GetAlignedPositionReversed(Alignment allignment, Vector2 position, Vector2 size);

/**
 * converts the over all alignment into horizontal text alignment.
 */
[[nodiscard]] TextAlignment GetHorizontalTextAlignment(Alignment alignment);
/**
 * converts the over all alignment into vertical text alignment.
 */
[[nodiscard]] TextAlignment GetVerticalTextAlignment(Alignment alignment);
