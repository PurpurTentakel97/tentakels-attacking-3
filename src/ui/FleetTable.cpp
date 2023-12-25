//
// Purpur Tentakel
// 15.05.2023
//

#include "FleetTable.h"
#include "helper/HFocusEvents.h"
#include "logic/Galaxy.h"
#include "logic/Player.h"
#include "ui_lib/Table.h"
#include "ui_lib/Text.h"

void FleetAndTargetPointTable::Initialization(PlayerData currentPlayer) {
    AppContext_ty_c appContext{ AppContext::GetInstance() };
    auto const fleets{ m_galaxy->GetFleets() };
    auto const targetPoints{ m_galaxy->GetTargetPoints() };
    int constexpr startFleets{ 2 };
    auto const startTargetPoints{ startFleets + (fleets.size() > 0 ? fleets.size() : 1) + 1 };
    auto const tableSize{ startTargetPoints + (targetPoints.size() > 0 ? targetPoints.size() : 1) };

    m_table = std::make_shared<Table>(
            GetElementPosition(0.0f, 0.0f),
            GetElementSize(1.0f, 1.0f),
            Alignment::TOP_LEFT,
            1000,
            tableSize,
            4,
            Vector2(0.25f, 0.05f),
            0.2f
    );
    m_table->SetAllEditable(false);
    m_table->SetFixedHeadline(true);
    m_table->SetScrollable(true);
    m_table->SetHighlightHover(true);
    m_table->SetHeadlineValues<std::string>({
            appContext.languageManager.Text("ui_fleet_table_headline_id"),
            appContext.languageManager.Text("ui_fleet_table_headline_position"),
            appContext.languageManager.Text("ui_fleet_table_headline_ship_count"),
            appContext.languageManager.Text("ui_fleet_table_headline_destination"),
    });
    m_elements.push_back(m_table);

    m_table->SetValue<std::string>(1, 0, appContext.languageManager.Text("ui_fleet_table_headline_fleets", ":"));
    if (fleets.size() > 0) {
        for (size_t i = 0; i < fleets.size(); ++i) {
            auto const fleet{ fleets.at(i) };

            PlayerData player{ appContext.playerCollection.GetPlayerOrNpcByID(fleet->GetPlayer()->GetID()) };
            // fleet ID
            m_table->SetValue<int>(i + startFleets, 0, static_cast<int>(fleet->GetID()));
            m_table->SetSingleCellTextColor(player.color, i + startFleets, 0);

            // position
            std::string const pos{ GetStringFromPosition(fleet->GetPos(), false) };
            m_table->SetValue<std::string>(i + startFleets, 1, pos);

            // count
            m_table->SetValue<int>(i + startFleets, 2, static_cast<int>(fleet->GetShipCount()));

            // destination
            auto const destination{ fleet->GetTarget() };
            std::string dest;
            if (fleet->GetPlayer()->GetID() != currentPlayer.ID) {
                dest = "---";
            } else if (destination->IsPlanet()) {
                dest = appContext.languageManager.Text("ui_fleet_table_dest_planet", destination->GetID());
            } else if (destination->IsFleet()) {
                dest = appContext.languageManager.Text("ui_fleet_table_dest_fleet", destination->GetID());
            } else if (destination->IsTargetPoint()) {
                dest = appContext.languageManager.Text("ui_fleet_table_dest_target_point", destination->GetID());
            } else {
                dest = appContext.languageManager.Text("ui_fleet_table_dest_invalid");
            }
            m_table->SetValue<std::string>(i + startFleets, 3, dest);
            if (fleet->GetPlayer()->GetID() == currentPlayer.ID) {
                m_table->SetSingleCellTextColor(
                        appContext.playerCollection.GetPlayerOrNpcByID(destination->GetPlayer()->GetID()).color,
                        i + startFleets,
                        3
                );
            }
        }
    } else {
        m_table->SetValue<std::string>(
                startFleets,
                0,
                appContext.languageManager.Text("ui_fleet_table_no_fleets_text")
        );
    }

    m_table->SetValue<std::string>(
            startTargetPoints - 1,
            0,
            appContext.languageManager.Text("ui_fleet_table_headline_target_point", ":")
    );
    if (targetPoints.size() > 0) {
        for (size_t i = 0; i < targetPoints.size(); ++i) {
            auto const targetPoint{ targetPoints.at(i) };

            PlayerData player{ appContext.playerCollection.GetPlayerOrNpcByID(targetPoint->GetPlayer()->GetID()) };
            // target point ID
            m_table->SetValue<int>(i + startTargetPoints, 0, static_cast<int>(targetPoint->GetID()));
            m_table->SetSingleCellTextColor(player.color, i + startTargetPoints, 0);

            // position
            std::string const pos{ GetStringFromPosition(targetPoint->GetPos(), true) };
            m_table->SetValue<std::string>(i + startTargetPoints, 1, pos);

            // return if the current player is not this player.


            // count
            m_table->SetValue<int>(i + startTargetPoints, 2, static_cast<int>(targetPoint->GetShipCount()));

            m_table->SetValue<std::string>(i + startTargetPoints, 3, "---");
        }
    } else {
        m_table->SetValue<std::string>(
                startTargetPoints,
                0,
                appContext.languageManager.Text("ui_fleet_table_no_target_point")
        );
    }
}

std::string FleetAndTargetPointTable::GetStringFromPosition(vec2pos_ty position, bool const getCoordinates) const {

    if (!getCoordinates) {
        for (auto const& p : m_galaxy->GetPlanets()) {
            auto const& pos{ p->GetPos() };
            if (pos == position) {
                return AppContext::GetInstance().languageManager.Text("ui_fleet_table_orig_planet", p->GetID());
            }
        }
        for (auto const& t : m_galaxy->GetTargetPoints()) {
            auto const& pos{ t->GetPos() };
            if (pos == position) {
                return AppContext::GetInstance().languageManager.Text("ui_fleet_table_orig_target_point", t->GetID());
            }
        }
    }
    std::stringstream stream;

    stream << "X: " << position.x << " | Y: " << position.y;
    return stream.str();
}

FleetAndTargetPointTable::FleetAndTargetPointTable(
        Vector2 pos,
        Vector2 size,
        Alignment alignment,
        Galaxy_ty_raw galaxy,
        PlayerData currentPlayer
)
    : Scene{ pos, size, alignment },
      m_galaxy{ galaxy } {

    Initialization(currentPlayer);
}

void FleetAndTargetPointTable::SetActive(bool active, AppContext_ty_c appContext) {

    if (active == m_active) {
        return;
    }

    if (m_table->IsNestedFocus() && !active) {
        DeleteFocusLayer();
        m_table->SetNestedFocus(false);
    }
    Scene::SetActive(active, appContext);
}
