//
// Purpur Tentakel
// 05.10.2022
//

#include "ColorPickerCell.hpp"
#include "ColorPicker.hpp"
#include <app/AppContext.hpp>
#include <helper/HFocusEvents.hpp>
#include <helper/HInput.hpp>
#include <utils/Colors.hpp>


namespace uil {
    void ColorPickerCell::SetColor() const {
        m_colorPicker->SetColor(m_color);
    }

    ColorPickerCell::ColorPickerCell(unsigned int const ID, Vector2 const pos, Vector2 const size, Alignment const alignment, Color const color, ColorPicker* const colorPicker)
	: UIElement{ pos, size, alignment },Focusable{ ID },
	m_color{ color }, m_colorPicker{ colorPicker },
	m_hover{
		0.05f,
          utl::Colors::AsString(color),
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

    void ColorPickerCell::SetEnabled(bool const enabled) {
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

    void ColorPickerCell::CheckAndUpdate(Vector2 const& mousePosition, app::AppContext_ty_c appContext) {

        UIElement::CheckAndUpdate(mousePosition, appContext);
        m_hover.CheckAndUpdate(mousePosition, appContext);

        if (!m_enabled) {
            return;
        }

        bool const renderHover{ CheckCollisionPointRec(mousePosition, m_collider) };
        if (renderHover) {
            m_hover.SetRenderHover(mousePosition, appContext);
        }

        bool const mouseClick{ renderHover && IsMouseButtonPressed(MOUSE_BUTTON_LEFT) };
        if (mouseClick) {
            m_colorPicker->SetCellFocuses(appContext);

            hlp::SelectFocusElement(this, m_colorPicker->IsPopUp());
        }

        bool const enterClick{ IsFocused() && hlp::IsConfirmInputPressed() };
        if (mouseClick or enterClick) {
            m_colorPicker->SetColor(m_color);
        }
    }


    void ColorPickerCell::Render(app::AppContext_ty_c) {
        if (!m_enabled) {
            return;
        }

        DrawRectanglePro(m_collider, Vector2(0.0f, 0.0f), 0.0f, m_color);

        DrawRectangleLinesEx(m_collider, 3.0f, m_color != PURPLE ? PURPLE : DARKPURPLE);
    }
} // namespace uil
