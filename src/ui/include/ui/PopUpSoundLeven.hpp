//
// Purpur Tentakel
// 14.11.2022
//

#pragma once
#include "ui_lib/PopUp.hpp"

class ClassicButton;
class Slider;
class CheckBox;

/**
 * provides a popup that sets the sound level.
 */
class SoundLevelPopUp final : public PopUp {
private:
	Slider_ty m_slider; ///< contains the slider to set the sound level
	CheckBox_ty m_checkBox; ///< contains the checkbox to mute the sound
	ClassicButton_ty m_acceptBtn; ///< contains the button to set the current value

	/**
	 * initializes all ui elements.
	 */
	void Initialize();

public:
	/**
	 * ctor.
	 * only initialisation.
	 */
	SoundLevelPopUp(Vector2 pos, Vector2 size, Alignment alignment,
		std::string const& title, std::string& subTitle);

	/**
	 * renders the popup.
	 * calls the slider, checkbox and button to render.
	 */
	void Render(AppContext_ty_c appContext) override;
};
