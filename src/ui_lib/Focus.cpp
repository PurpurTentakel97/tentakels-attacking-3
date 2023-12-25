//
// Purpur Tentakel
// 04.09.2022
//

#include "Focus.h"
#include "Focusable.h"
#include "AppContext.h"
#include "event/UIEvents.hpp"
#include "helper/HPrint.h"
#include <stdexcept>
#include <functional>

bool Focus::HasAnyEnabledElements() const {
	for (auto const& e : m_focus) {
		if (e->IsEnabled()) {
			return true;
		}
	}
	return false;
}

void Focus::UnfocusAllAtTopLayer() {
	for (auto& focus : m_focus) {
		focus->SetFocus(false);
	}

	m_currentFocus = nullptr;
}
Focusable_ty_raw Focus::GetFirstFocus() {
	Focusable_ty_raw firstFocus{ nullptr };
	bool const hasAnyEnabledElements{ HasAnyEnabledElements() };

	for (auto focus : m_focus) {
		if (hasAnyEnabledElements
			and !focus->IsEnabled()) {
				continue;
		}

		if (!firstFocus) {
			firstFocus = focus;
		}
		if (firstFocus->GetFocusID() > focus->GetFocusID()) {
			firstFocus = focus;
		}
	}

	return firstFocus;
}
Focusable_ty_raw Focus::GetLastFocus() {
	Focusable_ty_raw lastFocus{ nullptr };
	bool const hasAnyEnabledElements{ HasAnyEnabledElements() };

	for (auto focus : m_focus) {
		if (hasAnyEnabledElements
			and !focus->IsEnabled()) {
				continue;
		}
		if (!lastFocus) {
			lastFocus = focus;
			continue;
		}
		if (lastFocus->GetFocusID() < focus->GetFocusID()) {
			lastFocus = focus;
		}
	}

	return lastFocus;
}
Focusable_ty_raw Focus::GetNextFocus() {
	unsigned int const currentID{ m_currentFocus ? m_currentFocus->GetFocusID() : 0 };
	Focusable_ty_raw nextFocus{ nullptr };
	bool const hasAnyEnabledElements{ HasAnyEnabledElements() };

	for (auto focus : m_focus) {
		if (!focus) {
			throw 0;
		}
		if (hasAnyEnabledElements 
			and !focus->IsEnabled()) {
				continue;
		}
		if (focus->GetFocusID() > currentID) {
			if (!nextFocus) {
				nextFocus = focus;
				continue;
			}
			if (focus->GetFocusID() < nextFocus->GetFocusID()) {
				nextFocus = focus;
			}
		}
	}

	return nextFocus;
}
Focusable_ty_raw Focus::GetPreviousFocus() {
	unsigned int const currentID{ m_currentFocus ? m_currentFocus->GetFocusID()
		: static_cast<unsigned int>(m_focus.size()) };
	Focusable_ty_raw previousFocus{ nullptr };
	bool const hasAnyEnabledElements{ HasAnyEnabledElements() };

	for (auto focus : m_focus) {
		if (hasAnyEnabledElements
			and !focus->IsEnabled()) {
				continue;
		}
		if (focus->GetFocusID() < currentID) {
			if (!previousFocus) {
				previousFocus = focus;
				continue;
			}
			if (focus->GetFocusID() > previousFocus->GetFocusID()) {
				previousFocus = focus;
			}
		}
	}

	return previousFocus;
}
void Focus::SetInitialFocus() {
	m_currentFocus = GetFirstFocus();
	if (m_currentFocus) {
		m_currentFocus->SetFocus(true);
	}
}
void Focus::SetNextFocus() {
	m_currentFocus->SetFocus(false);

	Focusable_ty_raw nextFocus{ GetNextFocus() };
	if (!nextFocus) {
		nextFocus = GetFirstFocus();
	}

	m_currentFocus = nextFocus;
	m_currentFocus->SetFocus(true);
}
void Focus::SetPreviousFocus() {
	m_currentFocus->SetFocus(false);

	Focusable_ty_raw previousFocus{ GetPreviousFocus() };
	if (!previousFocus) {
		previousFocus = GetLastFocus();
	}

	m_currentFocus = previousFocus;
	m_currentFocus->SetFocus(true);
}
bool Focus::IsExistingFocus(Focusable_ty_raw focusable) {
	for (auto focus : m_focus) {
		if (focus == focusable) {
			return true;
		}
	}
	return false;
}

