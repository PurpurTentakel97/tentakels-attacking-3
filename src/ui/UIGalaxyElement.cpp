//
// Purpur Tentakel
// 15.06.2023
//

#include "UIGalaxyElement.hpp"
#include <alias/AliasCustomRaylib.hpp>
#include <app/AppContext.hpp>
#include <ui_lib/ShipCountRing.hpp>
#include <utils/Colors.hpp>


namespace ui {
    UIGalaxyElement::UIGalaxyElement(
            unsigned int const focusID,
            unsigned int const ID,
            Vector2 const size,
            app::PlayerData const& player,
            Vector2 const pos,
            Vector2 const colliderPos
    )
        : UIElement{ pos, size, uil::Alignment::MID_MID },
          Focusable{ focusID },
          m_ID{ ID },
          m_currentPlayer{ player },
          m_colliderPos{ colliderPos },
          m_color{ player.color },
          m_stringID{ std::to_string(ID) },
          m_hover{ 0.03f, "", player.color, Vector2(0.01f, 0.01f) } { }

    void UIGalaxyElement::UpdatePosition(Rectangle const newCollider) {
        cst::Resolution_ty_c resolution{ app::AppContext::GetInstance().GetResolution() };
        Vector2 const newPos{ (newCollider.x + newCollider.width * m_colliderPos.x) / resolution.x,
                              (newCollider.y + newCollider.height * m_colliderPos.y) / resolution.y };
        SetPosition(newPos);
        m_ring->SetPosition(m_pos);
    }

    void UIGalaxyElement::SetOnClick(std::function<void(UIGalaxyElement*)> onClick) {
        m_onClick = std::move(onClick);
    }

    void UIGalaxyElement::SetPlayer(app::PlayerData const player) {
        m_currentPlayer = std::move(player);
        if (utl::Colors::AreSame(m_color, GRAY)) {
            m_color = m_currentPlayer.color;
        }
    }

    app::PlayerData UIGalaxyElement::GetPlayer() const {
        return m_currentPlayer;
    }

    void UIGalaxyElement::SetColor(Color const color) {
        m_color = color;
    }

    Color UIGalaxyElement::GetColor() const {
        return m_color;
    }

    unsigned int UIGalaxyElement::GetID() const {
        return m_ID;
    }

    bool UIGalaxyElement::IsHover() const {
        return m_renderHover;
    }

    bool UIGalaxyElement::IsEnabled() const {
        return m_isEnabled;
    }

    void UIGalaxyElement::SetEnabled(bool const isEnabled) {
        m_isEnabled = isEnabled;
    }

    Rectangle UIGalaxyElement::GetCollider() const {
        return UIElement::GetCollider();
    }

    void UIGalaxyElement::Resize(app::AppContext_ty_c appContext) {

        m_hover.Resize(appContext);
        m_ring->Resize(appContext);
        UIElement::Resize(appContext);
    }
} // namespace ui
