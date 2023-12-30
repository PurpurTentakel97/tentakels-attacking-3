//
// Purpur Tentakel
// 16.02.2022
//

#pragma once

#include <alias/AliasLogic.hpp>
#include <ui_lib/Scene.hpp>
#include <ui_lib/Table.hpp>


namespace ui {
    class PlanetTable final : public uil::Scene {
    private:
        lgk::Galaxy_ty_raw m_galaxy;
        uil::Table_ty m_table;

        void Initialization();

    public:
        PlanetTable(Vector2 pos, Vector2 size, uil::Alignment alignment, lgk::Galaxy_ty_raw galaxy);

        void SetActive(bool active, app::AppContext_ty_c appContext) override;
    };
} // namespace ui
