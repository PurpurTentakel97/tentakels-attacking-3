//
// Purpur Tentakel
// 09.11.2022
//

#pragma once
#include "UIGalaxyElement.hpp"
#include <helper/HLogicAlias.hpp>


class UIPlanet final : public UIGalaxyElement {
private:
    Planet_ty_raw_c m_planet;
    Vector2 m_renderOffset{};

public:
    UIPlanet(
            unsigned int focusID,
            unsigned int ID,
            PlayerData const& player,
            Vector2 pos,
            Vector2 colliderPos,
            Planet_ty_raw_c planet
    );


    void UpdateHoverText() override;


    void CheckAndUpdate(Vector2 const& mousePosition, AppContext_ty_c appContext) override;

    void RenderRing(AppContext_ty_c appContext) override;

    void Render(AppContext_ty_c appContext) override;
};
