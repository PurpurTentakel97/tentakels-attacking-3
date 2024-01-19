//
// Purpur Tentakel
// 15.05.2023
//

#include "HSceneFleetTable.hpp"
#include <alias/AliasUtils.hpp>
#include <helper/HFocusEvents.hpp>
#include <ui_lib/Table.hpp>
#include <ui_lib/Text.hpp>


namespace ui {
    void FleetAndTargetPointTable::Initialization(app::PlayerData const& currentPlayer) {
        app::AppContext_ty_c appContext{ app::AppContext::GetInstance() };
        utl::usize constexpr startFleets{ 2 };
        auto const startTargetPoints{ startFleets + (not m_galaxy.fleets.empty() ? m_galaxy.fleets.size() : 1) + 1 };
        auto const tableSize{ startTargetPoints
                              + (not m_galaxy.targetPoints.empty() ? m_galaxy.targetPoints.size() : 1) };

        m_table = std::make_shared<uil::Table>(GetElementPosition(0.0f, 0.0f),
                                               GetElementSize(1.0f, 1.0f),
                                               uil::Alignment::TOP_LEFT,
                                               1000,
                                               tableSize,
                                               4,
                                               Vector2(0.25f, 0.05f),
                                               0.2f);
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
        if (not m_galaxy.fleets.empty()) {
            for (utl::usize i = 0; i < m_galaxy.fleets.size(); ++i) {
                auto const& fleet{ m_galaxy.fleets.at(i) };

                app::PlayerData player{ appContext.playerCollection.GetPlayerOrNpcByID(fleet.playerID) };
                // fleet ID
                m_table->SetValue<utl::usize>(i + startFleets, 0, fleet.ID);
                m_table->SetSingleCellTextColor(player.color, i + startFleets, 0);

                // position
                std::string const pos{ GetStringFromPosition(fleet.position, false) };
                m_table->SetValue<std::string>(i + startFleets, 1, pos);

                // count
                m_table->SetValue<utl::usize>(i + startFleets, 2, fleet.shipCount);

                // destination
                auto const destination{ fleet.destRepresentation };
                std::string const dest = [&appContext, &destination, &fleet, &currentPlayer]() -> std::string {
                    if (fleet.playerID != currentPlayer.ID) {
                        return "---";
                    } else {
                        switch (destination.type) {
                            case utl::TargetType::PLANET:
                                return appContext.languageManager.Text("ui_fleet_table_dest_planet", destination.ID);
                            case utl::TargetType::FLEET:
                                return appContext.languageManager.Text("ui_fleet_table_dest_fleet", destination.ID);
                            case utl::TargetType::TARGET_POINT:
                                return appContext.languageManager.Text("ui_fleet_table_dest_target_point",
                                                                       destination.ID);
                            default:
                                return appContext.languageManager.Text("ui_fleet_table_dest_invalid", destination.ID);
                        }
                    }
                }();

                m_table->SetValue<std::string>(i + startFleets, 3, dest);
                if (fleet.playerID == currentPlayer.ID) {
                    m_table->SetSingleCellTextColor(
                            appContext.playerCollection.GetPlayerOrNpcByID(destination.playerID).color,
                            i + startFleets,
                            3);
                }
            }
        } else {
            m_table->SetValue<std::string>(
                    startFleets, 0, appContext.languageManager.Text("ui_fleet_table_no_fleets_text"));
        }

        m_table->SetValue<std::string>(
                startTargetPoints - 1, 0, appContext.languageManager.Text("ui_fleet_table_headline_target_point", ":"));
        if (not m_galaxy.targetPoints.empty()) {
            for (utl::usize i = 0; i < m_galaxy.targetPoints.size(); ++i) {
                auto const& targetPoint{ m_galaxy.targetPoints.at(i) };

                app::PlayerData player{ appContext.playerCollection.GetPlayerOrNpcByID(targetPoint.playerID) };
                // target point ID
                m_table->SetValue<utl::usize>(i + startTargetPoints, 0, targetPoint.ID);
                m_table->SetSingleCellTextColor(player.color, i + startTargetPoints, 0);

                // position
                std::string const pos{ GetStringFromPosition(targetPoint.position, true) };
                m_table->SetValue<std::string>(i + startTargetPoints, 1, pos);

                // return if the current player is not this player.


                // count
                m_table->SetValue<utl::usize>(i + startTargetPoints, 2, targetPoint.shipCount);

                m_table->SetValue<std::string>(i + startTargetPoints, 3, "---");
            }
        } else {
            m_table->SetValue<std::string>(
                    startTargetPoints, 0, appContext.languageManager.Text("ui_fleet_table_no_target_point"));
        }
    }

    std::string FleetAndTargetPointTable::GetStringFromPosition(utl::vec2pos_ty_ref_c position,
                                                                bool const getCoordinates) const {

        if (!getCoordinates) {
            for (auto const& p : m_galaxy.planets) {
                auto const& pos{ p.position };
                if (pos == position) {
                    return app::AppContext::GetInstance().languageManager.Text("ui_fleet_table_orig_planet", p.ID);
                }
            }
            for (auto const& t : m_galaxy.targetPoints) {
                auto const& pos{ t.position };
                if (pos == position) {
                    return app::AppContext::GetInstance().languageManager.Text("ui_fleet_table_orig_target_point",
                                                                               t.ID);
                }
            }
        }
        std::stringstream stream;

        stream << "X: " << position.x << " | Y: " << position.y;
        return stream.str();
    }

    FleetAndTargetPointTable::FleetAndTargetPointTable(Vector2 const pos,
                                                       Vector2 const size,
                                                       uil::Alignment const alignment,
                                                       utl::RepresentationGalaxy galaxy,
                                                       app::PlayerData const& currentPlayer)
        : Scene{ pos, size, alignment },
          m_galaxy{ std::move(galaxy) } {

        Initialization(currentPlayer);
    }

    void FleetAndTargetPointTable::SetActive(bool const active, app::AppContext_ty_c appContext) {

        if (active == m_active) {
            return;
        }

        if (m_table->IsNestedFocus() && !active) {
            hlp::DeleteFocusLayer();
            m_table->SetNestedFocus(false);
        }
        Scene::SetActive(active, appContext);
    }
} // namespace ui
