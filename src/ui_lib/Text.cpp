//
// Purpur Tentakel
// 14.09.2022
//

#include "Text.hpp"
#include <AppContext.hpp>
#include <cassert>
#include <helper/HTextProcessing.hpp>

void Text::CreateToRender() {
    std::vector<std::string> const spitedText{ BreakLines(m_text) };
    std::vector<float> const horizontalOffset{
        hlp::GetHorizontalAlignedOffset(spitedText, m_collider, m_textSize, m_textAlignment)
    };
    std::vector<float> const verticalOffset{
        hlp::GetVerticalAlignedOffset(spitedText, m_textSize, m_collider, m_textAlignment)
    };

    assert(spitedText.size() == horizontalOffset.size());
    assert(spitedText.size() == verticalOffset.size());

    m_toRender.clear();
    for (size_t i = 0; i < spitedText.size(); ++i) {
        std::pair<std::string, Vector2> const a = {
            spitedText[i],
            { horizontalOffset[i] + m_collider.x, verticalOffset[i] + m_collider.y }
        };
        m_toRender.emplace_back(a);
    }
}

std::vector<std::string> Text::BreakLines(std::string const& toBreak) const {
    if (!m_lineBreaks) {
        return { toBreak };
    }

    std::vector<std::string> const toReturn{ hlp::BreakTextInVector(toBreak, m_textSize, m_collider.width) };

    return toReturn;
}

void Text::OpenURL() const {
    if (!m_URL.empty()) {
        ::OpenURL(m_URL.c_str());
    }
}

void Text::UpdateCollider() {
    UIElement::UpdateCollider();

    CreateToRender();
}

Text::Text(
        Vector2 const pos,
        Vector2 const size,
        Alignment const alignment,
        Alignment const textAlignment,
        float const textHeight,
        std::string text
)
    : UIElement{ pos, size, alignment },
      m_text{ std::move(text) },
      m_textHeight{ textHeight },
      m_textSize{ textHeight * AppContext::GetInstance().GetResolution().y },
      m_textAlignment{ textAlignment } {

    CreateToRender();
}

void Text::CheckAndUpdate(Vector2 const& mousePosition, AppContext_ty_c appContext) {

    UIElement::CheckAndUpdate(mousePosition, appContext);

    if (CheckCollisionPointRec(mousePosition, m_collider)) {
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            OpenURL();
        }
    }
}

void Text::Render(AppContext_ty_c) {
    for (auto const& [text, position] : m_toRender) {
        hlp::DrawTextWithOutline(text, position, m_textSize, m_color, m_renderBackground);
    }

    if (m_renderRectangle) {
        DrawRectangleLinesEx(m_collider, 1.0f, PURPLE);
    }
}

void Text::Resize(AppContext_ty_c appContext) {
    Resolution_ty_c resolution{ appContext.GetResolution() };
    UIElement::Resize(appContext);
    m_textSize = m_textHeight * resolution.y;
    CreateToRender();
}

void Text::SetPosition(Vector2 const pos) {
    UIElement::SetPosition(pos);
    CreateToRender();
}

void Text::SetSize(Vector2 const size) {
    UIElement::SetSize(size);
    CreateToRender();
}

void Text::SetCollider(Rectangle const collider) {
    UIElement::SetCollider(collider);
    CreateToRender();
}

float Text::GetRelativeTextHeight() const{
    return m_textSize;
}

void Text::SetText(std::string text) {
    m_text = std::move(text);
    CreateToRender();
}

std::string Text::GetText() const {
    return m_text;
}

void Text::SetColor(Color const color) {
    m_color = color;
}

Color Text::GetColor() const {
    return m_color;
}

void Text::SetURL(std::string URL) {
    hlp::StripString(URL);
    m_URL = URL;
}

void Text::ClearURL() {
    m_URL.clear();
}

std::string Text::GetURL() const {
    return m_URL;
}

void Text::LineBreaks(bool const lineBreaks) {
    m_lineBreaks = lineBreaks;
    CreateToRender();
}

void Text::RenderRectangle(bool const renderRectangle) {
    m_renderRectangle = renderRectangle;
}

void Text::SetRenderBackground(bool const isRenderBackground) {
    m_renderBackground = isRenderBackground;
}

bool Text::GetRenderBackground() const {
    return m_renderBackground;
}
