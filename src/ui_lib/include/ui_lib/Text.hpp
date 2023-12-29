//
// Purpur Tentakel
// 14.09.2022
//

#pragma once

#include "UIElement.hpp"
#include <string>


class Text final : public UIElement {
private:
    using render_ty = std::vector<std::pair<std::string const, Vector2>>;
    std::string m_text;
    render_ty m_toRender{};
    std::string m_URL{};
    float m_textHeight;
    float m_textSize;
    Alignment m_textAlignment;
    Color m_color{ WHITE };

    bool m_lineBreaks{ false };
    bool m_renderRectangle{ false };
    bool m_renderBackground{ false };


    void CreateToRender();

    [[nodiscard]] std::vector<std::string> BreakLines(std::string const& toBreak) const;

    void OpenURL() const;

    void UpdateCollider() override;

public:
    Text(Vector2 pos, Vector2 size, Alignment alignment, Alignment textAlignment, float textHeight, std::string text);

    void CheckAndUpdate(Vector2 const& mousePosition, app::AppContext_ty_c appContext) override;

    void Render(app::AppContext_ty_c appContext) override;

    void Resize(app::AppContext_ty_c appContext) override;

    void SetPosition(Vector2 pos) override;

    void SetSize(Vector2 size) override;

    void SetCollider(Rectangle collider) override;

    [[nodiscard]] float GetRelativeTextHeight() const;

    void SetText(std::string text);

    [[nodiscard]] std::string GetText() const;

    void SetColor(Color color);

    [[nodiscard]] Color GetColor() const;

    void SetURL(std::string URL);

    void ClearURL();

    [[nodiscard]] std::string GetURL() const;

    void LineBreaks(bool lineBreaks);

    void RenderRectangle(bool renderRectangle);

    void SetRenderBackground(bool isRenderBackground);

    [[nodiscard]] bool GetRenderBackground() const;
};