void Focus::SetSpecificFocus(Focusable_ty_raw focusable) {
	if (!IsExistingFocus(focusable)) { return; }

	if (m_currentFocus) {
		m_currentFocus->SetFocus(false);
	}
	m_currentFocus = focusable;
	m_currentFocus->SetFocus(true);
}
void Focus::SetSpecificNormalFocus(Focusable_ty_raw focusable) {
	if (m_PopUpLayerCounter == 0) {
		SetSpecificFocus(focusable);
	}
	else {
		m_toSelectRequest.AddElement(focusable);
	}
}
void Focus::SetSpecificPopUpFocus(Focusable_ty_raw focusable) {
	SetSpecificFocus(focusable);
}

void Focus::AddLayer() {
	m_lastFocus.push_back(m_currentFocus);
	m_focus.AddLayer();
	m_currentFocus = nullptr;
	m_renderFocus = false;
}
void Focus::AddNormalLayer() {
	if (m_PopUpLayerCounter == 0) {
		AddLayer();
	}
	else {
		m_addElementRequest.AddLayer();
		m_removeElementRequest.AddLayer();
		m_toSelectRequest.AddLayer();
		m_toAddOrDelete.push_back(true);
	}
}
void Focus::AddPopUpLayer() {
	AddLayer();
	++m_PopUpLayerCounter;
}
void Focus::DeleteLayer(bool setNewFocus) {
	for (auto f : m_focus) {
		f->SetFocus(false);
	}

	m_focus.RemoveLayer();

	if (!setNewFocus) {
		return;
	}

	if (m_lastFocus.size() > 0) {
		SetSpecificFocus(m_lastFocus.at(m_lastFocus.size() - 1));
		m_lastFocus.pop_back();
		m_renderFocus = false;
	}
}
void Focus::DeleteNormalLayer() {
	if (m_PopUpLayerCounter == 0) {
		DeleteLayer();
	}
	else {
		m_addElementRequest.AddLayer();
		m_removeElementRequest.AddLayer();
		m_toAddOrDelete.push_back(false);
	}
}
void Focus::DeletePopUpLayer() {
		DeleteLayer();
	--m_PopUpLayerCounter;
	if (m_PopUpLayerCounter == 0) {
		SetLayerAfterPopUp();
	}
}

void Focus::AddElement(Focusable_ty_raw focusable, bool setNewFocus) {
	CheckNewID(focusable->GetFocusID());
	m_focus.AddElement(focusable);

	if (!setNewFocus) {
		return;
	}

	if (m_currentFocus) {
		m_currentFocus->SetFocus(false);
	}
	SetInitialFocus();
}
void Focus::AddNormalElement(Focusable_ty_raw focusable) {
	if (m_PopUpLayerCounter == 0) {
		AddElement(focusable);
	}
	else {
		m_addElementRequest.AddElement(focusable);
	}
}
void Focus::AddPopUpElement(Focusable_ty_raw focusable) {
	AddElement(focusable);
}
void Focus::DeleteElement(Focusable_ty_raw focusable, bool setNextFocus) {
	m_focus.RemoveElement(focusable);

	if (!setNextFocus) {
		return;
	}

	if (m_currentFocus == focusable) {
		m_currentFocus = GetNextFocus();
	}
}
void Focus::DeleteNormalElement(Focusable_ty_raw focusable) {
	if (m_PopUpLayerCounter == 0) {
		DeleteElement(focusable);
	}
	else {
		m_removeElementRequest.AddElement(focusable);
	}
}
void Focus::DeletePopUpElement(Focusable_ty_raw focusable) {
	DeleteElement(focusable);
}

void Focus::SetLayerAfterPopUp() {

	while (true) {
		if (m_toAddOrDelete.size() == 0) {
			break;
		}

		if (m_toAddOrDelete.back()) {
			AddLayer();
		}
		else {
			DeleteLayer(false);
		}
		m_toAddOrDelete.pop_back();

		for (auto f : m_removeElementRequest) {
			if (f) {
				DeleteElement(f, false);
			}
		}
		m_removeElementRequest.RemoveLayer();

		for (auto f : m_addElementRequest) {
			if (f) {
				AddElement(f, false);
			}
		}
		m_addElementRequest.RemoveLayer();

		for (auto f : m_toSelectRequest) {
			if (f) {
				SetSpecificFocus(f);
			}
		}
		m_toSelectRequest.RemoveLayer();
	}

	for (auto f : m_removeElementRequest) {
		if (f) {
		DeleteElement(f, false);
		}
	}
	m_removeElementRequest.RemoveLayer();
	for (auto f : m_addElementRequest) {
		if (f) {
			AddElement(f, false);
		}
	}
	m_addElementRequest.RemoveLayer();

	for (auto f : m_toSelectRequest) {
		if (f) {
			SetSpecificFocus(f);
		}
	}
	m_toSelectRequest.RemoveLayer();
	
	m_toSelectRequest.Clear();
	m_addElementRequest.Clear();
	m_removeElementRequest.Clear();
	m_toAddOrDelete.clear();

	if (!m_currentFocus) {
		m_currentFocus = GetFirstFocus();
	}
}

