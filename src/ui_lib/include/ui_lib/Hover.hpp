//
// Purpur Tentakel
// 08.05.2023
//

#pragma once

#include "UIElement.hpp"


class Hover final : public UIElement {
private:
    std::string m_text;
    Color m_color;

    float m_textHeight;
    Vector2 m_textPosition{};
    Vector2 m_absoluteHoverOffset{};

    void CalculateDefault(app::AppContext_ty_c appContext);

public:
    Hover(float height, std::string text, Color color, Vector2 hoverOffset);

    [[nodiscard]] Vector2 GetRenderOffset() const;

    void SetRenderHover(Vector2 mousePosition, app::AppContext_ty_c appContext);

    void SetText(std::string const& text);

    void Render(app::AppContext_ty_c appContext) override;

    float RenderOffset(app::AppContext_ty_c appContext, Vector2 const& offset) const;

    void Resize(app::AppContext_ty_c appContext) override;
};
