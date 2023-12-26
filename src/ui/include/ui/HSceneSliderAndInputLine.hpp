//
// Purpur Tentakel
// 27.10.2022
//

#pragma once
#include "ui_lib/Scene.h"
#include "ui_lib/InputLine.hpp"
#include <functional>


/**
 * provides a scene that contains a slider, a button and an input line.
 */
class SliderAndInputLine : public Scene {
private:
	Slider_ty m_slider; ///< contains a the slider
	InputLine_int_ty m_inputLine; ///< contains a the input line
	ClassicButton_ty m_btn; ///< contains a the button
	std::function<void(int)> m_onSave{ [](int) {} }; ///< contains the llambda that gets called on save -> provides the current value

	bool m_isEnabled{ true }; ///< contains if the scene is enabled
	bool m_slided{ false }; ///< contains if the scene is currently sliding -> locks the button if the value in the input line chanced because of the slider
	int m_minValue; ///< contains the provided min value that should can be set.
	int m_maxValue; ///< contains the provided max value that should can be set.
	int m_currentValue; ///< contains the current value

	/**
	 * initializes all ui elements.
	 * connects the actions.
	 */
	void Initialize(unsigned int focusID);
	/**
	 * saves the value.
	 * sets the slider.
	 * disables the button.
	 */
	void BtnPressed();
	/**
	 * calls validate value.
	 * calls on save.
	 */
	void SaveValue();
	/**
	 * calculates current value.
	 * sets input line.
	 * calls save value.
	 */
	void Slide(float position);
	/**
	 * clamps the current value between min and max value.
	 * sets the current value in the input line.
	 * no need to net it somewhere else because it gets not set here, just validated.
	 */
	void ValidateCurrentValue();
	/**
	 * calculates the current percentage.
	 * sets the slider value.
	 */
	void SetSliderValue() const;

public:
	/**
	 * ctor.
	 * only initialization.
	 */
	SliderAndInputLine(unsigned int focusID, Vector2 pos, Vector2 size, Alignment alignment, 
		int minValue, int maxValue, int currentValue);

	/**
	 * scene logic.
	 */
	void CheckAndUpdate(Vector2 const& mousePosition, AppContext_ty_c appContext) override;

	/**
	 * sets if the scene is enabled.
	 */
	void SetEnabled(bool isEnabled);

	/**
	 * sets the lambda that gets called when the value is saved.
	 * returns the current value.
	 */
	void SetOnSave(std::function<void(int)> onSave);
	/**
	 * sets a new current value.
	 * validates the value.
	 * sets it in slider and input line.
	 */
	void SetValue(int value);

	/**
	 * randomizes a value between min and max value.
	 * updates slider and input line.
	 * saves the value.
	 */
	void RandomValue();
};
