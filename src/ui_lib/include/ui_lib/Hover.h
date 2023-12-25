//
// Purpur Tentakel
// 08.05.2023
//

#include "UIElement.hpp"
#pragma once


class Hover final : public UIElement {
private:
	std::string m_text; ///< contains the Hover text
	Color m_color; ///< contains the render text color
	Vector2 m_hoverOffset; ///< contains the offset between mouse and rectangle in decimal
	Vector2 m_absoluteHoverOffset; ///< contains the offset between mouse and rectangle in px

	float m_textHeight; ///< contains text size in px
	Vector2 m_textPosition; ///< contains the text position in px

	/**
	 * calculates textHeight, textPosition, colliderLength.
	 */
	void CalculateDefault(AppContext_ty_c appContext);

public:
	/**
	 * ctor
	 */
	Hover(float height, std::string text, Color color, Vector2 hoverOffset);

	/**
	 * calculates the collider for drawing so it can not go out of screen.
	 */
	[[nodiscard]] Vector2 GetRenderOffset() const;

	/**
	 * sets the position to the mouse position.
	 * renders the hover.
	 */
	void SetRenderHover(Vector2 mousePosition, AppContext_ty_c appContext);

	/**
	 * sets a new text to hovering
	 */
	void SetText(std::string const& text);

	/**
	 * renders the hover.
	 * gets called from HoverRender
	 */
	void Render(AppContext_ty_c appContext) override;
	/**
	 * renders the hover with offset.
	 * gets called from HoverRenderer
	 */
	float RenderOffset(AppContext_ty_c appContex, Vector2 const& offset) const;

	/**
	 * resizes the argument
	 */
	void Resize(AppContext_ty_c appContext) override;
};
