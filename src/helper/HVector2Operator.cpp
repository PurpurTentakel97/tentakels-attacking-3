//
// Purpur Tentakel
// 01.12.2022
//

#include "HVector2Operator.hpp"
#include <cmath>

Vector2 operator+(Vector2 const& lhs, Vector2 const& rhs) {
    return { lhs.x + rhs.x, lhs.y + rhs.y };
}
Vector2 operator-(Vector2 const& lhs, Vector2 const& rhs) {
    return { lhs.x - rhs.x, lhs.y - rhs.y };
}

Vector2 operator/(Vector2 const& lhs, float const rhs) {
    return { lhs.x / rhs, lhs.y / rhs };
}

Vector2 operator/(Vector2 const& lhs, int const rhs) {
    return { lhs.x / static_cast<float>(rhs), lhs.y / static_cast<float>(rhs) };
}

namespace hlp {
    float LenVec2(Vector2 const& value) {
        return std::sqrt(value.x * value.x + value.y * value.y);
    }

    std::string ToString(Vector2 const& value) {
        return "x: " + std::to_string(value.x) + " | y: " + std::to_string(value.y);
    }
} // namespace hlp
