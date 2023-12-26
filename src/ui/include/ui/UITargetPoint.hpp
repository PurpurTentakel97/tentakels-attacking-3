//
// Purpur Tentakel
// 09.11.2022
//

#pragma once
#include "UIGalaxyElement.hpp"
#include <helper/HLogicAlias.hpp>
#include <ui_lib/ShipCountRing.hpp>

/**
 * provides a Ui representation if the logic Planet.
 * gets implemented by the UIGalaxy.
 */
class UITargetPoint final : public UIGalaxyElement {
private:
    TargetPoint_ty_raw_c m_targetPoint; ///< contains the logic TargetPoint to this TargetPoint

public:
    /**
	 * ctor.
	 * converts the id to a string.
	 */
    UITargetPoint(
            unsigned int focusID,
            unsigned int ID,
            PlayerData player,
            Vector2 pos,
            Vector2 colliderPos,
            TargetPoint_ty_raw_c targetPoint
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
