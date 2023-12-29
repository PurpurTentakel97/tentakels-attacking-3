//
// Purpur Tentakel
// 18.09.2022
//

#pragma once

#include <CustomRaylib.hpp>


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

enum class TextAlignment {
    TOP,
    MID,
    BOTTOM,
    LEFT,
    RIGHT,
};

Rectangle GetAlignedCollider(Vector2& pos, Vector2 size, Alignment alignment);

[[nodiscard]] Vector2 GetAlignedPosition(Alignment alignment, Vector2 position, Vector2 size);

[[nodiscard]] Vector2 GetAlignedPositionReversed(Alignment alignment, Vector2 position, Vector2 size);

[[nodiscard]] TextAlignment GetHorizontalTextAlignment(Alignment alignment);

[[nodiscard]] TextAlignment GetVerticalTextAlignment(Alignment alignment);
