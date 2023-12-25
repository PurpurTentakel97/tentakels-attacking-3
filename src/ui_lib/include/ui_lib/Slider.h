//
// Purpur Tentakel
// 29.08.2022
//

#pragma once
#include "SliderButton.h"

/**
 * provides a slider that returns values between 0 and 100 if its getting slide.
 */
class Slider final : public UIElement {
private:
	bool m_isEnabled{ true }; ///< contains if the slider is enabled
	bool m_isHorizontal; ///< contains if the slider is horizontal or vertical
	bool m_isPressed{ false }; ///< contains if the button slider is currently pressed
	bool m_isScroll{ false }; ///< contains if the slider if currently scrolling
	float m_absoluteDimension{ 1.0f }; ////< contains the ration between the slider and button size
	float m_btnOffset{ 0.0f }; ///< contains the offset between the mouse and the button center

	SliderButton m_btn; ///< contains the button of the slider
	std::function<void(float)> m_onSlide{ [](float) {} }; ///< contains the onSlider lambda it gets called if the button gets moved

	/**
	 * calculates the initial position an size of the button.
	 */
	void CalculateInitialButton();

	/**
	 * calculates the position in the slider and calls onSlide.
	 */
	void CalculateOnSlide() const;
	/**
	 * slides the button.
	 * sets the offset if the mouse is onto the button.
	 */
	void Slide();
	/**
	 * slides the button if the mouse is no longer over the button but the mouse is still pressed.
	 */
	void SlideIfPressed();
	/**
	 * slides the button if the slider collider around the button is pressed.
	 */
	void MoveButtonIfColliderIsPressed(Vector2 const& mousePosition);
	/**
	 * slides the button if the mouse wheel is turned.
	 */
	void SlideIfScroll();
	/**
	 * sets the offset between the mouse position and the middle of the btn collider.
	 * resets the offset if the mouse position is outside of the button collider.
	 */
	void SetOffset(Vector2 mousePosition);

public:
	/**
	 * ctor.
	 * loads texture.
	 * initialize button.
	 */
	Slider(Vector2 pos,Vector2 size, Alignment alignment,
		bool isHorizontal, float absoluteDimension);

	/**
	 * logic of the slider.
	 * calls the button to update.
	 */
	void CheckAndUpdate(Vector2 const& mousePosition, AppContext_ty_c appContext) override;
	/**
	 * renders the slider.
	 * calls the button to render.
	 */
	void Render(AppContext_ty_c appContext) override;
	/**
	 * resizes the slider.
	 * calls the button to resize.
	 */
	void Resize(AppContext_ty_c appContext) override;
 
	/**
	 * sets the onSlide lambda that gets called when the slider gets slide.
	 */
	void SetOnSlide(std::function<void(float)> onSlide);
	/**
	 * sets button position onto the slider.
	 */
	void SetButtonPosition(float position);

	/**
	 * sets if the button reacts to the mouse wheel.
	 */
	void SetScrolling(bool isScroll);
	/**
	 * returns if the button reacts to the mouse wheel.
	 */
	[[nodiscard]] bool IsScrolling() const;

	/**
	 * sets a new ratio between the slider and button size.
	 */
	void SetAbsoluteDimension(float absolutDimension);
	/**
	 * returns the ratio between the slider and button size.
	 */
	[[nodiscard]] float GetAbsoluteDimension() const;

	/**
	 * sets the slider enabled.
	 */
	void SetEnabled(bool isEnabled);
	/**
	 * returns if the provided point is colliding with the slider.
	 */
	[[nodiscard]] bool IsColliding(Vector2 point) const;
};
