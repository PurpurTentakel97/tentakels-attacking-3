//
// Purpur Tentakel
// 15.05.2023
//

#pragma once

#include <alias/AliasUtils.hpp>
#include <ui_lib/Scene.hpp>
#include <utils/GalaxyRepresentation.hpp>

namespace ui {
    class FleetAndTargetPointTable final : public uil::Scene {
    private:
        utl::GalaxyRepresentation m_galaxy;
        uil::Table_ty m_table;

        void Initialization(app::PlayerData const& currentPlayer);

        [[nodiscard]] std::string GetStringFromPosition(utl::vec2pos_ty_ref_c position, bool getCoordinates) const;

    public:
        FleetAndTargetPointTable(Vector2 pos,
                                 Vector2 size,
                                 uil::Alignment alignment,
                                 utl::GalaxyRepresentation galaxy,
                                 app::PlayerData const& currentPlayer);

        void SetActive(bool active, app::AppContext_ty_c appContext) override;
    };
} // namespace ui
