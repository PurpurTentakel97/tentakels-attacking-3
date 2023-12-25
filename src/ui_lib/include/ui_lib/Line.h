//
// Purpur Tentakel
// 06.10.2022
//

#pragma once
#include "UIElement.hpp"

/**
 * provides a line.
 * the line is drawn from collider.x, collider.y to collider.x + with, collider.y + height.
 * to draw a line from right to left used a negative width.
 * same applies for the height.
 */
class Line final : public UIElement {
private:
	Vector2 m_start;
	Vector2 m_end;
	float m_thick; ///< contains the thickness of the line
	Color m_color; ///< contains the color the line is rendered with

public:
	/**
	 * ctor.
	 * only initialisation.
	 */
	Line(Vector2 start, Vector2 end, float thick, Color color);

	/**
	 * renders the line.
	 */
	void Render(AppContext_ty_c appContext);

	/**
	 * Updates all chances.
	 */
	virtual void Update();

	/**
	 * return the relative start point.
	 */
	[[nodiscard]] Vector2 GetStart() const;
	/**
	 * sets the relative start point.
	 * need to update.
	 */
	virtual void SetStart(Vector2 start);
	
	/**
	 * returns the relative end point.
	 */
	[[nodiscard]] Vector2 GetEnd() const;
	/**
	 * sets the relative end point.
	 * need tp update.
	 */
	virtual void SetEnd(Vector2 end);

	/**
	 * return the thickness.
	 */
	[[nodiscard]] float GetThick() const;
	/**
	 * sets the thickness.
	 * no nee to update.
	 */
	void SetThick(float thick);

	/**
	 * return the color.
	 */
	[[nodiscard]] Color GetColor() const;
	/**
	 * sets the color.
	 * no need to update.
	 */
	void SetColor(Color color);
};
