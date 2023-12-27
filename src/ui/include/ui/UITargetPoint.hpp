//
// Purpur Tentakel
// 09.11.2022
//

#pragma once
#include "UIGalaxyElement.hpp"
#include <helper/HLogicAlias.hpp>
#include <ui_lib/ShipCountRing.hpp>


class UITargetPoint final : public UIGalaxyElement {
private:
    TargetPoint_ty_raw_c m_targetPoint;

public:
    UITargetPoint(
            unsigned int focusID,
            unsigned int ID,
            PlayerData player,
            Vector2 pos,
            Vector2 colliderPos,
            TargetPoint_ty_raw_c targetPoint
    );

    void UpdateHoverText() override;

    void CheckAndUpdate(Vector2 const& mousePosition, AppContext_ty_c appContext) override;

    void RenderRing(AppContext_ty_c appContext) override;

    void Render(AppContext_ty_c appContext) override;
};
