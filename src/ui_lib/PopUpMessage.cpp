//
// Purpur Tentakel
// 10.09.2022
//

#include "PopUpMessage.hpp"
#include <app/AppContext.hpp>
#include <helper/HGeneral.hpp>
#include <memory>


namespace uil {
    void MessagePopUp::Initialize() {
        app::AppContext_ty_c appContext{ app::AppContext::GetInstance() };

        auto btn = std::make_shared<ClassicButton>(1,
                                                   hlp::GetElementPosition(m_pos, m_size, 0.5f, 0.8f),
                                                   hlp::GetElementSize(m_size, 0.3f, 0.2f),
                                                   Alignment::MID_MID,
                                                   appContext.languageManager.Text("ui_message_popup_ok_btn"),
                                                   app::SoundType::CLICKED_RELEASE_STD);

        btn->SetOnClick([this]() {
            this->m_callback();
            app::AppContext::GetInstance().eventManager.InvokeEvent(eve::ClosePopUpEvent(this));
        });
        eve::NewFocusPopUpElementEvent event{ btn.get() };
        appContext.eventManager.InvokeEvent(event);

        m_elements.push_back(btn);
    }

    MessagePopUp::MessagePopUp(Vector2 const pos,
                               Vector2 const size,
                               Alignment const alignment,
                               std::string const& title,
                               std::string& subTitle,
                               app::AssetType const infoTexture,
                               callback_ty callback)
        : PopUp{ pos, size, alignment, title, subTitle, infoTexture },
          m_callback{ std::move(callback) } {

        Initialize();
    }

    void MessagePopUp::CheckAndUpdate(Vector2 const& mousePosition, app::AppContext_ty_c appContext) {

        if (!m_firstEnter) {
            PopUp::CheckAndUpdate(mousePosition, appContext);
        }

        LateUpdate();
    }
} // namespace uil
