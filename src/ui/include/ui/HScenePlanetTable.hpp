//
// Purpur Tentakel
// 16.02.2022
//

#pragma once

#include <alias/AliasLogic.hpp>
#include <ui_lib/Scene.hpp>
#include <ui_lib/Table.hpp>

class PlanetTable final : public Scene {
private:
    Galaxy_ty_raw m_galaxy;
    Table_ty m_table;

    void Initialization();

public:
    PlanetTable(Vector2 pos, Vector2 size, Alignment alignment, Galaxy_ty_raw galaxy);

    void SetActive(bool active, app::AppContext_ty_c appContext) override;
};
