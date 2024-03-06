//
// Purpur Tentakel
// 14.11.2022
//

#include "PopUpSoundLevel.hpp"
#include <app/AppContext.hpp>
#include <helper/HFocusEvents.hpp>
#include <helper/HGeneral.hpp>
#include <ui_lib/ButtonClassic.hpp>
#include <ui_lib/CheckBox.hpp>
#include <ui_lib/Slider.hpp>
#include <ui_lib/Text.hpp>


namespace ui {
    void SoundLevelPopUp::Initialize() {
        app::AppContext_ty_c appContext = app::AppContext::GetInstance();

        m_slider = std::make_shared<uil::Slider>(
                hlp::GetElementPosition(m_pos, m_size, 0.5f, 0.65f),
                hlp::GetElementSize(m_size, 0.7f, 0.1f),
                uil::Alignment::BOTTOM_MID,
                true,
                10.0f
        );
        m_slider->SetEnabled(!appContext.constants.g_sound.get_is_mute());
        m_slider->SetButtonPosition(appContext.constants.g_sound.get_master_volume());
        m_slider->SetOnSlide([](float position) {
            app::AppContext::GetInstance().eventManager.InvokeEvent(eve::SetMasterVolumeEvent(position));
        });
        m_elements.push_back(m_slider);

        m_checkBox = std::make_shared<uil::CheckBox>(
                4,
                hlp::GetElementPosition(m_pos, m_size, 0.15f, 0.66f),
                hlp::GetElementSize(m_size, 0.0f, 0.04f).y,
                uil::Alignment::TOP_LEFT,
                1
        );
        m_checkBox->SetChecked(appContext.constants.g_sound.get_is_mute());
        m_checkBox->SetOnCheck([this](utl::usize, bool isChecked) {
            auto event = eve::MuteMasterVolumeEvent(isChecked);
            app::AppContext::GetInstance().eventManager.InvokeEvent(event);
            m_slider->SetEnabled(!isChecked);
        });
        hlp::AddFocusElement(m_checkBox.get(), true);
        m_elements.push_back(m_checkBox);

        m_elements.push_back(std::make_shared<uil::Text>(
                hlp::GetElementPosition(m_pos, m_size, 0.18f, 0.655f),
                hlp::GetElementSize(m_size, 0.2f, 0.3f),
                uil::Alignment::TOP_LEFT,
                uil::Alignment::TOP_LEFT,
                0.025f,
                appContext.languageManager.Text("ui_sound_level_popup_mute")
        ));

        m_acceptBtn = std::make_shared<uil::ClassicButton>(
                1,
                hlp::GetElementPosition(m_pos, m_size, 0.5f, 0.95f),
                hlp::GetElementSize(m_size, 0.2f, 0.15f),
                uil::Alignment::BOTTOM_MID,
                appContext.languageManager.Text("ui_sound_level_popup_accept_btn"),
                app::SoundType::ACCEPTED
        );
        m_acceptBtn->SetOnClick([this]() {
            app::AppContext::GetInstance().eventManager.InvokeEvent(eve::ClosePopUpEvent(this));
        });
        hlp::AddFocusElement(m_acceptBtn.get(), true);
        hlp::SelectFocusElement(m_acceptBtn.get(), true);
        m_elements.push_back(m_acceptBtn);
    }

    SoundLevelPopUp::SoundLevelPopUp(
            Vector2 const pos,
            Vector2 const size,
            uil::Alignment const alignment,
            std::string const& title,
            std::string& subTitle
    )
        : PopUp{ pos, size, alignment, title, subTitle, app::AssetType::QUESTION_MARK } {

        Initialize();
    }

    void SoundLevelPopUp::Render(app::AppContext_ty_c appContext) {

        PopUp::Render(appContext);

        DrawRectangleLinesEx(m_slider->GetCollider(), 2.0f, WHITE);
    }
} // namespace ui
