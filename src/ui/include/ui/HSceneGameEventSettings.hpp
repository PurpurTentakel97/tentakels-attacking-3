//
// Purpur Tentakel
// 24.10.2022
//

#pragma once
#include "AppContext.hpp"
#include "helper/HGameEventTypes.hpp"
#include "ui_lib/Scene.h"

/**
 * provides a scene where the game events can be set.
 */
class GameEventSettings : public Scene {
private:
	std::vector<CheckBox_ty> m_checkBoxes; ///< contains all check boxes

	std::array<std::pair<HGameEventType, std::string>, 7> m_text{{
		{ HGameEventType::GLOBAL,         AppContext::GetInstance().languageManager.Text("ui_game_events_settings_event_all")             },
		{ HGameEventType::PIRATES,        AppContext::GetInstance().languageManager.Text("ui_game_events_settings_event_pirates")         },
		{ HGameEventType::REVOLTS,        AppContext::GetInstance().languageManager.Text("ui_game_events_settings_event_revolts")         },
		{ HGameEventType::RENEGADE_SHIPS, AppContext::GetInstance().languageManager.Text("ui_game_events_settings_event_renegade_ships")  },
		{ HGameEventType::BLACK_HOLE,     AppContext::GetInstance().languageManager.Text("ui_game_events_settings_event_black_hole")      },
		{ HGameEventType::SUPERNOVA,      AppContext::GetInstance().languageManager.Text("ui_game_events_settings_event_supernova")       },
		{ HGameEventType::ENGINE_PROBLEM, AppContext::GetInstance().languageManager.Text("ui_game_events_settings_event_engine_problems") }
	}};

	/**
	 * initializes all ui elements.
	 * connects the actions.
	 */
	void Initialize(unsigned int focusID);

	/**
	 * sets the checkbox checkt with the provided id via event.
	 */
	void SetChecked(unsigned int index, bool isCecked);


public:
	/**
	 * ctor.
	 * add an event listener.
	 * triggers logic to send the initial data via event.
 	 */
	GameEventSettings(unsigned int focusID, Vector2 pos, Vector2 size, Alignment alignment);

	/**
	 * sets random values for every checkbox except for the global checkbox.
	 * calls global checkbox to set.
	 */
	void SetRandom();
};
