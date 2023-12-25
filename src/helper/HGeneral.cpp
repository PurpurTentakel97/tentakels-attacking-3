//
// Purpur Tentakel
// 05.09.2022
//

#include "HGeneral.h"

// Colors
bool operator==(Color lhs, Color rhs) {
	return {
			lhs.a == rhs.a
		and lhs.b == rhs.b
		and lhs.g == rhs.g
		and lhs.r == rhs.r
	};
}
bool operator!=(Color lhs, Color rhs) {
	return {
		not (lhs == rhs)
	};
}

// Position
Vector2 GetElementPosition(Vector2 const& pos, Vector2 const& size,
	float x, float y) {
	return {
		pos.x + x * size.x,
		pos.y + y * size.y
	};
}
Vector2 GetElementPositionReversed(Vector2 const& posP, Vector2 const& sizeP,
	Vector2 const& posC) {
	return {
		(posC.x - posP.x) / sizeP.x,
		(posC.y - posP.y) / sizeP.y
	};
}
Vector2 GetElementSize(Vector2 const& size, float x, float y) {
	return {
		x * size.x,
		y * size.y
	};
}
Vector2 GetElementSizeReversed(Vector2 const& sizeP, Vector2 const& sizeC) {
	return {
		sizeC.x / sizeP.x,
		sizeC.y / sizeP.y
	};
}

// Index
size_t GetIndexFromRowAndColumn(size_t row, size_t column,
	size_t maxColumn) {
	return row * maxColumn + column;
}
