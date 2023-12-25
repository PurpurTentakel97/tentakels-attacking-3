//
// Purpur Tentakel
// 31.08.2022
//

#pragma once
#include "Button.h"

/**
 * is used by the slider lass as button to slide.
 */
class SliderButton final : public Button {
public:
	using Button::Button;
	using Button::operator=;

	/**
	 * logic of the slider button.
	 * calls CheckAndUpdate from button.
	 */
	void CheckAndUpdate(Vector2 const& mousePosition, AppContext_ty_c appContext) override;

};
