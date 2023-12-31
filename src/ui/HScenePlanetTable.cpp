//
// Purpur Tentakel
// 16.02.2022
//

#include "HScenePlanetTable.hpp"
#include <alias/AliasUtils.hpp>
#include <helper/HFocusEvents.hpp>
#include <logic/Galaxy.hpp>
#include <logic/Player.hpp>


namespace ui {
    void PlanetTable::Initialization() {
        auto const planets{ m_galaxy->GetPlanets() };
        app::AppContext_ty_c appContext{ app::AppContext::GetInstance() };

        utl::usize discoveredCount{ 0 };
        for (auto const& p : planets) {
            if (p->IsDiscovered()) {
                ++discoveredCount;
            }
        }

        m_table = std::make_shared<uil::Table>(
                GetElementPosition(0.0f, 0.0f),
                GetElementSize(1.0f, 1.0f),
                uil::Alignment::TOP_LEFT,
                1000,
                discoveredCount + 1,
                4,
                Vector2(0.25f, 0.05f),
                0.2f
        );
        m_table->SetAllEditable(false);
        m_table->SetFixedHeadline(true);
        m_table->SetScrollable(true);
        m_table->SetHighlightHover(true);
        m_table->SetHeadlineValues<std::string>(
                { appContext.languageManager.Text("ui_planet_table_headline_id"),
                  appContext.languageManager.Text("ui_planet_table_headline_player"),
                  appContext.languageManager.Text("ui_planet_table_headline_production"),
                  appContext.languageManager.Text("ui_planet_table_headline_ship_count") }
        );
        m_elements.push_back(m_table);

        utl::usize addedCount{ 0 };
        for (auto const& p : planets) {
            //testing
            if (discoveredCount == addedCount) {
                break;
            }
            if (not p->IsDiscovered()) {
                continue;
            } else {
                ++addedCount;
            }

            // planet ID
            m_table->SetValue(addedCount, 0, p->GetID());

            // player name
            std::string entry;
            Color color;
            if (p->IsDestroyed()) {
                entry = appContext.languageManager.Text("ui_planet_table_player_name_destroyed");
                color = WHITE;
            } else if (!p->IsDiscovered()) {
                entry = appContext.languageManager.Text("ui_planet_table_player_name_not_discovered");
                color = WHITE;
            } else {
                app::PlayerData const& player{ appContext.playerCollection.GetPlayerOrNpcByID(p->GetPlayer()->GetID()
                ) };
                entry = player.GetName();
                color = player.color;
            }
            m_table->SetValue<std::string>(addedCount, 1, entry);
            m_table->SetSingleCellTextColor(color, addedCount, 1);

            if (p->IsDestroyed()) {
                continue;
            }
            if (!p->IsDiscovered()) {
                continue;
            }

            // production
            m_table->SetValue(addedCount, 2, p->GetProduction());

            // ship count
            m_table->SetValue(addedCount, 3, p->GetShipCount());
        }
    }

    PlanetTable::PlanetTable(
            Vector2 const pos,
            Vector2 const size,
            uil::Alignment const alignment,
            lgk::Galaxy_ty_raw const galaxy
    )
        : Scene{ pos, size, alignment },
          m_galaxy{ galaxy } {

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
