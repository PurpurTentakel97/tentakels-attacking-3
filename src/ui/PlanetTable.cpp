//
// Purpur Tentakel
// 16.02.2022
//

#include "PlanetTable.h"
#include "helper/HFocusEvents.h"
#include "logic/Player.h"

void PlanetTable::Initialization() {
    auto const planets{ m_galaxy->GetPlanets() };
    AppContext_ty_c appContext{ AppContext::GetInstance() };

    size_t discoveredCount{ 0 };
    for (auto const& p : planets) {
        if (p->IsDiscovered()) {
            ++discoveredCount;
        }
    }

    m_table = std::make_shared<Table>(
            GetElementPosition(0.0f, 0.0f),
            GetElementSize(1.0f, 1.0f),
            Alignment::TOP_LEFT,
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
    m_table->SetHeadlineValues<std::string>({ appContext.languageManager.Text("ui_planet_table_headline_id"),
                                              appContext.languageManager.Text("ui_planet_table_headline_player"),
                                              appContext.languageManager.Text("ui_planet_table_headline_production"),
                                              appContext.languageManager.Text("ui_planet_table_headline_ship_count") });
    m_elements.push_back(m_table);

    size_t addedCount{ 0 };
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
        m_table->SetValue<int>(addedCount, 0, static_cast<int>(p->GetID()));

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
            PlayerData const& player{ appContext.playerCollection.GetPlayerOrNpcByID(p->GetPlayer()->GetID()) };
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
        m_table->SetValue<int>(addedCount, 2, static_cast<int>(p->GetProduction()));

        // ship count
        m_table->SetValue<int>(addedCount, 3, static_cast<int>(p->GetShipCount()));
    }
}

PlanetTable::PlanetTable(Vector2 pos, Vector2 size, Alignment alignment, Galaxy_ty_raw galaxy)
    : Scene{ pos, size, alignment },
      m_galaxy{ galaxy } {

    Initialization();
}

void PlanetTable::SetActive(bool active, AppContext_ty_c appContext) {

    if (active == m_active) {
        return;
    }

    if (m_table->IsNestedFocus() && !active) {
        DeleteFocusLayer();
        m_table->SetNestedFocus(false);
    }
    Scene::SetActive(active, appContext);
}
