//
// Purpur Tentakel
// 09.11.2022
//

#include "UIPlanet.hpp"
#include <app/AppContext.hpp>
#include <helper/HInput.hpp>
#include <logic/Planet.hpp>
#include <ui_lib/ShipCountRing.hpp>


namespace ui {
    UIPlanet::UIPlanet(utl::usize const focusID, utl::usize const ID, app::PlayerData const& player, Vector2 const pos,
	Vector2 const colliderPos, utl::RepresentationPlanet planet)
	:UIGalaxyElement{ focusID, ID, { 0.015f, 0.025f }, player, pos, colliderPos }, m_planet{ std::move(planet) } {

        app::AppContext_ty_c appContext{ app::AppContext::GetInstance() };
        auto const textSize =
                MeasureTextEx(*(appContext.assetManager.GetFont()), m_stringID.c_str(), m_collider.height, 0.0f);

        m_renderOffset = { (m_collider.width - textSize.x) / 2, (m_collider.height - textSize.y) / 2 };

        m_ring = std::make_shared<uil::CountRing>(m_pos,
                                                  m_size,
                                                  uil::Alignment::DEFAULT,
                                                  m_size.x / 2.0f,
                                                  m_size.x * 1.5f,
                                                  static_cast<int>(m_planet.shipCount),
                                                  s_maxShipCount);
        Color color{ m_currentPlayer.color };
        color.a = s_ringColorAlpha;
        m_ring->SetRingColor(color);

        UpdateHoverText();
    }

    void UIPlanet::UpdateHoverText() {
        std::string const position{ "X: " + std::to_string(m_planet.position.x)
                                    + ", Y: " + std::to_string(m_planet.position.y) };

        std::string hover{};
        if (m_planet.isDestroyed) {
            std::string const text_1{ m_currentPlayer.GetName() + " | " + position + " |" };
            std::string const text_2{ std::to_string(m_planet.shipCount) };
            hover = { app::AppContext::GetInstance().languageManager.Text("ui_planet_hover", text_1, text_2) };
        } else {
            hover = { m_currentPlayer.GetName() + " | " + position };
        }
        m_hover.SetText(hover);
    }

    void UIPlanet::CheckAndUpdate(Vector2 const& mousePosition, app::AppContext_ty_c appContext) {

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

    void UIPlanet::RenderRing(app::AppContext_ty_c appContext) {
        if (m_planet.isDiscovered) {
            m_ring->Render(appContext);
        }
    }

    void UIPlanet::Render(app::AppContext_ty_c appContext) {

        DrawCircle(static_cast<int>(m_collider.x + m_collider.width / 2),
                   static_cast<int>(m_collider.y + m_collider.height / 2),
                   m_collider.width / 2,
                   BLACK);

        DrawTextEx(*(appContext.assetManager.GetFont()),
                   m_stringID.c_str(),
                   { m_collider.x + m_renderOffset.x, m_collider.y + m_renderOffset.y },
                   m_collider.height,
                   0.0f,
                   m_color);
    }
} // namespace ui
