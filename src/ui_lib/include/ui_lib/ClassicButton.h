//
// Purpur Tentakel
// 04.09.2022
//

#pragma once
#include "Button.h"
#include "Focusable.h"

/**
 * standard button that calls function if it gets released and is down.
 */
class ClassicButton final : public Button, public Focusable {
private:
public:
	/**
	 * ctor.
	 * only initialisation
	 */
	ClassicButton(unsigned int focusID, Vector2 pos, Vector2 size, Alignment alignment,
		std::string const& text, SoundType releaseSound);

	/**
	 * returns if the button is enabled.
	 */
	[[nodiscard]] bool IsEnabled() const override;

	/**
	 * calculates the logic of the button and calls the other functions.
	 * calls CheckAndUpdate in button.
	 */
	void CheckAndUpdate(Vector2 const& mousePosition, AppContext_ty_c appContext) override;
	
	/**
	 * return current collider of the button.
	 */
	[[nodiscard]] Rectangle GetCollider() const override;
};
