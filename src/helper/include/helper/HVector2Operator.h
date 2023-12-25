//
// Purpur Tentakel
// 01.12.2022
//

#pragma once
#include "CustomRaylib.h"
#include <string>

/**
 * adds two Vector2 from Raylib.
 */
[[nodiscard]] Vector2 operator+ (Vector2 const& lhs, Vector2 const& rhs);
/**
 * subtracts two Vector2 from Raylib.
 */
[[nodiscard]] Vector2 operator- (Vector2 const& lhs, Vector2 const& rhs);
/**
 * divides a Vector2 from RayLib with a float.
 */
[[nodiscard]] Vector2 operator/ (Vector2 const& lhs, float rhs);
/**
* divides a Vector2 from RayLib with a int.
 */
[[nodiscard]] Vector2 operator/ (Vector2 const& lhs, int rhs);

/**
 * returns the length of an Vector2 from Raylib.
 */
[[nodiscard]] float LenVec2(Vector2 const& value);

/**
 * returns a string representation.
 */
[[nodiscard]] std::string ToString(Vector2 const& value);
