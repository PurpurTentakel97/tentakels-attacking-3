//
// Purpur Tentakel
// 14.09.2022
//

#pragma once
#include "UIElement.hpp"
#include <string>

/**
 * displays a text in a collider that can be aligned. 
 */
class Text final : public UIElement {
private:
	using render_ty = std::vector<std::pair<std::string const, Vector2>>;
	std::string m_text; ///< contains the raw string that was set to the text
	render_ty m_toRender;///< contains the modified string that gets rendered and the position of each line
	std::string m_URL{ "" }; ///< contains an URL that can be opened by klick
	float m_textHeight; ///< contains the absolute text height in px
	float m_textSize; ///< contains the relativ text size
	Alignment m_textAlignment; ///< contains the text alignment
	Color m_color{ WHITE }; ///< contains the color the text will be rendered in

	bool m_lineBreaks{ false }; ///< contains if the text is automatically breaks in multiple lines
	bool m_renderRectangle{ false }; ///< contains if the collider will be rendered
	bool m_renderBackground{ false }; ///< contains if the text will render a background if its a dark color

	/**
	 * generates a printable version if the raw string.
	 * that contains the alignment and the line breaks.
	 */
	void CreateToRender();
	/**
	 * calls a helper function that replaces some whitespace with \n.
	 * returns directly if the line break is deactivated.
	 */
	std::vector<std::string> BreakLines(std::string toBreak) const;

	/**
	 * opens the provided URL if one is provided.
	 * else nothing happens.
	 */
	void OpenURL() const;

	/**
	 * calls UpdateCollider of the UIElement.
	 * updates the text position.
	 */
	void UpdateCollider() override;

public:
	/**
	 * ctor.
	 * calls to generate to render.
	 */
	Text(Vector2 pos, Vector2 size, Alignment alignment,
		Alignment textAlignment, float textHeight, std::string text);

	/**
	 * text logic.
	 * in particular if it gets pressed.
	 */
	void CheckAndUpdate(Vector2 const& mousePosition, AppContext_ty_c appContext);
	/**
	 * renders the text.
	 */
	void Render(AppContext_ty_c appContext);
	/**
	 * resizes the text.
	 * creates a not render string.
	 */
	void Resize(AppContext_ty_c appContext) override;

	/**
	 * updates the text position and the collider.
	 */
	void SetPosition(Vector2 pos) override;
	/**
	 * updates the text size and the collider.
	 */
	void SetSize(Vector2 size) override;
	/**
	 * calls UIElement to set collider.
	 * create a new render text.
	 */
	void SetCollider(Rectangle colider) override;

	/**
	 * returns the current relative text height.
	 */
	[[nodiscard]] float GetRelativeTextHeight();

	/**
	 * sets a new raw string.
	 * generates a new render string.
	 */
	void SetText(std::string text);
	/**
	 * returns the raw string.
	 */
	[[nodiscard]] std::string GetText() const;

	/**
	 * sets the text color.
	 */
	void SetColor(Color color);
	/**
	 * returns the text color.
	 */
	[[nodiscard]] Color GetColor() const;

	/**
	 * sets the text url.
	 */
	void SetURL(std::string URL);
	/**
	 * clears the text url.
	 */
	void ClearURL();
	/**
	 * returns the text url.
	 */
	[[nodiscard]] std::string GetURL() const;

	/**
	 * sets if the line Beaks are generated.
	 * creates a new render string.
	 */
	void LineBreaks(bool lineBreaks);
	/**
	 * sets if the collider gets rendered.
	 */
	void RenderRectangle(bool renderRectangle);

	/**
	 * sets if the text renders a background for dark colors.
	 */
	void SetRenderBackground(bool isRenderBackround);
	/**
	 * returns if the backgrounds gets currently renders for dark colors.
	 */
	[[nodiscard]] bool GetRenderBackground() const;
};
