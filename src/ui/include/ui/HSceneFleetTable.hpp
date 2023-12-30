//
// Purpur Tentakel
// 15.05.2023
//

#pragma once

#include <ui_lib/Scene.hpp>


class FleetAndTargetPointTable final : public uil::Scene {
private:
    lgk::Galaxy_ty_raw m_galaxy;
    uil::Table_ty m_table;

    void Initialization(app::PlayerData const& currentPlayer);

    [[nodiscard]] std::string GetStringFromPosition(utl::vec2pos_ty_ref_c position, bool getCoordinates) const;

public:
    FleetAndTargetPointTable(
            Vector2 pos,
            Vector2 size,
            uil::Alignment alignment,
            lgk::Galaxy_ty_raw galaxy,
            app::PlayerData const& currentPlayer
    );

    void SetActive(bool active, app::AppContext_ty_c appContext) override;
};
