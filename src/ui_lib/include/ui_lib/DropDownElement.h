//
// Purpur Tentakel
// 01.12.2022
//

#pragma once
#include "UIElement.hpp"
#include "Focusable.h"
#include <functional>

class DropDownElement : public UIElement, public Focusable {
private:
	bool m_isEnabled{ true }; ///< contains if the element is currently enabled
	bool m_hover{ false }; ///< contains if the mouse if currently hovering over the element
	unsigned int m_ID; ///< contains the unique element ID
	float m_fontSize; ///< contains the font height
	std::string m_toRender; ///< contains the string that gets rendered
	std::string m_text; ///< contains the raw string
	Vector2 m_textPosition; ///< contains the position the text gets rendered at
	std::function<void(unsigned int)> m_onClick{ [](unsigned int) {} }; ///< contains the action that gets called on click or enter
	std::function<Rectangle(Rectangle)> m_getTemporaryCollider;

	/**
	 * generates the toRender string out of the raw string.
	 */
	void CreateToRender();

	/**
	 * calls UpdateCollider of the UIElement.
	 * Updates the text.
	 */
	void UpdateCollider() override;
	/**
	 * calls UpdateReverseCollider of the UIElement.
	 * Updates the text.
	 */
	void UpdateColliderReverse() override;

public:
	/**
	 * ctor.
	 * create toRender.
	 */
	DropDownElement(Vector2 pos, Vector2 size, Alignment alignment,
		unsigned int focusID, unsigned int ID, std::string const& text, std::function<Rectangle(Rectangle)> getTemoraryCollider);

	/**
	 * calls the CheckAndUpdate member function of the UIElement.
	 * contains the element logic.
	 */
	void CheckAndUpdate(Vector2 const&, AppContext_ty_c) override;
	/**
	 * renders the element.
	 */
	void Render(AppContext_ty_c appContext) override;

	/**
	 * returns if the element is currently enabled.
	 */
	[[nodiscard]] bool IsEnabled() const override;
	/**
	 * sets if the element is currently enabled.
	 */
	void SetEnabled(bool isEnabled);

	/**
	 * sets the current text of the element.
	 */
	void SetText(std::string text);
	/**
	 * returns the current entry text.
	 */
	[[nodiscard]] std::string GetText() const;

	/**
	 * returns the ID of the Entry.
	 */
	[[nodiscard]] unsigned int GetID() const;

	/**
	 * sets the lambda that gets called on click or enter.
	 * provides the ID of the clicked element.
	 */
	void SetOnClick(std::function<void(unsigned int)> onClick);

	/**
	 * returns the element collider.
	 */
	[[nodiscard]] Rectangle GetCollider() const override;
};
