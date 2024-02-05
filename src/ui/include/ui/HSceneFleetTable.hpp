//
// Purpur Tentakel
// 15.05.2023
//

#pragma once

#include <alias/AliasUtils.hpp>
#include <ui_lib/Scene.hpp>
#include <utils/RepresentationGalaxy.hpp>

namespace ui {
    class FleetAndTargetPointTable final : public uil::Scene {
    private:
        utl::RepresentationGalaxy m_galaxy;
        uil::Table_ty m_table;
        app::PlayerData m_currentPlayer;

        void Initialization();

        [[nodiscard]] std::string GetStringFromPosition(utl::vec2pos_ty_ref_c position, bool getCoordinates) const;

        void SetAlias(utl::usize spaceObjectID, std::string alias) const;

    public:
        FleetAndTargetPointTable(Vector2 pos,
                                 Vector2 size,
                                 uil::Alignment alignment,
                                 utl::RepresentationGalaxy galaxy,
                                 app::PlayerData currentPlayer);

        void SetActive(bool active, app::AppContext_ty_c appContext) override;
    };
} // namespace ui
