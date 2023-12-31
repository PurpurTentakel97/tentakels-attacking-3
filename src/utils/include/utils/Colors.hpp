//
// Purpur Tentakel
// 20.10.2022
//

#pragma once

#include <CustomRaylib.hpp>
#include <array>
#include <string>


namespace utl {
    struct Colors final {
    private:
        using ColorArray = std::array<Color, 16>;
        ColorArray m_colors{
            // clang-format off
        YELLOW,
        GOLD,
        PINK,
        MAGENTA,
        ORANGE,
        RED,
        MAROON,
        NECRO,
        LIME,
        DARKGREEN,
        SKYBLUE,
        BLUE,
        DARKBLUE,
        PURPLE,
        VIOLET,
        DARKPURPLE,
            // clang-format on
        };

    public:
        [[nodiscard]] bool CheckValidColor(Color const& color) const;

        [[nodiscard]] ColorArray GetColors() const;

        [[nodiscard]] static std::string AsString(Color color);

        [[nodiscard]] static bool AreSame(Color lhs, Color rhs);

        [[nodiscard]] static bool NeedBackground(Color color);
    };
} // namespace utl

[[nodiscard]] inline bool operator==(Color lhs, Color rhs) {
    return lhs.a == rhs.a and lhs.b == rhs.b and lhs.g == rhs.g and lhs.r == rhs.r;
}

[[nodiscard]] inline bool operator!=(Color lhs, Color rhs) {
    return not(lhs == rhs);
}
