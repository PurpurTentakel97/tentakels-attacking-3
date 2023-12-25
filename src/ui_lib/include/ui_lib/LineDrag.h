//
// Purpur Tentakel
// 30.05.2023
//

#pragma once
#include "UIElement.hpp"

class LineDrag final : public UIElement {
private:
	Vector2 m_start; ///< contains the relative start of the line
	Vector2 m_end; ///< contains the relative end of the line
	float m_thick; ///< contains the thickness the line gets rendered with
	Color m_color; ///< contains the color the lein gets rendere with
	std::function<void(Vector2, Vector2)> m_callback; ///< gets called, returns global relative start and end position
	bool m_render{ false };///< contains if the line gets rendered

public:
	/**
	 * sets default values.
	 * most will be overwritten in CheckAndUpdate.
	 */
	LineDrag(float thick, Color color, std::function<void(Vector2, Vector2)> callback);

	/**
	 * returns the relative start position on the screen.
	 */
	[[nodiscard]] Vector2 GetStart() const;
	/**
	 * returns the relative end position on the screen.
	 */
	[[nodiscard]] Vector2 GetEnd() const;
	/**
	 * sets the thickness of the line.
	 */
	void SetThick(float thick);
	/**
	 * return the thickness of the line.
	 */
	[[nodiscard]] float GetThick() const;
	/**
	 * sets the color of the line.
	 */
	void SetColor(Color color);
	/**
	 * returns the color of the line.
	 */
	[[nodiscard]] Color GetColor() const;
	/**
	 * sets the callback that gets called after releasing the left mouse button.
	 */
	void SetCallback(std::function<void(Vector2, Vector2)> callback);
	/**
	 * removes the callback
	 */
	void ClearCallback();

	/**
	 * moves the line and handles if a mouse button is pressed and mouse is moved.  
	 */
	void CheckAndUpdate(Vector2 const& mousePosition, AppContext const&) override;
	/**
	 * renders the line if the flag is set. 
	 */
	void Render(AppContext const&) override;
};
