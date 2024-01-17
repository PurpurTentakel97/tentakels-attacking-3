//
// Purpur Tentakel
// 09.11.2022
//

#pragma once

#include "UIGalaxyElement.hpp"
#include <utils/PlanetRepresentation.hpp>


namespace ui {
    class UIPlanet final : public UIGalaxyElement {
    private:
        utl::PlanetRepresentation m_planet;
        Vector2 m_renderOffset{};

    public:
        UIPlanet(
                utl::usize focusID,
                utl::usize ID,
                app::PlayerData const& player,
                Vector2 pos,
                Vector2 colliderPos,
                 utl::PlanetRepresentation planet);


        void UpdateHoverText() override;


        void CheckAndUpdate(Vector2 const& mousePosition, app::AppContext_ty_c appContext) override;

        void RenderRing(app::AppContext_ty_c appContext) override;

        void Render(app::AppContext_ty_c appContext) override;
    };
} // namespace ui
