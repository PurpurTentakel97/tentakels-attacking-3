//
// Purpur Tentakel
// 24.10.2022
//

#pragma once

#include <ui_lib/Scene.hpp>


namespace ui {
    class GameEventSettings : public uil::Scene {
    private:
        std::vector<uil::CheckBox_ty> m_checkBoxes;
        std::array<std::pair<cst::HGameEventType, std::string>, 7> m_text{
            {
             // clang-format off
        { cst::HGameEventType::GLOBAL,         app::AppContext::GetInstance().languageManager.Text("ui_game_events_settings_event_all"            ) },
        { cst::HGameEventType::PIRATES,        app::AppContext::GetInstance().languageManager.Text("ui_game_events_settings_event_pirates"        ) },
        { cst::HGameEventType::REVOLTS,        app::AppContext::GetInstance().languageManager.Text("ui_game_events_settings_event_revolts"        ) },
        { cst::HGameEventType::RENEGADE_SHIPS, app::AppContext::GetInstance().languageManager.Text("ui_game_events_settings_event_renegade_ships" ) },
        { cst::HGameEventType::BLACK_HOLE,     app::AppContext::GetInstance().languageManager.Text("ui_game_events_settings_event_black_hole"     ) },
        { cst::HGameEventType::SUPERNOVA,      app::AppContext::GetInstance().languageManager.Text("ui_game_events_settings_event_supernova"      ) },
        { cst::HGameEventType::ENGINE_PROBLEM, app::AppContext::GetInstance().languageManager.Text("ui_game_events_settings_event_engine_problems") },
             // clang-format on
            }
        };

        void Initialize(utl::usize focusID);

        void SetChecked(utl::usize index, bool isChecked);

    public:
        GameEventSettings(utl::usize focusID, Vector2 pos, Vector2 size, uil::Alignment alignment);

        void SetRandom();
    };
} // namespace ui
