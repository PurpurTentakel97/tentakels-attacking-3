//
// Purpur Tentakel
// 15.06.2023
//

#include "UIGalaxyElement.hpp"
#include <AppContext.hpp>
#include <helper/HColors.hpp>
#include <ui_lib/ShipCountRing.hpp>

UIGalaxyElement::UIGalaxyElement(
        unsigned int focusID,
        unsigned int ID,
        Vector2 size,
        PlayerData player,
        Vector2 pos,
        Vector2 colliderPos
)
    : UIElement{ pos, size, Alignment::MID_MID },
      Focusable{ focusID },
      m_ID{ ID },
      m_currentPlayer{ player },
      m_colliderPos{ colliderPos },
      m_color{ player.color },
      m_stringID{ std::to_string(ID) },
      m_hover{ 0.03f, "", player.color, Vector2(0.01f, 0.01f) } { }

void UIGalaxyElement::UpdatePosition(Rectangle newCollider) {
    Resolution_ty_c resolution{ AppContext::GetInstance().GetResolution() };
    Vector2 const newPos{ (newCollider.x + newCollider.width * m_colliderPos.x) / resolution.x,
                          (newCollider.y + newCollider.height * m_colliderPos.y) / resolution.y };
    SetPosition(newPos);
    m_ring->SetPosition(m_pos);
}

void UIGalaxyElement::SetOnClick(std::function<void(UIGalaxyElement*)> onClick) {
    m_onClick = onClick;
}

void UIGalaxyElement::SetPlayer(PlayerData player) {
    m_currentPlayer = player;
    if (Colors::AreSame(m_color, GRAY)) {
        m_color = m_currentPlayer.color;
    }
}
PlayerData UIGalaxyElement::GetPlayer() const {
    return m_currentPlayer;
}

void UIGalaxyElement::SetColor(Color color) {
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
void UIGalaxyElement::SetEnabled(bool isEnabled) {
    m_isEnabled = isEnabled;
}

Rectangle UIGalaxyElement::GetCollider() const {
    return UIElement::GetCollider();
}
void UIGalaxyElement::Resize(AppContext_ty_c appContext) {

    m_hover.Resize(appContext);
    m_ring->Resize(appContext);
    UIElement::Resize(appContext);
}
