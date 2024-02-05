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
    void FleetAndTargetPointTable::Initialization() {
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
                                               5,
                                               Vector2(0.2f, 0.05f),
                                               0.2f);
        m_table->SetAllEditable(false);
        m_table->SetFixedHeadline(true);
        m_table->SetScrollable(true);
        m_table->SetHighlightHover(true);
        m_table->SetHeadlineValues<std::string>({
                appContext.languageManager.Text("ui_fleet_table_headline_id"),
                appContext.languageManager.Text("ui_fleet_table_headline_alias"),
                appContext.languageManager.Text("ui_fleet_table_headline_position"),
                appContext.languageManager.Text("ui_fleet_table_headline_ship_count"),
                appContext.languageManager.Text("ui_fleet_table_headline_destination"),
        });
        m_elements.push_back(m_table);

        auto const onCellUpdate = [this](uil::TableCell& c) {
            auto const index = m_table->Index(&c);
            auto const ID    = m_table->ValueCell<utl::usize>(index.first, index.second - 1);
            SetAlias(ID, std::move(c.Value<std::string>()));
        };


        m_table->SetValue<std::string>(1, 0, appContext.languageManager.Text("ui_fleet_table_headline_fleets", ":"));
        if (not m_galaxy.fleets.empty()) {
            for (utl::usize i = 0; i < m_galaxy.fleets.size(); ++i) {
                auto const& fleet{ m_galaxy.fleets.at(i) };
                utl::usize const row{ i + startFleets };
                utl::usize column{ 0 };
                auto const incCol{ [&column = column]() { ++column; } };

                app::PlayerData player{ appContext.playerCollection.GetPlayerOrNpcByID(fleet.playerID) };
                // fleet ID
                m_table->SetValue(row, column, fleet.ID);
                m_table->SetSingleCellTextColor(player.color, row, column);
                incCol();

                // alias
                m_table->SetValue(row, column, appContext.aliasManager.Alias(fleet.ID, m_currentPlayer.ID));
                m_table->SetSingleEditable(row, column, true);
                m_table->SetSingleCallback(row, column, onCellUpdate);
                incCol();

                // position
                std::string const pos{ GetStringFromPosition(fleet.position, false) };
                m_table->SetValue<std::string>(row, column, pos);
                incCol();

                // count
                m_table->SetValue<utl::usize>(row, column, fleet.shipCount);
                incCol();

                // destination
                auto const destination{ fleet.destRepresentation };
                std::string const dest = [&appContext, &destination, &fleet, this]() -> std::string {
                    if (fleet.playerID != m_currentPlayer.ID) {
                        return "---";
                    } else {
                        switch (destination.type) {
                            case utl::SpaceObjectType::PLANET:
                                return appContext.languageManager.Text("ui_fleet_table_dest_planet", destination.ID);
                            case utl::SpaceObjectType::FLEET:
                                return appContext.languageManager.Text("ui_fleet_table_dest_fleet", destination.ID);
                            case utl::SpaceObjectType::TARGET_POINT:
                                return appContext.languageManager.Text("ui_fleet_table_dest_target_point",
                                                                       destination.ID);
                            default:
                                return appContext.languageManager.Text("ui_fleet_table_dest_invalid", destination.ID);
                        }
                    }
                }();

                m_table->SetValue<std::string>(row, column, dest);
                if (fleet.playerID == m_currentPlayer.ID) {
                    m_table->SetSingleCellTextColor(
                            appContext.playerCollection.GetPlayerOrNpcByID(destination.playerID).color, row, column);
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
                utl::usize row{ i + startTargetPoints };
                utl::usize column{ 0 };
                auto const incCol{ [&column = column]() { ++column; } };

                app::PlayerData player{ appContext.playerCollection.GetPlayerOrNpcByID(targetPoint.playerID) };
                // target point ID
                m_table->SetValue(row, column, targetPoint.ID);
                m_table->SetSingleCellTextColor(player.color, row, column);
                incCol();

                // alias
                m_table->SetValue(row, column, appContext.aliasManager.Alias(targetPoint.ID, m_currentPlayer.ID));
                m_table->SetSingleEditable(row, column, true);
                m_table->SetSingleCallback(row, column, onCellUpdate);
                incCol();

                // position
                std::string const pos{ GetStringFromPosition(targetPoint.position, true) };
                m_table->SetValue(row, column, pos);
                incCol();

                // count
                m_table->SetValue(row, column, targetPoint.shipCount);
                incCol();
                m_table->SetValue<std::string>(row, column, "---");
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

    void FleetAndTargetPointTable::SetAlias(utl::usize spaceObjectID, std::string alias) const {
        app::AppContext_ty appContext = app::AppContext::GetInstance();
        appContext.aliasManager.SetAlias(spaceObjectID, m_currentPlayer.ID, std::move(alias));
    }

    FleetAndTargetPointTable::FleetAndTargetPointTable(Vector2 const pos,
                                                       Vector2 const size,
                                                       uil::Alignment const alignment,
                                                       utl::RepresentationGalaxy galaxy,
                                                       app::PlayerData currentPlayer)
        : Scene{ pos, size, alignment },
          m_galaxy{ std::move(galaxy) },
          m_currentPlayer{ std::move(currentPlayer) } {

        Initialization();
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
