//
// Purpur Tentakel
// 16.02.2022
//

#include "HScenePlanetTable.hpp"
#include <alias/AliasUtils.hpp>
#include <helper/HFocusEvents.hpp>
#include <ui_lib/TableCell.hpp>


namespace ui {
    void PlanetTable::Initialization() {
        auto const planets{ m_galaxy.planets };
        app::AppContext_ty_c appContext{ app::AppContext::GetInstance() };

        utl::usize discoveredCount{ 0 };
        for (auto const& p : planets) {
            if (p.isDiscovered) {
                ++discoveredCount;
            }
        }

        m_table = std::make_shared<uil::Table>(GetElementPosition(0.0f, 0.0f),
                                               GetElementSize(1.0f, 1.0f),
                                               uil::Alignment::TOP_LEFT,
                                               1000,
                                               discoveredCount + 1,
                                               5,
                                               Vector2(0.2f, 0.05f),
                                               0.2f);
        m_table->SetAllEditable(false);
        m_table->SetFixedHeadline(true);
        m_table->SetScrollable(true);
        m_table->SetHighlightHover(true);
        m_table->SetHeadlineValues<std::string>(
                { appContext.languageManager.Text("ui_planet_table_headline_id"),
                  appContext.languageManager.Text("ui_planet_table_headline_alias"),
                  appContext.languageManager.Text("ui_planet_table_headline_player"),
                  appContext.languageManager.Text("ui_planet_table_headline_production"),
                  appContext.languageManager.Text("ui_planet_table_headline_ship_count") });
        m_elements.push_back(m_table);

        utl::usize addedCount{ 0 };
        for (auto const& p : planets) {
            //testing
            if (discoveredCount == addedCount) {
                break;
            }
            if (not p.isDiscovered) {
                continue;
            } else {
                ++addedCount;
            }
            utl::usize column{ 0 };
            auto const incCol{ [&column = column]() { ++column; } };
            // planet ID
            m_table->SetValue(addedCount, column, p.ID);
            incCol();

            // alias
            m_table->SetValue(addedCount, column, appContext.aliasManager.Alias(p.ID, m_currentPlayer.ID));
            m_table->SetSingleEditable(addedCount, column, true);
            m_table->SetSingleCallback(addedCount, column, [this](uil::TableCell& c) {
                auto const index = m_table->Index(&c);
                auto const ID    = m_table->ValueCell<utl::usize>(index.first, index.second - 1);
                this->SetAlias(ID, std::move(c.Value<std::string>()));
            });
            incCol();

            // player name
            std::string entry;
            Color color;
            if (p.isDestroyed) {
                entry = appContext.languageManager.Text("ui_planet_table_player_name_destroyed");
                color = WHITE;
            } else if (not p.isDiscovered) {
                entry = appContext.languageManager.Text("ui_planet_table_player_name_not_discovered");
                color = WHITE;
            } else {
                app::PlayerData const& player{ appContext.playerCollection.GetPlayerOrNpcByID(p.playerID) };
                entry = player.GetName();
                color = player.color;
            }
            m_table->SetValue(addedCount, column, entry);
            m_table->SetSingleCellTextColor(color, addedCount, column);

            if (p.isDestroyed) {
                continue;
            }
            if (!p.isDiscovered) {
                continue;
            }
            incCol();

            // production
            m_table->SetValue(addedCount, column, p.production);
            incCol();

            // ship count
            m_table->SetValue(addedCount, column, p.shipCount);
        }
    }

    void PlanetTable::SetAlias(utl::usize spaceObjectID, std::string alias) {
        app::AppContext_ty appContext = app::AppContext::GetInstance();
        appContext.aliasManager.SetAlias(spaceObjectID, m_currentPlayer.ID, std::move(alias));
    }

    PlanetTable::PlanetTable(Vector2 const pos,
                             Vector2 const size,
                             uil::Alignment const alignment,
                             utl::RepresentationGalaxy galaxy,
                             app::PlayerData currentPlayer)
        : Scene{ pos, size, alignment },
          m_galaxy{ std::move(galaxy) },
          m_currentPlayer{ std::move(currentPlayer) } {

        Initialization();
    }
    void PlanetTable::SetActive(bool const active, app::AppContext_ty_c appContext) {

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
