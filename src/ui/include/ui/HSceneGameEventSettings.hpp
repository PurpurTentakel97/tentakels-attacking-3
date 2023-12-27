//
// Purpur Tentakel
// 24.10.2022
//

#pragma once
#include <AppContext.hpp>
#include <helper/HGameEventTypes.hpp>
#include <ui_lib/Scene.hpp>


class GameEventSettings : public Scene {
private:
    std::vector<CheckBox_ty> m_checkBoxes;
    std::array<std::pair<HGameEventType, std::string>, 7> m_text{
        {
         // clang-format off
        { HGameEventType::GLOBAL,         AppContext::GetInstance().languageManager.Text("ui_game_events_settings_event_all"            ) },
        { HGameEventType::PIRATES,        AppContext::GetInstance().languageManager.Text("ui_game_events_settings_event_pirates"        ) },
        { HGameEventType::REVOLTS,        AppContext::GetInstance().languageManager.Text("ui_game_events_settings_event_revolts"        ) },
        { HGameEventType::RENEGADE_SHIPS, AppContext::GetInstance().languageManager.Text("ui_game_events_settings_event_renegade_ships" ) },
        { HGameEventType::BLACK_HOLE,     AppContext::GetInstance().languageManager.Text("ui_game_events_settings_event_black_hole"     ) },
        { HGameEventType::SUPERNOVA,      AppContext::GetInstance().languageManager.Text("ui_game_events_settings_event_supernova"      ) },
        { HGameEventType::ENGINE_PROBLEM, AppContext::GetInstance().languageManager.Text("ui_game_events_settings_event_engine_problems") },
         // clang-format on
        }
    };

    void Initialize(unsigned int focusID);

    void SetChecked(unsigned int index, bool isChecked);

public:
    GameEventSettings(unsigned int focusID, Vector2 pos, Vector2 size, Alignment alignment);

    void SetRandom();
};
