//
// Purpur Tentakel
// 04.09.2022
//

#include "Focusable.hpp"
#include "AppContext.hpp"
#include "event/EventsUI.hpp"
#include "helper/HFocusEvents.hpp"
#include "helper/HPrint.hpp"

Focusable::Focusable(unsigned int ID)
	: m_focusID(ID) { }
Focusable::~Focusable() {
	DeleteFocusElement(this);
}

bool Focusable::IsFocused() const {
	return m_isFocus;
}
void Focusable::SetFocus(bool focus) {
	m_wasLastFocus = m_isFocus;
	m_isFocus = focus;
}
bool Focusable::GotFocused() const {
	return not m_wasLastFocus and m_isFocus;
}
bool Focusable::IsNestedFocus() const {
	return m_isNestedFocus;
}
void Focusable::SetNestedFocus(bool nestedFocus) {
	m_isNestedFocus = nestedFocus;
}
unsigned int Focusable::GetFocusID() const {
	return m_focusID;
}

void Focusable::SetFocusID(unsigned int focusID) noexcept {
	m_focusID = focusID;
}
