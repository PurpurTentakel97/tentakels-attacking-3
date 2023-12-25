//
// Purpur Tentakel
// 25.09.2022
//

#pragma once
#include "CustomRaylib.h"
#include "HLogicAlias.hpp"
#include <string>
#include <vector>

enum class Alignment;

/**
 * replace a space thru an \n so that the text will break while displaying.
 */
void BreakText(std::string& toBreak, float fontSize, float length,
	AppContext_ty_c appContext);
/**
 * splits the string and returns a vector.
 */
[[nodiscard]] std::vector<std::string> BreakTextInVector(std::string const& toBreak, float fontSite,
	float length);

/**
 * returns the text absoluteHeight based of the parent relativeSize.
 */
[[nodiscard]] float GetElementTextHeight(Vector2 const& relativeSize, float absoluteHeight);

/**
 * modifies the string so it fits into a collider.
 * adds indicators(dots) if the string is modified.
 */
[[nodiscard]] std::string GetPrintableTextInCollider(std::string const& text,
	float fontSize, Rectangle colider, AppContext_ty_c appContext);
/**
 * modifies the string so it fits into a collider.
 * adds indicators(dots) if the string is modified.
 */
[[nodiscard]] std::string GetPrintablePlaceholderTextInCollider(std::string const& text,
	float fontSize, Rectangle colider, AppContext_ty_c appContext);

/**
 * removes whitespace from the beginning and the end of a string.
 */
void StripString(std::string& toStrip);

/**
 * modifies a string so it gets vertical aligned.
 */
[[nodiscard]] Vector2 GetVerticalAlignedTextPosition(std::string const& text,
	float fontSize, Rectangle colider, Alignment alignment);
/**
 * returns the vertical offset per line in a vector.
 */
[[nodiscard]] std::vector<float> GetVerticalAlignedOffset(std::vector<std::string> text,
	float fontSize, Rectangle colider, Alignment alignment);
/**
 * modifies a string so it gets horizontal aligned.
 */
[[nodiscard]] std::string GetHorizontalAlignedText(std::string const& text,
	Rectangle colider, float fontSize, Alignment alignment);
/**
 * returns the horizontal offset per line in a vector.
 */
[[nodiscard]] std::vector<float> GetHorizontalAlignedOffset(std::vector<std::string> text,
	Rectangle colider, float fontSize, Alignment alignment);

/**
 * draws the text with white shadow of need to
 */
void DrawTextWithOutline(std::string const& text, Vector2 position, float size, Color color, bool background);
