//
// Purpur Tentakel
// 03.04.2023
//

#include "Focusable.h"
#include "UIElement.hpp"
#include <any>
#pragma once

class AbstractTableCell : public UIElement, public Focusable {
protected:
	bool m_isEditable{ true }; ///< contains if the cell is currently editable
	Color m_backgroundColor{ BLACK }; ///< contains the background of the cell
	float m_textSize; ///< contains the text size the text is rendered with
	Vector2 m_textPosition; ///< contains the absolute text position 
	Color m_textColor{ WHITE }; ///< contains the color a text is redered with

public:
	/**
	 * ctor.
	 * initializes the table with empty cells.
	 */
	AbstractTableCell(Vector2 pos, Vector2 size, Alignment alignment, unsigned int focusID);

	/**
	 * calculates the text size.
	 * need to be implemented in every cell.
	 */
	virtual void CalculateTextSize() = 0;

	/**
	 * returns the current value.
	 */
	[[nodiscard]] virtual std::any GetValue() const = 0;
	/**
	 * returns the current value as string.
	 */
	[[nodiscard]] virtual std::string GetValueAsString() const = 0;

	/**
	 * sets the background color.
	 */
	void SetBackgroundColor(Color color);
	/**
	 * returns the current background color.
	 */
	[[nodiscard]] Color GetBackgroundColor() const;

	/**
	 * sets if the cell is editable.
	 */
	void SetEditable(bool IsEditable) noexcept;
	/**
	 * returns true if the cell is editable.
	 */
	[[nodiscard]] bool IsEditable() const noexcept;

	/**
	 * returns if the current elements is enabled.
	 */
	[[nodiscard]] bool IsEnabled() const noexcept override;
	/**
	 * returns thr current collider.
	 */
	[[nodiscard]] Rectangle GetCollider() const noexcept override;

	/**
	 * returns if the point in inside the cell collider.
	 */
	[[nodiscard]] bool IsColliding(Vector2 point) const;

	/**
	 * sets the render color for text. color cells will ignore this
	 */
	void SetTextColor(Color color);
	/**
	 * returns the current text color.
	 */
	[[nodiscard]] Color GetTextColor() const;

	/**
	 * use this if the cell is clicked.
	 * need to be implemented by every cell.
	 */
	virtual void Clicked(Vector2 const&, AppContext_ty_c) = 0;
	/**
	 * calls the CheckAndUpdate member function of UIElement.
	 * contains the logic of the cell.
	 */
	virtual void CheckAndUpdate(Vector2 const&, AppContext_ty_c) override = 0;
	/**
	 * renders the cell
	 */
	virtual void Render(AppContext_ty_c appContext) override;
};
