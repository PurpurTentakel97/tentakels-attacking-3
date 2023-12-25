//
// Purpur Tentakel
// 05.10.2022
//

#pragma once
#include "UIElement.hpp"
#include "Focusable.h"
#include "Hover.h"

class ColorPicker;

/**
 * provides the cell for the color picker.
 */
class ColorPickerCell final : public UIElement, public Focusable {
private:
	bool m_enabled{ true }; ///< contains if the cell is enabled
	Color m_color; ///< contains the color of the cell
	ColorPicker* m_colorPicker; ///< contains a pointer to the color picker it belongs to
	Hover m_hover; ///< contains the hover element

	/**
	 * calls the color picker to set the cell color as current color.
	 */
	void SetColor() const;

public:
	/**
	 * ctor.
	 * only initialize.
	 */
	ColorPickerCell(unsigned int ID, Vector2 pos, Vector2 size, Alignment alignment,
		Color color, ColorPicker* colorPicker);

	/**
	 * returns the current color.
	 */
	[[nodiscard]] Color GetColor() const;

	/**
	 * returns if the cell contains a current color.
	 */
	[[nodiscard]] bool IsBlankCell() const;
	/**
	 * sets if the current cell is enabled.
	 */
	void SetEnabled(bool enabled);
	/**
	 * returns if the current cell is enabled.
	 */
	[[nodiscard]] bool IsEnabled() const override;
	/**
	 * returns the current collider.
	 */
	[[nodiscard]] Rectangle GetCollider() const override;

	/**
	 * logic of the cell.
	 * triggers the color picker to update specific member functions
	 */
	void CheckAndUpdate(Vector2 const& mousePosition, AppContext_ty_c appContext) override;
	/**
	 * renders the cell.
	 */
	void Render(AppContext_ty_c appContext) override;
};
