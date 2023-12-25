//
// Purpur Tentakel
// 05.10.2022
//

#include "ColorPickerCell.h"
#include "ColorPicker.h"
#include "AppContext.h"
#include "helper/HFocusEvents.h"
#include "helper/HInput.h"
#include <iostream>

void ColorPickerCell::SetColor() const {
	m_colorPicker->SetColor(m_color);
}

ColorPickerCell::ColorPickerCell(unsigned int ID, Vector2 pos, Vector2 size, Alignment alignment, Color color, ColorPicker* colorPicker)
	: UIElement{ pos, size, alignment },Focusable{ ID },
	m_color{ color }, m_colorPicker{ colorPicker },
	m_hover{
		0.05f,
		AppContext::GetInstance().colors.AsString(color),
		WHITE,
		{0.01f,0.01f}
	}
		{

	if (IsBlankCell()) {
		m_enabled = false;
	}
}

Color ColorPickerCell::GetColor() const {
	return m_color;
}

bool ColorPickerCell::IsBlankCell() const {
	return m_color == BLANK;
}
void ColorPickerCell::SetEnabled(bool enabled) {
	if (IsBlankCell()) {
		m_enabled = false;
		return;
	}
	m_enabled = enabled;
}
bool ColorPickerCell::IsEnabled() const {
	return m_enabled;
}
Rectangle ColorPickerCell::GetCollider() const {
	return UIElement::GetCollider();
}

void ColorPickerCell::CheckAndUpdate(Vector2 const& mousePosition,
	AppContext_ty_c appContext) {

	UIElement::CheckAndUpdate(mousePosition, appContext);
	m_hover.CheckAndUpdate(mousePosition, appContext);

	if (!m_enabled) {
		return;
	}

	bool const renderHover{ CheckCollisionPointRec(mousePosition, m_collider) };
	if (renderHover) {
		m_hover.SetRenderHover(mousePosition, appContext);
	}

	bool const mouseClick{
		renderHover
		&& IsMouseButtonPressed(MOUSE_BUTTON_LEFT) 
	};
	if (mouseClick) {
		m_colorPicker->SetCellFocuses(appContext);

		SelectFocusElement(this, m_colorPicker->IsPopUp());
	}

	bool const enterClick{
		IsFocused()
		&& IsConfirmInputPressed() 
	};
	if (mouseClick or enterClick) {
		m_colorPicker->SetColor(m_color);
	}
}
void ColorPickerCell::Render([[maybe_unused]] AppContext_ty_c appContext) {
	if (!m_enabled) {
		return;
	}

	DrawRectanglePro(
		m_collider,
		Vector2(0.0f, 0.0f),
		0.0f,
		m_color
	);

	DrawRectangleLinesEx(
		m_collider,
		3.0f,
		m_color != PURPLE ? PURPLE : DARKPURPLE
	);
}
