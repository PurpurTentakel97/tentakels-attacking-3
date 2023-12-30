//
// Purpur Tentakel
// 01.12.2022
//

#pragma once

#include <CustomRaylib.hpp>
#include <string>


[[nodiscard]] Vector2 operator+(Vector2 const& lhs, Vector2 const& rhs);

[[nodiscard]] Vector2 operator-(Vector2 const& lhs, Vector2 const& rhs);

[[nodiscard]] Vector2 operator/(Vector2 const& lhs, float rhs);

[[nodiscard]] Vector2 operator/(Vector2 const& lhs, int rhs);

namespace hlp {
    [[nodiscard]] float LenVec2(Vector2 const& value);

    [[nodiscard]] std::string ToString(Vector2 const& value);
} // namespace hlp
