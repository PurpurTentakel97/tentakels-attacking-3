//
// Purpur Tentakel
// 04.10.2022
//

#include "include/ui/CellPopUp.h"
#include "AppContext.hpp"
#include "helper/HFocusEvents.h"
#include "helper/HGeneral.h"
#include "helper/HInput.h"

namespace {
	// Need for PopUp ctor
	std::string subTitle{ "" };
}

void CellPopUp::Initialize() {

	AppContext_ty_c appContext{ AppContext::GetInstance() };

	auto cancelBtn = std::make_shared<ClassicButton>(
		2,
		GetElementPosition(m_pos, m_size, 0.1f, 0.95f),
		GetElementSize(m_size, 0.3f, 0.2f),
		Alignment::BOTTOM_LEFT,
		appContext.languageManager.Text("ui_cell_popup_cancel_btn"),
		SoundType::CLICKED_RELEASE_STD
		);

	AddFocusElement(cancelBtn.get(), true);

	cancelBtn->SetOnClick([this]() {
		this->SetShouldClose();
		});

	m_elements.push_back(cancelBtn);
}
ClassicButton_ty CellPopUp::InitializeAcceptButton() {

	AppContext_ty_c appContext{ AppContext::GetInstance() };

	auto acceptBtn = std::make_shared<ClassicButton>(
		1,
		GetElementPosition(m_pos, m_size, 0.9f, 0.95f),
		GetElementSize(m_size, 0.3f, 0.2f),
		Alignment::BOTTOM_RIGHT,
		appContext.languageManager.Text("ui_cell_popup_accept_btn"),
		SoundType::ACCEPTED
		);

	AddFocusElement(acceptBtn.get(), true);

	m_elements.push_back(acceptBtn);

	return acceptBtn;
}

void CellPopUp::SetShouldClose() {
	m_shouldClose = true;
}

void CellPopUp::CheckEnter() {
	bool validEnterClose =
		(IsKeyReleased(KEY_ENTER)
			or IsKeyPressed(KEY_KP_ENTER))
		&& !m_shouldClose
		&& !m_firstEnter;
	if (validEnterClose) {
		auto event = PlaySoundEvent(SoundType::ACCEPTED);
		AppContext::GetInstance().eventManager.InvokeEvent(event);
		SetValue();
	}

	LateUpdate();
}

void CellPopUp::Close(AppContext_ty_c appContext) {
	if (m_shouldClose) {
		auto event = ClosePopUpEvent(this);
		appContext.eventManager.InvokeEvent(event);
	}
}

CellPopUp::CellPopUp(Vector2 pos, Vector2 size, Alignment alignment,
	std::string const& title, AssetType infoTexture)
	: PopUp{ pos, size, alignment, title, subTitle, infoTexture } {
	
	Initialize();
}

void CellPopUp::CheckAndUpdate(Vector2 const& mousePosition,
	AppContext_ty_c appContext) {

	PopUp::CheckAndUpdate(mousePosition, appContext);

	CheckEnter();

	if (IsBackInputPressed()) {
		PlaySoundEvent event{ SoundType::CLICKED_RELEASE_STD };
		appContext.eventManager.InvokeEvent(event);
		SetShouldClose();
	}

	Close(appContext);
}
