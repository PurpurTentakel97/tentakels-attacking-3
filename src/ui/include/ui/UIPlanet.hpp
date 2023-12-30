//
// Purpur Tentakel
// 09.11.2022
//

#pragma once

#include "UIGalaxyElement.hpp"


class UIPlanet final : public UIGalaxyElement {
private:
    lgk::Planet_ty_raw_c m_planet;
    Vector2 m_renderOffset{};

public:
    UIPlanet(
            unsigned int focusID,
            unsigned int ID,
            app::PlayerData const& player,
            Vector2 pos,
            Vector2 colliderPos,
            lgk::Planet_ty_raw_c planet
    );


    void UpdateHoverText() override;


    void CheckAndUpdate(Vector2 const& mousePosition, app::AppContext_ty_c appContext) override;

    void RenderRing(app::AppContext_ty_c appContext) override;

    void Render(app::AppContext_ty_c appContext) override;
};
