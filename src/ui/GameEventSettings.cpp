//
// Purpur Tentakel
// 24.10.2022
//

#include "GameEventSettings.h"
#include "helper/HRandom.h"
#include "ui_lib/CheckBox.h"
#include "ui_lib/Line.h"
#include "ui_lib/Text.h"
#include <array>
#include <cassert>
#include <utility>


void GameEventSettings::Initialize(unsigned int focusID) {

    AppContext_ty_c appContext{ AppContext::GetInstance() };

    // Title
    auto title = std::make_shared<Text>(
            GetElementPosition(0.5f, 0.0f),
            GetElementSize(0.8f, 0.2f),
            Alignment::TOP_MID,
            Alignment::TOP_MID,
            0.07f,
            appContext.languageManager.Text("ui_game_event_settings_title")
    );
    // title->RenderRectangle(true);
    m_elements.push_back(title);

    // Line
    m_elements.push_back(
            std::make_shared<Line>(GetElementPosition(0.3f, 0.15f), GetElementPosition(0.7f, 0.15f), 3.0f, WHITE)
    );

    // Text and Check Box
    float const firstRow{ 0.25f };
    float const row{ 0.035f };
    float const cbX{ 0.51f };
    float const textX{ 0.49f };


    for (size_t i = 0; i < m_text.size(); ++i) {
        auto displayText = std::make_shared<Text>(
                GetElementPosition(textX, firstRow + row * static_cast<float>(i) * 2),
                GetElementSize(textX + 0.15f, row * 3),
                Alignment::MID_RIGHT,
                Alignment::MID_RIGHT,
                row,
                m_text.at(i).second
        );
        // displayText->RenderRectangle(true);
        m_elements.push_back(displayText);

        auto element = std::make_shared<CheckBox>(
                i + focusID,
                GetElementPosition(cbX, firstRow + row * static_cast<float>(i) * 2),
                GetElementSize(0.0f, row * 1.5f).y,
                Alignment::MID_LEFT,
                i
        );
        element->SetOnCheck([this](unsigned int index, bool isChecked) { this->SetChecked(index, isChecked); });
        element->SetChecked(appContext.constants.gameEvents.IsFlag(m_text.at(i).first));
        m_checkBoxes.push_back(element);
        m_elements.push_back(element);
    }
}

void GameEventSettings::SetChecked(unsigned int index, bool isChecked) {
    AppContext_ty appContext{ AppContext::GetInstance() };
    appContext.constants.gameEvents.SetFlag(m_text.at(index).first, isChecked);

    assert(m_checkBoxes.size() == m_text.size());

    for (size_t i = 0; i < m_checkBoxes.size(); ++i) {
        m_checkBoxes.at(i)->SetChecked(appContext.constants.gameEvents.IsFlag(m_text.at(i).first));
    }
}

GameEventSettings::GameEventSettings(unsigned int focusID, Vector2 pos, Vector2 size, Alignment alignment)
    : Scene{ pos, size, alignment } {

    Initialize(focusID);
}


void GameEventSettings::SetRandom() {
    Random& random{ Random::GetInstance() };
    AppContext_ty appContext{ AppContext::GetInstance() };

    assert(m_checkBoxes.size() == m_text.size());

    for (size_t i = 1; i < m_checkBoxes.size(); ++i) { // 0 is the global checkbox
        bool r = random.random(2) == 1;
        appContext.constants.gameEvents.SetFlag(m_text.at(i).first, r);
        m_checkBoxes.at(i)->SetChecked(appContext.constants.gameEvents.IsFlag(m_text.at(i).first));
    }
    m_checkBoxes.at(0)->SetChecked(appContext.constants.gameEvents.IsFlag(HGameEventType::GLOBAL));
}
