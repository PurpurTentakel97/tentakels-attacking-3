//
// Purpur Tentakel
// 14.11.2022
//

#include "SoundLevelPopUp.h"
#include "AppContext.h"
#include "helper/HFocusEvents.h"
#include "helper/HGeneral.h"
#include "ui_lib/CheckBox.h"
#include "ui_lib/ClassicButton.h"
#include "ui_lib/Slider.h"
#include "ui_lib/Text.h"

void SoundLevelPopUp::Initialize() {
    AppContext_ty_c appContext = AppContext::GetInstance();

    m_slider = std::make_shared<Slider>(
            GetElementPosition(m_pos, m_size, 0.5f, 0.65f),
            GetElementSize(m_size, 0.7f, 0.1f),
            Alignment::BOTTOM_MID,
            true,
            10.0f
    );
    m_slider->SetEnabled(!appContext.constants.sound.muteVolume);
    m_slider->SetButtonPosition(appContext.constants.sound.masterVolume);
    m_slider->SetOnSlide([this](float position) {
        AppContext::GetInstance().eventManager.InvokeEvent(SetMasterVolumeEvent(position));
    });
    m_elements.push_back(m_slider);

    m_checkBox = std::make_shared<CheckBox>(
            4,
            GetElementPosition(m_pos, m_size, 0.15f, 0.66f),
            GetElementSize(m_size, 0.0f, 0.04f).y,
            Alignment::TOP_LEFT,
            1
    );
    m_checkBox->SetChecked(appContext.constants.sound.muteVolume);
    m_checkBox->SetOnCheck([this](unsigned int, bool isChecked) {
        AppContext_ty appContext = AppContext::GetInstance();
        auto event = MuteMasterVolumeEvent(isChecked);
        appContext.eventManager.InvokeEvent(event);
        m_slider->SetEnabled(!isChecked);
    });
    AddFocusElement(m_checkBox.get(), true);
    m_elements.push_back(m_checkBox);

    m_elements.push_back(std::make_shared<Text>(
            GetElementPosition(m_pos, m_size, 0.18f, 0.655f),
            GetElementSize(m_size, 0.2f, 0.3f),
            Alignment::TOP_LEFT,
            Alignment::TOP_LEFT,
            0.025f,
            appContext.languageManager.Text("ui_sound_level_popup_mute")
    ));

    m_acceptBtn = std::make_shared<ClassicButton>(
            1,
            GetElementPosition(m_pos, m_size, 0.5f, 0.95f),
            GetElementSize(m_size, 0.2f, 0.15f),
            Alignment::BOTTOM_MID,
            appContext.languageManager.Text("ui_sound_level_popup_accept_btn"),
            SoundType::ACCEPTED
    );
    m_acceptBtn->SetOnClick([this]() { AppContext::GetInstance().eventManager.InvokeEvent(ClosePopUpEvent(this)); });
    AddFocusElement(m_acceptBtn.get(), true);
    SelectFocusElement(m_acceptBtn.get(), true);
    m_elements.push_back(m_acceptBtn);
}

SoundLevelPopUp::SoundLevelPopUp(
        Vector2 pos,
        Vector2 size,
        Alignment alignment,
        std::string const& title,
        std::string& subTitle
)
    : PopUp{ pos, size, alignment, title, subTitle, AssetType::QUESTION_MARK } {

    Initialize();
}

void SoundLevelPopUp::Render(AppContext_ty_c appContext) {

    PopUp::Render(appContext);

    DrawRectangleLinesEx(m_slider->GetCollider(), 2.0f, WHITE);
}
