//
// Purpur Tentakel
// 16.06.2023
//

#pragma once

#include <app/PlayerCollection.hpp>
#include <ui_lib/Hover.hpp>
#include <ui_lib/Line.hpp>
#include <ui_lib/UIElement.hpp>
#include <utils/RepresentationSpaceObject.hpp>


namespace ui {
    class UIFleet final : public uil::UIElement {
    private:
        utl::usize m_ID;
        app::PlayerData m_player;
        Vector2 m_relativeStart;
        Vector2 m_relativeEnd;
        utl::RepresentationFleet m_fleet;
        std::function<bool(Vector2 const&)> m_isInGalaxyCollider;
        uil::Line m_line;
        uil::Hover m_hover;
        bool m_isDisplayAsPoint{ false };
        uil::CountRing_ty m_ring{ nullptr };

    public:
        UIFleet(utl::usize ID,
                app::PlayerData const& player,
                Vector2 start,
                Vector2 end,
                Vector2 relativeStart,
                Vector2 relativeEnd,
                utl::RepresentationFleet fleet,
                std::function<bool(Vector2 const&)> isInGalaxyCollider);

        [[nodiscard]] utl::usize GetID() const;

        [[nodiscard]] bool IsColliding(Vector2 const& mousePosition) const;

        [[nodiscard]] bool IsRingOverlappingWithRectangle(Rectangle const& rect) const;

        [[nodiscard]] app::PlayerData GetPlayer() const;

        void UpdateHoverText();

        void UpdatePositions(Rectangle newCollider);

        void SetDisplayedAsPoint(bool isDisplayedAsPoint);

        [[nodiscard]] bool IsDisplayAsPoint() const;

        void CheckAndUpdate(Vector2 const&, app::AppContext_ty_c appContext) override;

        void Render(app::AppContext_ty_c appContext) override;

        void RenderRing(app::AppContext_ty_c appContext);

        void Resize(app::AppContext_ty_c appContext) override;
    };
} // namespace ui
