//
// Purpur Tentakel
// 20.10.2022
//

#pragma once
#include "CustomRaylib.h"
#include <string>
#include <array>

/**
 * contains all available colors of the game and validates it.
 */
struct Colors final {
private:
	using ColorArray = std::array<Color, 16>; ///< type of the color array
	ColorArray m_colors { ///< contains all colors of the game.
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
	};

public:
	/**
	 * check if the provided color is valid.
	 */
	[[nodiscard]] bool CheckValidColor(Color const& color) const;

	/**
	 * returns all colors.
	 */
	[[nodiscard]] ColorArray GetColors() const;
	/**
	 * returns a string for a color.
	 */
	[[nodiscard]] static std::string AsString(Color color);
	/**
	 * returns if the colors are the same.
	 */
	[[nodiscard]] static bool AreSame(Color lhs, Color rhs);
	/**
	 * returns if a color should have a background.
	 */
	[[nodiscard]] static bool NeedBackground(Color color);
};
