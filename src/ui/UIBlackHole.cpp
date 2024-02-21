//
// Purpur Tentakel
// 18.02.2024
//

#include "UIBlackHole.hpp"
#include <helper/HInput.hpp>

namespace ui {
    UIBlackHole::UIBlackHole(utl::usize focusID,
                             utl::usize ID,
                             app::PlayerData const& player,
                             Vector2 pos,
                             Vector2 colliderPos,
                             utl::RepresentationBlackHole blackHole,
                             float radiusPerUnit)
        : UIGalaxyElement{ focusID, ID, { 0.015f, 0.025f }, player, pos, colliderPos },
          m_blackHole{ blackHole }, m_radiusPerUnit{radiusPerUnit} {
        app::AppContext_ty_c appContext{ app::AppContext::GetInstance() };
        auto const textSize =
                MeasureTextEx(*(appContext.assetManager.GetFont()), m_stringID.c_str(), m_collider.height, 0.0f);

        m_renderOffset = { (m_collider.width - textSize.x) / 2, (m_collider.height - textSize.y) / 2 };

        UpdateHoverText();
        UpdateRadius(1.0f);
    }

    void UIBlackHole::UpdateRadius(float scaleFactor) {
        auto const& resolution = app::AppContext::GetInstance().GetResolution();
        m_radius               = m_radiusPerUnit * static_cast<float>(m_blackHole.radius) * scaleFactor * resolution.x;
    }

    void UIBlackHole::UpdateHoverText() {
        auto const& appContext = app::AppContext::GetInstance();
        if (m_blackHole.isDiscovered) {
            m_hover.SetText(appContext.languageManager.Text("ui_black_hole_hover_discovered",
                                                            m_blackHole.position.x,
                                                            m_blackHole.position.y,
                                                            m_blackHole.radius));
        } else {
            m_hover.SetText(appContext.languageManager.Text(
                    "ui_black_hole_hover_not_discovered", m_blackHole.position.x, m_blackHole.position.y));
        }
    }

    void UIBlackHole::RenderRing(app::AppContext_ty_c) {
        DrawCircle(static_cast<int>(m_collider.x + m_collider.width / 2),
                   static_cast<int>(m_collider.y + m_collider.height / 2),
                   m_radius,
                   WHITE);
    }

    void UIBlackHole::Render(app::AppContext_ty_c appContext) {
        DrawTextEx(*(appContext.assetManager.GetFont()),
                   m_stringID.c_str(),
                   { m_collider.x + m_renderOffset.x, m_collider.y + m_renderOffset.y },
                   m_collider.height,
                   0.0f,
                   m_color);
    }

    void UIBlackHole::CheckAndUpdate(Vector2 const& mousePosition, app::AppContext_ty_c appContext) {
        UIElement::CheckAndUpdate(mousePosition, appContext);

        if (CheckCollisionPointRec(mousePosition, m_collider)) {
            if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
                m_onClick(this);
            }

            m_renderHover = true;
            UpdateHoverText();

        } else {
            m_renderHover = false;
        }

        if (m_renderHover) {
            m_hover.SetRenderHover(mousePosition, appContext);
        }

        if (IsFocused() && hlp::IsConfirmInputPressed()) {
            m_onClick(this);
        }
    }
} // namespace ui
