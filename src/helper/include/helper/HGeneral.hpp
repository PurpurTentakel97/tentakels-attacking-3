//
// Purpur Tentakel
// 05.09.2022
//

#pragma once
#include <CustomRaylib.hpp>
#include <cstddef>

// Colors
[[nodiscard]] bool operator==(Color lhs, Color rhs);

[[nodiscard]] bool operator!=(Color lhs, Color rhs);

// Position
Vector2 GetElementPosition(Vector2 const& pos, Vector2 const& size, float x, float y);

Vector2 GetElementPositionReversed(Vector2 const& posP, Vector2 const& sizeP, Vector2 const& posC);

Vector2 GetElementSize(Vector2 const& size, float x, float y);

Vector2 GetElementSizeReversed(Vector2 const& sizeP, Vector2 const& sizeC);

// Index
size_t GetIndexFromRowAndColumn(size_t row, size_t column, size_t maxColumn);
