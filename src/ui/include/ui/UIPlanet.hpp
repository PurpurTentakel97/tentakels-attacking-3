//
// Purpur Tentakel
// 09.11.2022
//

#pragma once
#include "UIGalaxyElement.hpp"
#include <helper/HLogicAlias.hpp>

/**
 * provides a Ui representation if the logic Planet.
 * gets implemented by the UIGalaxy.
 */
class UIPlanet final : public UIGalaxyElement {
private:
    Planet_ty_raw_c m_planet; ///< contains the logic Planet to this Planet
    Vector2 m_renderOffset;   ///< contains the offset to the collider for rendering

public:
    /**
	 * ctor.
	 * converts the id to a string.
	 */
    UIPlanet(
            unsigned int focusID,
            unsigned int ID,
            PlayerData player,
            Vector2 pos,
            Vector2 colliderPos,
            Planet_ty_raw_c planet
    );

    /**
	 * updates the hover text
	 */
    void UpdateHoverText() override;

    /**
	 * planet logic.
	 */
    void CheckAndUpdate(Vector2 const& mousePosition, AppContext_ty_c appContext) override;
    /**
	 * Renders the ring of the Element.
	 */
    void RenderRing(AppContext_ty_c appContext) override;
    /**
	 * renders the planet.
	 */
    void Render(AppContext_ty_c appContext) override;
};
