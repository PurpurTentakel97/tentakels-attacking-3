//
// Purpur Tentakel
// 18.02.2024
//

#pragma once

#include "UIGalaxyElement.hpp"

namespace ui {
    class UIBlackHole final : public UIGalaxyElement {
    private:
        utl::RepresentationBlackHole m_blackHole;
        float m_radiusPerUnit;
        float m_radius{};
        Vector2 m_renderOffset{};

    public:
        UIBlackHole(utl::usize focusID,
                    utl::usize ID,
                    app::PlayerData const& player,
                    Vector2 pos,
                    Vector2 colliderPos,
                    utl::RepresentationBlackHole blackHole,
                    float radiusPerUnit);

        void UpdateRadius(float scaleFactor);

        // UIGalaxyElement
        void UpdateHoverText() override;

        // UIElement
        void RenderRing(app::AppContext_ty_c appContext) override;

        void Render(app::AppContext_ty_c appContext) override;

        void CheckAndUpdate(Vector2 const& mousePosition, app::AppContext_ty_c appContext) override;
    };
} // namespace ui
