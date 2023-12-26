//
// Purpur Tentakel
// 23.07.2023
//

#pragma once
#include "UIElement.hpp"

class CountRing final : public UIElement {
private:
	Vector2 m_absolutePos; ///< contains the absolute position
	float m_relativeDotSize; ///<< contains the relative dot size
	float m_absoluteDotSize; ///<< contains the relative dot size
	float m_relativeMaxRingSize; ///< contains the absolute outer size
	float m_absoluteRingSize; ///< contains the absolute outer size
	int m_currentCount; ///< contains the current count of the elements
	int m_maxCount; ///< contains the max count of the elements
	Color m_dotColor{ BLACK }; //< contains the dot color
	Color m_ringColor{ GREY_50 }; //< contains the ring color

	/**
	 * calculates the absolute ring size.
	 */
	void CalculateRing();

public:

	CountRing(Vector2 pos, Vector2 size, Alignment alignment, 
		float innerSize, float ringSize, int currentCount, int maxCount);

	/**
	 * returns if the ring is overlapping with a rectangle
	 */
	[[nodiscard]] bool IsOverlapping(Rectangle const& rect) const;

	/**
	 * calls the Ring to set ne new values.
	 */
	void Update();
	/**
	 * returns the maximum count the ring is referring to while calculating.
	 */
	[[nodiscard]] int GetMaxCount() const;
	/**
	 * sets the maximum count the ring is referring to while calculating.
	 */
	void SetMaxCount(int maxCount);
	/**
	 * returns the current count the ring is referring to while calculating.
	 */
	[[nodiscard]] int GetCurrentCount() const;
	/**
	 * sets the current count the ring is referring to while calculating.
	 */
	void SetCurrentCount(int currentCount);
	/**
	 * returns the dot color.
	 */
	[[nodiscard]] Color GetDotColor() const;
	/**
	 * sets a new color the dot is rendered with.
	 */
	void SetDotColor(Color color);
	/**
	 * returns the ring color.
	 */
	[[nodiscard]] Color GetRingColor() const;
	/**
	 * sets a new color the ring is rendered with.
	 */
	void SetRingColor(Color color);

	/**
	 * updates the position.
	 */
	void SetPosition(Vector2 newPos) override;
	/**
	 * calls only the UIElement to update.
	 */
	void CheckAndUpdate(Vector2 const& mousePosition, AppContext_ty_c appContext) override;
	/**
	 * renders the ring if there is a count.
	 */
	void Render(AppContext_ty_c appContext) override;
	/**
	 * Calls the UIElement top resize and calls Update for the ring.
	 */
	void Resize(AppContext_ty_c appContext) override;
};