void Focus::CheckNewID(unsigned int newID) {
	for (auto focus : m_focus) {
		if (focus->GetFocusID() == newID) {
			throw std::invalid_argument("ID already exists, ID: " + newID);
		}
	}
}

Focus::Focus() {
	AddLayer();
	AppContext_ty appContext{ AppContext::GetInstance() };
	appContext.eventManager.AddListener(this);

	Print(PrintType::INITIALIZE, "Focus");
}

void Focus::Clear() {
	m_focus.Clear();
	m_currentFocus = nullptr;

	m_addElementRequest.Clear();
	m_removeElementRequest.Clear();
	m_toSelectRequest.Clear();
	m_toAddOrDelete.clear();
	m_PopUpLayerCounter = 0;
}

void Focus::OnEvent(Event const& event) {
	if (auto const focusEvent =dynamic_cast<NewFocusElementEvent const*>(&event)) {
		AddNormalElement(focusEvent->GetFocusable());
		return;
	}
	if (auto const focusEvent = dynamic_cast<NewFocusPopUpElementEvent const*>(&event)) {
		AddPopUpElement(focusEvent->GetFocusable());
		return;
	}

	if (auto const focusEvent = dynamic_cast<DeleteFocusElementEvent const*>(&event)) {
		DeleteNormalElement(focusEvent->GetFocusable());
		return;
	}
	if (auto const focusEvent = dynamic_cast<DeleteFocusPopUpElementEvent const*>(&event)) {
		DeletePopUpElement(focusEvent->GetFocusable());
		return;
	}

	if (auto const focusEvent = dynamic_cast<SelectFocusElementEvent const*>(&event)) {
		SetSpecificNormalFocus(focusEvent->GetFocusable());
		return;
	}
	if (auto const focusEvent = dynamic_cast<SelectFocusPopUpElementEvent const*>(&event)) {
		SetSpecificPopUpFocus(focusEvent->GetFocusable());
		return;
	}
	if (auto const focusEvent = dynamic_cast<SelectNextFocusElementEvent const*>(&event)) {
		SetNextFocus();
		return;
	}

	if (auto const focusEvent = dynamic_cast<NewFocusLayerEvent const*>(&event)) {
		AddNormalLayer();
		return;
	}
	if (auto const focusEvent = dynamic_cast<NewFocusPopUpLayerEvent const*>(&event)) {
		AddPopUpLayer();
		return;
	}

	if (auto const focusEvent = dynamic_cast<DeleteFocusLayerEvent const*>(&event)) {
		DeleteNormalLayer();
		return;
	}
	if (auto const focusEvent = dynamic_cast<DeleteFocusPopUpLayerEvent const*>(&event)) {
		DeletePopUpLayer();
		return;
	}

	if (auto const focusEvent = dynamic_cast<ClearFocusEvent const*>(&event)) {
		Clear();
		return;
	}

	if (auto const focusEvent = dynamic_cast<RenderFocusEvent const*>(&event)) {
		m_renderFocus = focusEvent->GetRender();
		return;
	}
}

void Focus::CheckAndUpdate() {
	if (!m_currentFocus) {
		return;
	}

	if (IsKeyPressed(KEY_TAB)) {
		m_renderFocus = true;
		if (IsKeyDown(KEY_LEFT_SHIFT) or IsKeyDown(KEY_RIGHT_SHIFT)) {
			SetPreviousFocus();
			return;
		}
		SetNextFocus();
	}
}
void Focus::Render() {
	if (!m_currentFocus) { return; }
	if (!m_renderFocus) { return; }

	Rectangle const& f_colider{ m_currentFocus->GetCollider() };
	float const offset{ 5.0 };
	DrawRectangleLinesEx(
		Rectangle(
			static_cast<int>(f_colider.x) - offset,
			static_cast<int>(f_colider.y) - offset,
			static_cast<int>(f_colider.width) + 2.0f * offset,
			static_cast<int>(f_colider.height) + 2.0f * offset),
		offset,
		PURPLE
	);
}
