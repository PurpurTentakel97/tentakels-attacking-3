//
// Purpur Tentakel
// 09.11.2022
//

#include "UITargetPoint.hpp"
#include <app/AppContext.hpp>
#include <helper/HInput.hpp>
#include <logic/Player.hpp>
#include <logic/TargetPoint.hpp>


namespace ui {
    UITargetPoint::UITargetPoint(utl::usize const focusID, utl::usize const ID, app::PlayerData const& player, Vector2 const pos,
                                 Vector2 const colliderPos, utl::RepresentationTargetPoint targetPoint)
        : UIGalaxyElement{ focusID, ID,{ 0.005f,0.01f },  player, pos, colliderPos }, m_targetPoint{ std::move(targetPoint) } {

        m_ring = std::make_shared<uil::CountRing>(m_pos,
                                                  m_size,
                                                  uil::Alignment::DEFAULT,
                                                  m_size.x / 2.0f,
                                                  m_size.x * 1.5f,
                                                  static_cast<int>(m_targetPoint.shipCount),
                                                  s_maxShipCount);
        Color color{ m_currentPlayer.color };
        color.a = s_ringColorAlpha;
        m_ring->SetRingColor(color);
        UpdateHoverText();
    }

    void UITargetPoint::UpdateHoverText() {
        std::string const position{ "x: " + std::to_string(m_targetPoint.position.x)
                                    + ", y: " + std::to_string(m_targetPoint.position.y) };
        std::string const text_1{ std::to_string(m_targetPoint.ID) + " | " + position + " |" };
        std::string const text_2{ std::to_string(m_targetPoint.shipCount) };
        m_hover.SetText(app::AppContext::GetInstance().languageManager.Text("ui_target_point_hover", text_1, text_2));
    }

    void UITargetPoint::CheckAndUpdate(Vector2 const& mousePosition, app::AppContext_ty_c appContext) {

        UIElement::CheckAndUpdate(mousePosition, appContext);
        m_ring->CheckAndUpdate(mousePosition, appContext);

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

    void UITargetPoint::RenderRing(app::AppContext_ty_c appContext) {
        if (m_targetPoint.isDiscovered) {
            m_ring->Render(appContext);
        }
    }

    void UITargetPoint::Render(app::AppContext_ty_c) {


        DrawCircle(static_cast<int>(m_collider.x + m_collider.width / 2),
                   static_cast<int>(m_collider.y + m_collider.height / 2),
                   m_collider.width / 2,
                   m_color);
    }
} // namespace ui
