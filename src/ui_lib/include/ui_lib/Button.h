//
// Purpur Tentakel
// 15.08.2022
//

#pragma once
#include "UIElement.hpp"
#include <string>
#include <functional>

/**
 * base button class
 * 
 */
class Button : public UIElement {
protected:
	enum class State { ///< contains the possible button states
		ENABLED,
		HOVER,
		PRESSED,
		DISABLED,
	};
	bool m_isPressed{ false }; ///< contains if the button is currently pressed
	Texture2D* m_texture{ }; ///< contains a pointer of the btn texture
	Rectangle m_textureRec{ }; ///< defines a rectangle on the texture that will be rendered
	State m_state{ State::ENABLED }; ///< contains the current button state
	int m_buttonParts{ 4 }; ///< defines in how many parts the texture gets split

	float m_textSize{ 24.0f }; ///< defines the text height in px
	std::string m_text{ }; ///< contains the text on the button
	Vector2 m_textPosition{ }; ///< contains the position of the text

	SoundType m_sound{ }; ///< contains the release sound of the button

	std::function<void()> m_onClick{ []() {} }; ///< contains a lambda that gets called if the button is down
	std::function<void()> m_onPress{ []() {} }; ///< contains a lambda that gets called if the button is released

	/**
	 * calculates the text size and position.
	 */
	void SetTextSizeAndPosition(AppContext_ty_c appContext);
	/**
	 * checks if the provided state is the same as the current state.
	 */
	[[nodiscard]] bool IsSameState(State state) const;

	/**
	 * calls UpdateCollider from the UIElement.
	 * updated the text position and size.
	 */
	void UpdateCollider() override;

public:
	/**
	 * ctor.
	 * initialize and calls text calculating.
	 */
	Button(Vector2 pos, Vector2 size, Alignment alignment,
		std::string const& text, SoundType releaseSound);
	Button();

	/**
	 * complete logic og the button.
	 */
	virtual void CheckAndUpdate(Vector2 const& mousePosition, AppContext_ty_c appContext) override;
	/**
	 * renders the button.
	 */
	void Render(AppContext_ty_c appContext) override;
	/**
	 * calls resize from UIElement.
	 * resizes the text.
	 */
	void Resize(AppContext_ty_c appContext) override;

	/**
	 * sets the onClick lambda that is called when the button gets released.
	 */
	void SetOnClick(std::function<void()> onClick);
	/**
	 * sets the onPress lambda that is called when the button is down.
	 */
	void SetOnPress(std::function<void()> onPress);

	/**
	 * sets a new button text and calculates the new text height.
	 */
	void SetText(std::string const& text);
	/**
	 * returns the current text.
	 */
	[[nodiscard]] std::string GetText() const;

	/**
	 * sets weather the button is enabled or not.
	 */
	virtual void SetEnabled(bool enabled);
	/**
	 * returns if the button is enabled.
	 */
	[[nodiscard]] bool IsEnabled() const;

	/**
	 * sets a new collider.
	 * calls the UIElement and resets text position.
	 */
	void SetCollider(Rectangle collider) override;
	
	/**
	 * sets a new position and resets the text position,
	 */
	void SetPosition(Vector2 pos) override;
};
