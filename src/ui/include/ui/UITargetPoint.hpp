//
// Purpur Tentakel
// 09.11.2022
//

#pragma once

#include "UIGalaxyElement.hpp"
#include <ui_lib/ShipCountRing.hpp>
#include <utils/TargetPointRepresentation.hpp>


namespace ui {
    class UITargetPoint final : public UIGalaxyElement {
    private:
        utl::TargetPointRepresentation m_targetPoint;

    public:
        UITargetPoint(
                utl::usize focusID,
                utl::usize ID,
                app::PlayerData const& player,
                Vector2 pos,
                Vector2 colliderPos,
                      utl::TargetPointRepresentation targetPoint);

        void UpdateHoverText() override;

        void CheckAndUpdate(Vector2 const& mousePosition, app::AppContext_ty_c appContext) override;

        void RenderRing(app::AppContext_ty_c appContext) override;

        void Render(app::AppContext_ty_c appContext) override;
    };
} // namespace ui
