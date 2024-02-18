//
// Purpur Tentakel
// 09.11.2022
//

#pragma once

#include "UIGalaxyElement.hpp"
#include <utils/RepresentationSpaceObject.hpp>


namespace ui {
    class UIPlanet final : public UIGalaxyElement {
    private:
        utl::RepresentationPlanet m_planet;
        Vector2 m_renderOffset{};

    public:
        UIPlanet(utl::usize focusID,
                 utl::usize ID,
                 app::PlayerData const& player,
                 Vector2 pos,
                 Vector2 colliderPos,
                 utl::RepresentationPlanet planet);


        void UpdateHoverText() override;

        void CheckAndUpdate(Vector2 const& mousePosition, app::AppContext_ty_c appContext) override;

        virtual void RenderRing(app::AppContext_ty_c appContext) override;

        void Render(app::AppContext_ty_c appContext) override;
    };
} // namespace ui
