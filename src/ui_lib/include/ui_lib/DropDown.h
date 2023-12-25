//
// Purpur Tentakel
// 01.12.2022
//

#pragma once
#include "UIElement.hpp"
#include "Focusable.h"
#include <memory>
#include <vector>
#include <functional>

class DropDownElement;

class DropDown : public UIElement, public Focusable {
private:
	bool m_isEnabled{ true }; ///< contains if the element is currently enabled
	bool m_isFoldouts{ false }; ///< contains if the element is currents folded out
	bool m_isScrolling{ true }; ///< contains if the DropDown in able to scroll
	std::vector<std::shared_ptr<DropDownElement>> m_dropDownElements; ///< contains all elements in the drop down

	Texture const* m_arrowTexture; ///< contains the texture of the arrow that controls if the menu is dropped down
	Rectangle m_arrowTextureRec; ///< contains the dimensions onto the texture
	Rectangle m_arrowCollider; ///< contains the absolute dimensions of the arrow

	std::shared_ptr<DropDownElement> m_currentElement{ nullptr }; ///< contains the current element
	std::string m_currentElementText{ "" }; ///< contains the text of the current element
	float m_fontSize{ 0.0f }; ///< contains the height of the text of the current element
	Vector2 m_textPosition{ 0.0f,0.0f }; ///< contains the position of the current element

	float m_dropDownHeight; ///< contains the relative height of the drop down part
	Rectangle m_dropDownCollider; ///< contains the collider of the drop down part
	std::function<void(unsigned int)> m_onSave{ [](unsigned int) {} }; ///< gets called of save

	/**
	 * initializes all ui elements.
	 * context the on click.
	 */
	void Initialize(std::vector<std::string> const& elements, unsigned int startFocusID);
	/**
	 * gets called of the elements as on click action.
	 */
	void OnElementClick(unsigned int ID);

	/**
	 * sets the current element and current element text.
	 */
	void SetCurrentElement(std::shared_ptr<DropDownElement> element);
	void SetCurrentElementOutUpdate(std::shared_ptr<DropDownElement> element);

	/**
	 * sets the current text
	 */
	void SetText();

	/**
	 * toggles the drop down menu.
	 */
	void ToggleFoldedOut();

	/**
	 * calculates a collider that represents the area where the provided collider
	 * overlaps with the drop down collider.
	 * returns the temporary collider.
	 */
	[[nodiscard]] Rectangle GetTemporaryCollider(Rectangle collider) const;

	/**
	 * checks if the elements in overlapping with the drop down collider.
	 * sets the element active if so.
	 * sets it inactive if not.
	 */
	void CheckAndSetElementsEnabled();

	/**
	 * scrolls the entries an sets new focused entry if necessary.
	 * the movement value gets multiplied ba the wheel value.
	 */
	void ScrollMove(float wheel);
	/**
	 * clamps the first and last value into the drop down collider.
	 */
	void ClampScrolling();
	/**
	 * Checks if scrolling should be enabled.
	 */
	void CheckIfScrolling();

	/**
	 * calls UpdateCollider from UIElement.
	 * sets a new position of the arrow and the current element text.
	 */
	void UpdateCollider() override;

public:
	/**
	 * ctor.
	 * only initialization.
	 */
	DropDown(Vector2 pos, Vector2 size, Alignment alignment, 
		float dropDownSize, unsigned int focusID, unsigned int startElementFocusID, std::vector<std::string> const& elements);


	/**
	 * returns the current element.
	 */
	[[nodiscard]] std::shared_ptr<DropDownElement> GetCurrentElement() const;
	/**
	 * sets the element of the provided ID as current element.
	 * returns if the element was set.
	 */
	bool SetCurrentElementByID(unsigned int ID);
	/**
	 * sets the element of the provided string as current element.
	 * returns if the element was set.
	 */
	bool SetCurrentElementByString(std::string const& element);


	/**
	 * calls the CheckAndUpdate of the UIElement.
	 * contains the DropDown logic.
	 */
	void CheckAndUpdate(Vector2 const&, AppContext_ty_c) override;
	/**
	 * renders the DropDown.
	 */
	void Render(AppContext_ty_c appContext) override;
	/**
	 * resizes itself and alle elements it contains.
	 */
	void Resize(AppContext_ty_c appContext) override;

	/**
	 * returns if the element is currently enabled.
	 */
	[[nodiscard]] bool IsEnabled() const override;
	/**
	 * sets if the element is currently enabled.
	 */
	void SetEnabled(bool isEnabled);
	/**
	 * returns if the drop down is folded out.
	 */
	[[nodiscard]] bool IsFoldedOut() const;

	/**
	 * returns the current collider of the element.
	 */
	[[nodiscard]] Rectangle GetCollider() const override;

	/**
	 * sets the lambda that gets called when a value gets set.
	 * provides the element ID when it gets called.
	 */
	void SetOnSave(std::function<void(unsigned int)> onSave);
};
