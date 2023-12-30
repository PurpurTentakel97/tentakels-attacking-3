//
// Purpur Tentakel
// 08.05.2023
//

#include "Hover.hpp"
#include <alias/AliasCustomRaylib.hpp>
#include <app/AppContext.hpp>
#include <event/EventsUI.hpp>
#include <helper/HTextProcessing.hpp>


namespace uil {
    void Hover::CalculateDefault(app::AppContext_ty_c appContext) {
        cst::Resolution_ty_c resolution{ appContext.GetResolution() };
        Vector2 const textOffset{
            resolution.x * 0.01f,
            resolution.y * 0.01f,
        };

        Vector2 const measure = MeasureTextEx(*appContext.assetManager.GetFont(), m_text.c_str(), m_textHeight, 0.0f);

        Rectangle const newCollider{ m_collider.x, m_collider.y, measure.x + textOffset.x, measure.y + textOffset.y };
        SetCollider(newCollider);

        m_textPosition = { m_collider.x + textOffset.x / 2, m_collider.y + textOffset.y / 2 };
    }

    Hover::Hover(float const height, std::string text, Color const color, Vector2 const hoverOffset)
	: UIElement{ { 0.0f, 0.0f }, { 0.0f, 0.0f }, Alignment::BOTTOM_LEFT },
      m_text{ std::move(text) },m_color(color), m_textHeight{ 0.0f } {

        app::AppContext_ty appContext{ app::AppContext::GetInstance() };
        cst::Resolution_ty_c resolution{ appContext.GetResolution() };
        m_textHeight = { height * resolution.y };

        CalculateDefault(appContext);


        m_absoluteHoverOffset = { hoverOffset.x * resolution.x, hoverOffset.y * resolution.y };
    }

    Vector2 Hover::GetRenderOffset() const {
        cst::Resolution_ty_c resolution{ app::AppContext::GetInstance().GetResolution() };
        Vector2 renderOffset{ 0, 0 };
        if (m_collider.x + m_collider.width > resolution.x) {
            renderOffset.x = m_collider.x + m_collider.width - resolution.x;
        }
        if (m_collider.y < 0) {
            renderOffset.y = -m_collider.y;
        }

        return renderOffset;
    }

    void Hover::SetRenderHover(Vector2 const mousePosition, app::AppContext_ty_c appContext) {
        Rectangle const newCollider{ mousePosition.x + m_absoluteHoverOffset.x,
                                     mousePosition.y - m_absoluteHoverOffset.y - m_collider.height,
                                     m_collider.width,
                                     m_collider.height };
        SetCollider(newCollider);
        CalculateDefault(appContext);

        eve::RenderHoverEvent event{ this };
        appContext.eventManager.InvokeEvent(event);
    }

    void Hover::SetText(std::string const& text) {
        m_text = { text };
    }

    void Hover::Render(app::AppContext_ty_c appContext) {
        auto const& renderOffset{ GetRenderOffset() };
        RenderOffset(appContext, renderOffset);
    }

    float Hover::RenderOffset(app::AppContext_ty_c, Vector2 const& offset) const {
        Rectangle const dummyCollider{ m_collider.x - offset.x,
                                       m_collider.y - offset.y,
                                       m_collider.width,
                                       m_collider.height };
        Vector2 const dummyTextPosition{ m_textPosition.x - offset.x, m_textPosition.y - offset.y };

        DrawRectangleRec(dummyCollider, GREY_100);
        DrawRectangleLinesEx(dummyCollider, 2.0f, PURPLE);

        hlp::DrawTextWithOutline(m_text, dummyTextPosition, m_textHeight, m_color, true);

        return m_collider.height;
    }

    void Hover::Resize(app::AppContext_ty_c appContext) {
        UIElement::Resize(appContext);
        CalculateDefault(appContext);
    }
} // namespace uil
