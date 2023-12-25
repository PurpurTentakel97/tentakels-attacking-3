//
// Purpur Tentakel
// 23.10.2022
//

#pragma once
#include "UIElement.hpp"
#include "Focusable.h"
#include <functional>

/**
 * used to represent a checkable bool.
 */
class CheckBox final : public UIElement, public Focusable {
private:
	bool m_isEnabled{ true }; ///< contains if the checkbox is enabled
	bool m_isChecked{ false }; ///< contains if the checkbox id checked
	bool m_isHovered{ false }; ///< contains hover over the checkbox

	unsigned int m_ID; ///< contains the checkbox id -> used to return in onCheck

	Texture* m_texture; ///< contains the texture of the chop
	Rectangle m_textureRec; ///< contains the dimensions of the texture

	std::function<void(unsigned int, bool)> m_onCheck{ [](unsigned int, bool) {} }; ///< contains the lambda onCheck -> gets called when the state chances

	/**
	 * plays the sound and toggles the check state.
	 */
	void Check(AppContext_ty_c appContext);

public:
	/**
	 * ctor.
	 * recalculates the collider.
	 * handles the textures.
	 */
	CheckBox(unsigned int focusID, Vector2 pos, float height, Alignment alignment, unsigned int checkBoxID);

	/**
	 * sets the onCheck lambda that gets called when the checkbox gets checked.
	 */
	void SetOnCheck(std::function<void(unsigned int, bool)> onCheck);
	/**
	 * returns the ID if the checkbox.
	 */
	[[nodiscard]] unsigned int GetID() const;

	/**
	 * sets if the checkbox is checked.
	 */
	void SetChecked(bool isChecked);
	/**
	 * returns if the checkbox is checked.
	 */
	[[nodiscard]] bool IsChecked() const;

	/**
	 * sets the checkbox enabled.
	 */
	void SetEnabled(bool isEnabled);
	/**
	 * returns if the checkbox is enabled.
	 */
	[[nodiscard]] bool IsEnabled() const override;
	/**
	 * returns the current collider.
	 */
	[[nodiscard]] Rectangle GetCollider() const override;

	/**
	 * logic of the checkbox.
	 * 
	 */
	void CheckAndUpdate(Vector2 const& mousePosition, AppContext_ty_c appContext) override;
	/**
	 * renders the checkbox.
	 */
	void Render(AppContext_ty_c appContext) override;
	/**
	 * resizes the checkbox and calls the ui-element to resize.
	 * updates horizontal size.
	 */
	void Resize(AppContext_ty_c appContext) override;
};
