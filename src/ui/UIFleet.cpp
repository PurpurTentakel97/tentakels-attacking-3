//
// Purpur Tentakel
// 16.06.2023
//

#include "UIFleet.hpp"
#include "UIGalaxyElement.hpp"
#include <alias/AliasCustomRaylib.hpp>
#include <app/AppContext.hpp>
#include <logic/Fleet.hpp>
#include <ui_lib/ShipCountRing.hpp>


namespace ui {
    UIFleet::UIFleet(utl::usize const ID, app::PlayerData const& player, Vector2 const start, Vector2 const end, Vector2 const relativeStart, Vector2 const relativeEnd,
                 lgk::Fleet_ty_raw_c fleet, std::function<bool(Vector2 const&)> isInGalaxyCollider)
    : UIElement{ start, { 0.005f,0.01f }, uil::Alignment::MID_MID }, m_ID{ ID }, m_player{ player },
    m_relativeStart{ relativeStart }, m_relativeEnd{ relativeEnd }, m_fleet { fleet }, m_isInGalaxyCollider{ std::move(isInGalaxyCollider) },
    m_line{
        start,
        end,
        1.0f,
        player.color
    },
    m_hover{
        0.03f,
        "",
        player.color,
        Vector2(0.01f,0.01f)
    } {

        m_ring = std::make_shared<uil::CountRing>(
                Vector2{ m_pos.x - m_size.x / 2, m_pos.y - m_size.y / 2 },
                m_size,
                uil::Alignment::MID_MID,
                m_size.x,
                m_size.x * 3.0f,
                static_cast<int>(m_fleet->GetShipCount()),
                UIGalaxyElement::s_maxShipCount
        );
        Color color{ m_player.color };
        color.a = UIGalaxyElement::s_ringColorAlpha;
        m_ring->SetRingColor(color);

        UpdateHoverText();
    }

    utl::usize UIFleet::GetID() const {
        return m_ID;
    }

    bool UIFleet::IsColliding(Vector2 const& mousePosition) const {
        if (not m_isInGalaxyCollider(mousePosition)) {
            return false;
        }

        if (m_isDisplayAsPoint) {
            return CheckCollisionPointRec(mousePosition, m_collider);
        }

        cst::Resolution_ty_c resolution{ app::AppContext::GetInstance().GetResolution() };
        auto const& lineStart{ m_line.GetStart() };
        auto const& lineEnd{ m_line.GetEnd() };
        Vector2 const start{ lineStart.x * resolution.x, lineStart.y * resolution.y };
        Vector2 const end{
            lineEnd.x * resolution.x,
            lineEnd.y * resolution.y,
        };

        return CheckCollisionPointLine(mousePosition, start, end, 5);
    }

    bool UIFleet::IsRingOverlappingWithRectangle(Rectangle const& rect) const {
        return m_ring->IsOverlapping(rect);
    }

    app::PlayerData UIFleet::GetPlayer() const {
        return m_player;
    }

    void UIFleet::UpdateHoverText() {
        std::string const position{ "X: " + std::to_string(m_fleet->GetPos().x)
                                    + ", Y: " + std::to_string(m_fleet->GetPos().y) };
        std::string const text_1{ std::to_string(m_fleet->GetID()) + " | " + position + " |" };
        std::string const text_2{ std::to_string(m_fleet->GetShipCount()) };
        m_hover.SetText(app::AppContext::GetInstance().languageManager.Text("ui_fleet_hover", text_1, text_2));
    }

    void UIFleet::UpdatePositions(Rectangle const newCollider) {
        // update line
        cst::Resolution_ty_c resolution{ app::AppContext::GetInstance().GetResolution() };
        Vector2 const start{ (newCollider.x + newCollider.width * m_relativeStart.x) / resolution.x,
                             (newCollider.y + newCollider.height * m_relativeStart.y) / resolution.y };
        Vector2 const end{ (newCollider.x + newCollider.width * m_relativeEnd.x) / resolution.x,
                           (newCollider.y + newCollider.height * m_relativeEnd.y) / resolution.y };

        m_line.SetStart(start);
        m_line.SetEnd(end);
        m_line.Update();

        // update collider
        auto collider{ GetCollider() };
        collider.x = newCollider.x + newCollider.width * m_relativeStart.x;
        collider.y = newCollider.y + newCollider.height * m_relativeStart.y;
        SetCollider(collider);
        m_ring->SetPosition(m_pos);
    }

    void UIFleet::SetDisplayedAsPoint(bool const isDisplayedAsPoint) {
        m_isDisplayAsPoint = isDisplayedAsPoint;
    }

    bool UIFleet::IsDisplayAsPoint() const {
        return m_isDisplayAsPoint;
    }

    void UIFleet::CheckAndUpdate(Vector2 const& mousePosition, app::AppContext_ty_c appContext) {
        UIElement::CheckAndUpdate(mousePosition, appContext);
        m_ring->CheckAndUpdate(mousePosition, appContext);

        if (IsColliding(mousePosition)) {
            UpdateHoverText();
            m_hover.SetRenderHover(mousePosition, appContext);
        }
    }

    void UIFleet::Render(app::AppContext_ty_c appContext) {

        if (m_isDisplayAsPoint) {
            DrawCircle(
                    static_cast<int>(m_collider.x),
                    static_cast<int>(m_collider.y),
                    m_collider.width / 2,
                    m_player.color
            );
            return;
        }

        m_line.Render(appContext);
    }

    void UIFleet::RenderRing(app::AppContext_ty_c appContext) {
        m_ring->Render(appContext);
    }

    void UIFleet::Resize(app::AppContext_ty_c appContext) {
        UIElement::Resize(appContext);
        m_line.Resize(appContext);
        m_hover.Resize(appContext);
        m_ring->Resize(appContext);
    }
} // namespace ui
