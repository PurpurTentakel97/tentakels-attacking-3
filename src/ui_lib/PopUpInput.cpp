//
// Purpur Tentakel
// 04.10.2022
//

#include "PopUpInput.hpp"
#include <app/AppContext.hpp>
#include <helper/HFocusEvents.hpp>
#include <helper/HGeneral.hpp>
#include <helper/HInput.hpp>

namespace uil {
    namespace {
        // Need for PopUp ctor
        std::string subTitle{};
    } // namespace

    void PopUpInput::Initialize() {

        app::AppContext_ty_c appContext{ app::AppContext::GetInstance() };

        auto cancelBtn = std::make_shared<ClassicButton>(2,
                hlp::GetElementPosition(m_pos, m_size, 0.1f, 0.95f),
                hlp::GetElementSize(m_size, 0.3f, 0.2f),
                                                         Alignment::BOTTOM_LEFT,
                                                         appContext.languageManager.Text("ui_cell_popup_cancel_btn"),
                app::SoundType::CLICKED_RELEASE_STD
        );

        hlp::AddFocusElement(cancelBtn.get(), true);

        cancelBtn->SetOnClick([this]() { this->SetShouldClose(); });

        m_elements.push_back(cancelBtn);
    }

    ClassicButton_ty PopUpInput::InitializeAcceptButton() {

        app::AppContext_ty_c appContext{ app::AppContext::GetInstance() };

        auto acceptBtn = std::make_shared<ClassicButton>(1,
                hlp::GetElementPosition(m_pos, m_size, 0.9f, 0.95f),
                hlp::GetElementSize(m_size, 0.3f, 0.2f),
                                                         Alignment::BOTTOM_RIGHT,
                                                         appContext.languageManager.Text("ui_cell_popup_accept_btn"),
                app::SoundType::ACCEPTED
        );

        hlp::AddFocusElement(acceptBtn.get(), true);

        m_elements.push_back(acceptBtn);

        return acceptBtn;
    }

    void PopUpInput::SetShouldClose() {
        m_shouldClose = true;
    }

    void PopUpInput::CheckEnter() {
        bool validEnterClose =
                (IsKeyReleased(KEY_ENTER) or IsKeyPressed(KEY_KP_ENTER)) && !m_shouldClose && !m_firstEnter;
        if (validEnterClose) {
            auto event = eve::PlaySoundEvent(app::SoundType::ACCEPTED);
            app::AppContext::GetInstance().eventManager.InvokeEvent(event);
            SetValue();
        }

        LateUpdate();
    }

    void PopUpInput::Close(app::AppContext_ty_c appContext) {
        if (m_shouldClose) {
            auto event = eve::ClosePopUpEvent(this);
            appContext.eventManager.InvokeEvent(event);
        }
    }

    PopUpInput::PopUpInput(Vector2 const pos,
            Vector2 const size,
                           Alignment const alignment,
                           std::string const& title,
            app::AssetType const infoTexture
    )
        : PopUp{ pos, size, alignment, title, subTitle, infoTexture } {

        Initialize();
    }

    void PopUpInput::CheckAndUpdate(Vector2 const& mousePosition, app::AppContext_ty_c appContext) {

        PopUp::CheckAndUpdate(mousePosition, appContext);

        CheckEnter();

        if (hlp::IsBackInputPressed()) {
            eve::PlaySoundEvent event{ app::SoundType::CLICKED_RELEASE_STD };
            appContext.eventManager.InvokeEvent(event);
            SetShouldClose();
        }

        Close(appContext);
    }
} // namespace ui
