//
// Purpur Tentakel
// 05.10.2022
//

#pragma once
#include "ColorPickerCell.h"
#include <vector>
#include <functional>
#include <memory>

/**
 * provides a Grid of colors to choose from.
 */
class ColorPicker final : public UIElement, public Focusable {
private:
	bool m_isPopUp{ }; ///< contains if the color picker was generated inside a popup

	size_t m_countX{ }; ///< contains the count of columns
	size_t m_countY{ }; ///< contains the count of rows
	std::vector<std::unique_ptr<ColorPickerCell>> m_cells{ }; ///< contains all current color cells
	ColorPickerCell* m_currentColorCell{ nullptr }; ///< contains the current color cell
	ColorPickerCell* m_previousColorCell{ nullptr }; ///< contains the previous color cell
	std::function<void()> m_onEnter{ []() {} }; ///< contains the lambda that is called if confirm input is pressed

	/**
	 * initializes the cells. 
	 */
	void Initialize();
	/**
	 * disables the cells if the colors are already used.
	 */
	void SetUsedColors(AppContext_ty_c appContext);
	/**
	 * retunes if not nested focus.
	 * sets the color that is in focus.
	 */
	void SetColorFromFocus();
	/**
	 * checks if the current color is valid.
	 * returns if its valid.
	 * calls a valid color via event.
	 */
	void CheckForValidColor(AppContext_ty_c appContext);

public:
	/**
	 * ctor.
	 * only initialisation.
 	 */
	ColorPicker(unsigned int ID, Vector2 pos, Vector2 size, Alignment alignment, bool isPopUp = false);
	/**
	 * deletes a focus layer if nested focus.
	 */
	~ColorPicker() override;

	/**
	 * returns the current color.
	 * if no current color it returns blank.
	 */
	[[nodiscard]] Color GetColor() const;
	/**
	 * returns if the current color has chanced since the last tick.
	 */
	[[nodiscard]] bool HasColorChanced() const;
	/**
	 * sets the first color.
	 * calls SetColor.
	 * return if the color was set.
	 */
	bool SetInitialColor(Color color);
	/**
	 * set a specific color if it exists in the color picker.
	 * returns if the color was set.
	 */
	bool SetColor(Color color);

	/**
	 * sets the onEnter lambda that get called if enter is pressed.
	 */
	void SetOnEnter(std::function<void()> onEnter);

	/**
	 * early return if already nested focus.
	 * add a focus layer.
	 * adds all cells as focus element.
	 */
	void SetCellFocuses(AppContext_ty_c appContext);
	/**
	 * sets if a specific color is enabled.
	 */
	void SetEnabled(bool enabled, Color color);
	/**
	 * returns true.
	 */
	[[nodiscard]] bool IsEnabled() const override;
	/**
	 * returns id the color picker was generated inside of an popup.
	 */
	[[nodiscard]] bool IsPopUp() const;

	/**
	 * logic of the color picker.
	 * calls all cells to update.
	 */
	void CheckAndUpdate(Vector2 const& mousePosition, AppContext_ty_c appContext) override;
	/**
	 * renders the color picker.
	 * calls all cells to render.
	 */
	void Render(AppContext_ty_c appContext) override;
	/**
	 * resizes the color picker.
	 * calls all cells to resize.
	 */
	void Resize(AppContext_ty_c appContext) override;

	/**
	 * returns the current collider.
	 */
	[[nodiscard]] Rectangle GetCollider() const override;
};
