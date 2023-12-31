//
// Purpur Tentakel
// 25.09.2022
//

#pragma once

#include <CustomRaylib.hpp>
#include <alias/AliasApp.hpp>
#include <alias/AliasUiLib.hpp>
#include <string>
#include <vector>

namespace hlp {
    void BreakText(std::string& toBreak, float fontSize, float length, app::AppContext_ty_c appContext);

    [[nodiscard]] std::vector<std::string> BreakTextInVector(std::string const& toBreak, float fontSite, float length);

    [[nodiscard]] float GetElementTextHeight(Vector2 const& relativeSize, float absoluteHeight);

    [[nodiscard]] std::string GetPrintableTextInCollider(
            std::string const& text,
            float fontSize,
            Rectangle collider,
            app::AppContext_ty_c appContext
    );

    [[nodiscard]] std::string GetPrintablePlaceholderTextInCollider(
            std::string const& text,
            float fontSize,
            Rectangle collider,
            app::AppContext_ty_c appContext
    );

    void StripString(std::string& toStrip);

    [[nodiscard]] Vector2 GetVerticalAlignedTextPosition(
            std::string const& text,
            float fontSize,
            Rectangle collider,
            uil::Alignment alignment
    );

    [[nodiscard]] std::vector<float> GetVerticalAlignedOffset(
            std::vector<std::string> text,
            float fontSize,
            Rectangle collider,
            uil::Alignment alignment
    );

    [[nodiscard]] std::string
    GetHorizontalAlignedText(std::string const& text, Rectangle collider, float fontSize, uil::Alignment alignment);

    [[nodiscard]] std::vector<float> GetHorizontalAlignedOffset(
            std::vector<std::string> const& text,
            Rectangle collider,
            float fontSize,
            uil::Alignment alignment
    );

    void DrawTextWithOutline(std::string const& text, Vector2 position, float size, Color color, bool background);
} // namespace hlp
