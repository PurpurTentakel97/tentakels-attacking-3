//
// Purpur Tentakel
// 21.11.2022
//

#include "PopUpValidate.hpp"
#include <app/AppContext.hpp>
#include <event/EventGenerel.hpp>
#include <helper/HFocusEvents.hpp>
#include <helper/HInput.hpp>
#include <ui_lib/ButtonClassic.hpp>

void ValidatePopUp::Initialize() {

    app::AppContext_ty_c appContext{ app::AppContext::GetInstance() };

    auto acceptBtn = std::make_shared<ClassicButton>(
            2,
            hlp::GetElementPosition(m_pos, m_size, 0.33f, 0.9f),
            hlp::GetElementSize(m_size, 0.2f, 0.15f),
            Alignment::BOTTOM_MID,
            appContext.languageManager.Text("ui_validate_popup_accept_btn"),
            SoundType::ACCEPTED
    );
    acceptBtn->SetOnClick([this]() {
        this->m_callback(true);
        this->Close();
    });
    hlp::AddFocusElement(acceptBtn.get(), true);
    m_elements.push_back(acceptBtn);

    auto cancelBtn = std::make_shared<ClassicButton>(
            1,
            hlp::GetElementPosition(m_pos, m_size, 0.66f, 0.9f),
            hlp::GetElementSize(m_size, 0.2f, 0.15f),
            Alignment::BOTTOM_MID,
            appContext.languageManager.Text("ui_validate_popup_cancel_btn"),
            SoundType::CLICKED_RELEASE_STD
    );
    cancelBtn->SetOnClick([this]() {
        this->m_callback(false);
        this->Close();
    });
    hlp::AddFocusElement(cancelBtn.get(), true);
    hlp::SelectFocusElement(cancelBtn.get(), true);
    m_elements.push_back(cancelBtn);
}

void ValidatePopUp::Close() {
    m_shouldClose = true;
}

ValidatePopUp::ValidatePopUp(
        Vector2 const pos,
        Vector2 const size,
        Alignment const alignment,
        std::string const& title,
        std::string& subTitle,
        app::AssetType const infoTexture,
        std::function<void(bool)> callback
)
    : PopUp{ pos, size, alignment, title, subTitle, infoTexture },
      m_callback{ std::move(callback) } {

    Initialize();

    if (hlp::IsConfirmInputReleased()) {
        m_firstEnter = true;
    }
}

void ValidatePopUp::CheckAndUpdate(Vector2 const& mousePosition, app::AppContext_ty_c appContext) {
    if (!m_firstEnter) {
        PopUp::CheckAndUpdate(mousePosition, appContext);
    } else {
        LateUpdate();
    }
}
