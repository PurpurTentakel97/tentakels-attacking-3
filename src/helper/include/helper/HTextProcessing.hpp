//
// Purpur Tentakel
// 25.09.2022
//

#pragma once
#include "HLogicAlias.hpp"
#include <CustomRaylib.hpp>
#include <string>
#include <vector>

enum class Alignment;

namespace hlp {
    void BreakText(std::string& toBreak, float fontSize, float length, AppContext_ty_c appContext);

    [[nodiscard]] std::vector<std::string> BreakTextInVector(std::string const& toBreak, float fontSite, float length);

    [[nodiscard]] float GetElementTextHeight(Vector2 const& relativeSize, float absoluteHeight);

    [[nodiscard]] std::string
    GetPrintableTextInCollider(std::string const& text, float fontSize, Rectangle collider, AppContext_ty_c appContext);

    [[nodiscard]] std::string GetPrintablePlaceholderTextInCollider(
            std::string const& text,
            float fontSize,
            Rectangle collider,
            AppContext_ty_c appContext
    );

    void StripString(std::string& toStrip);

    [[nodiscard]] Vector2
    GetVerticalAlignedTextPosition(std::string const& text, float fontSize, Rectangle collider, Alignment alignment);

    [[nodiscard]] std::vector<float>
    GetVerticalAlignedOffset(std::vector<std::string> text, float fontSize, Rectangle collider, Alignment alignment);

    [[nodiscard]] std::string
    GetHorizontalAlignedText(std::string const& text, Rectangle collider, float fontSize, Alignment alignment);

    [[nodiscard]] std::vector<float> GetHorizontalAlignedOffset(
            std::vector<std::string> const& text,
            Rectangle collider,
            float fontSize,
            Alignment alignment
    );

    void DrawTextWithOutline(std::string const& text, Vector2 position, float size, Color color, bool background);
} // namespace hlp
