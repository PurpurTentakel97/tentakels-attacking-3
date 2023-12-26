//
// Purpur Tentakel
// 10.09.2022
//

#include "AppContext.hpp"
#include "helper/HGeneral.hpp"
#include "include/ui/PopUpMessage.hpp"
#include <memory>

void MessagePopUp::Initialize() {
	AppContext_ty_c appContext{ AppContext::GetInstance() };

	auto btn = std::make_shared<ClassicButton>(
		1,
		GetElementPosition(m_pos, m_size,0.5f, 0.8f),
		GetElementSize(m_size,0.3f, 0.2f),
		Alignment::MID_MID,
		appContext.languageManager.Text("ui_message_popup_ok_btn"),
		SoundType::CLICKED_RELEASE_STD
		);

	btn->SetOnClick([this]() {
		this->m_callback();
		AppContext::GetInstance().eventManager.InvokeEvent(ClosePopUpEvent(this));
		});
	NewFocusPopUpElementEvent event{ btn.get() };
	appContext.eventManager.InvokeEvent(event);

	m_elements.push_back(btn);
}

MessagePopUp::MessagePopUp(Vector2 pos, Vector2 size, Alignment alignment,
	std::string const& title, std::string& subTitle, AssetType infoTexture, std::function<void()> callback)
	: PopUp{ pos, size, alignment, title, subTitle, infoTexture }, m_callback{ callback } {

	Initialize();
}

void MessagePopUp::CheckAndUpdate(Vector2 const& mousePosition,
	AppContext_ty_c appContext) {

	if (!m_firstEnter) {
		PopUp::CheckAndUpdate(mousePosition, appContext);
	}

	LateUpdate();
}
