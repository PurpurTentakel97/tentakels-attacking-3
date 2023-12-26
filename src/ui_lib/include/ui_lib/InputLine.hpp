//
// Purpur Tentakel
// 06.09.2022
//

#pragma once
#include "AppContext.hpp"
#include "Focusable.h"
#include "UIElement.hpp"
#include "helper/HInput.h"
#include "helper/HTextProcessing.h"
#include <functional>
#include <string>

/**
 * provides text input.
 */
template <class T>
class InputLine final : public UIElement, public Focusable {
protected:
	bool m_isEnabled{ true }; ///< contains if the input line is enabled
	bool m_shouldClearByFocus{ false }; ///< contains if the input lines clears by getting focussed and new input
	bool m_isClearNextInput{ false }; ///< contains if the input line clears by the next input once
	bool m_alreadyCleared{ false }; ///< contains if the input line got already cleared
	unsigned int m_charLimit; ///< contains the max about of chars in the input line
	std::string m_value; ///< contains the current value
	std::string m_oldValue; ///< contains the old value
	std::string m_placeholderText; ///< contains the placeholder text -> gets showed when no value is provided
	double m_backspacePressTime{ 0.0 }; ///< contains the time since the last time backspace got pressed and still hold
	std::function<void()> m_onEnter{ []() {} }; ///< contains the onEnter lambda gets called then enter is pressed
	std::function<void()> m_onValueChanced{ []() {} }; ///< contains the lambda that gets calles when the value chances.

	/**
	 * checks weather the input line is still full.
	 * if not the char is added.
	 * returns if a char was added.
	 */
	bool AddChar(int key) {
		bool const validAdd{ m_charLimit > m_value.size() };

		if (validAdd) {
			m_value += static_cast<char>(key);

			PlaySoundEvent const event { SoundType::TEXT };
			AppContext::GetInstance().eventManager.InvokeEvent(event);

			m_onValueChanced();
		}

		return validAdd;
	}
	/**
	 * removes a char if the input line is not empty.
	 * if it is empty: nothing happens.
	 */
	void RemoveChar() {
		if (m_value.size() != 0) {
			m_value.pop_back();

			PlaySoundEvent const event { SoundType::TEXT };
			AppContext::GetInstance().eventManager.InvokeEvent(event);

			m_onValueChanced();
		}
	}
	/**
	 * gets deleted here because it is overloaded for each of the provided datatypes.
	 * checks if a specific key is a valid key.
	 */
	[[nodiscard]] bool IsValidKey(int key) = delete;

public:
	/**
	 * ctor.
	 * loads texture.
	 */
	InputLine(unsigned int focusID, Vector2 pos, Vector2 size, Alignment alignment, unsigned int charLimit)
		: UIElement{ pos, size, alignment }, Focusable{ focusID }, m_charLimit{ charLimit }  { }

	/**
	 * logic of the input line.
	 */
	void CheckAndUpdate(Vector2 const& mousePosition, AppContext_ty_c appContext) override {

		UIElement::CheckAndUpdate(mousePosition, appContext);

		if (!m_isEnabled) { return; }

		bool const hover{ CheckCollisionPointRec(mousePosition, m_collider) };
		bool const validSelect{
			    !IsFocused()
			and hover
			and IsMouseButtonPressed(MOUSE_LEFT_BUTTON) 
		};

		if (validSelect) {
			SelectFocusElementEvent const event { this };
			appContext.eventManager.InvokeEvent(event);
		}

		if (!IsFocused()) { m_alreadyCleared = false; return; }

		bool const enter{ IsOnlyEnterConfirmInputPressed() };
		if (enter) {
			m_onEnter();
		}

		if (IsKeyPressed(KEY_BACKSPACE)) {
			RemoveChar();
			m_backspacePressTime = GetTime();
			return;
		}

		if (IsKeyDown(KEY_BACKSPACE)) {
			if (m_backspacePressTime < GetTime() - 0.5) {
				RemoveChar();
				return;
			}
		}

		while (true) {
			int const key{ GetCharPressed() };

			if (key <= 0) { break; }

			if (not m_alreadyCleared) {
				if (m_shouldClearByFocus and GotFocused()) {
					Clear();
					m_alreadyCleared = true;
				}
			}
			if (m_isClearNextInput) {
				Clear();
				m_isClearNextInput = false;
			}

			if (!IsValidKey(key)) { continue; }

			if (!AddChar(key)) {
				ShowMessagePopUpEvent const event{
					appContext.languageManager.Text("ui_input_line_popup_max_input_title"),
					appContext.languageManager.Text("ui_input_line_popup_max_input_text"),
					[]() { }
				};
				appContext.eventManager.InvokeEvent(event);
				break;
			}
		}
	}
	/**
	 * renders the input line
	 */
	void Render(AppContext_ty_c appContext) override {

		auto const constants{ appContext.constants.textProcessing };
		// Update here to make sure its after call of HasValueChanced();
		m_oldValue = m_value;

		DrawRectangleRec(
			m_collider,
			GREY_100
		);

		if (m_isEnabled) {
			DrawRectangleLinesEx(
				m_collider,
				2.0f,
				PURPLE
			);
		}

		float const posX{ m_collider.x + 10.0f };
		float const posY{ m_collider.y + m_collider.height * 0.1f };
		float const fontSize{ m_collider.height * 0.8f };
		std::string printableInput{ "" };

		if (m_value.size() > 0) {
			printableInput = GetPrintableTextInCollider(
				m_value,
				fontSize,
				m_collider,
				appContext
			);
			DrawTextEx(
				*(appContext.assetManager.GetFont()),
				printableInput.c_str(),
				Vector2(posX, posY),
				fontSize,
				0,
				WHITE
			);
		}
		else {
			std::string const printablePlaceholder{ GetPrintablePlaceholderTextInCollider(
				m_placeholderText,
				fontSize,
				m_collider,
				appContext
			) };
			DrawTextEx(
				*(appContext.assetManager.GetFont()),
				printablePlaceholder.c_str(),
				Vector2(posX, posY),
				fontSize,
				0,
				GRAY
			);
		}


		if (IsFocused()) {
			size_t const time{ static_cast<size_t>(GetTime() * 2.0) };
			Vector2 textLength = MeasureTextEx(
				*(appContext.assetManager.GetFont()),
				printableInput.c_str(),
				fontSize,
				0.0f
			);

			if (time % 2 == 0) {
				DrawTextEx(
					*(appContext.assetManager.GetFont()),
					&constants.cursor,
					Vector2(
						posX + constants.cursorOffset + textLength.x,
						posY + m_collider.height * 0.05f
					),
					fontSize,
					0,
					PURPLE
				);
			}
		}
	}

	/**
	 * sets a new placeholder text.
	 * it will be rendered if the input line is empty.
	 */
	void SetPlaceholderText(std::string placeholderText) {
		m_placeholderText = placeholderText;
	}
	/**
	 * sets a value into the input line.
	 */
	void SetValue(T value) {
		m_value = std::to_string(value);
		m_onValueChanced();
	}
	/**
	 * extends the current value.
	 * adds the provided text an the end oif the current text.
	 */
	void ExtendValue(T value) {
		m_value += std::to_string(value);
		m_onValueChanced();
	}
	/**
	 * gets deleted here because it is overloaded for each of the provided datatypes.
	 * returns the value.
	 */
	[[nodiscard]] T GetValue() = delete;
	/**
	 * clears the input line.
	 */
	void Clear() {
		m_value.clear();
		m_onValueChanced();
	}

	/**
	 * returns the current collider.
	 */
	[[nodiscard]] Rectangle GetCollider() const override {
		return UIElement::GetCollider();
	}
	/**
	 * returns if the input line has any value.
	 */
	[[nodiscard]] bool HasValue() const {
		return !m_value.empty();
	}
	/**
	 * returns if the value has chanced since the last tick.
	 */
	[[nodiscard]] bool HasValueChanced() const {
		return m_value != m_oldValue;
	}
	/**
	 * sets the onEnter lambda that is called when enter is pressed.
	 */
	void SetOnEnter(std::function<void()> onEnter) {
		m_onEnter = onEnter;
	}
	/**
	 * sets the onValueChanced lambda that is called when the value of the input line chanced.
	 */
	void SetOnValueChanced(std::function<void()> onValueChanged) {
		m_onValueChanced = onValueChanged;
	}

	/**
	 * sets if the input line clears itself when it gets focused and an input happens.
	 */
	void SetShouldClearByFocus(bool isShouldClearByFocus) {
		m_shouldClearByFocus = isShouldClearByFocus;
	}
	/**
	 * returns if the input line clears itself when it gets focused and an input happens.
	 */
	[[nodiscard]] bool IsShouldClearByFocus() const {
		return m_shouldClearByFocus;
	}
	/**
	 * clears the input line by next input
	 */
	void ClearByNextInput() {
		m_isClearNextInput = true;
	}
	
	/**
	 * returns if the input line is enabled.
	 */
	[[nodiscard]] bool IsEnabled() const override {
		return m_isEnabled;
	}
	/**
	 * sets if the input line is enabled.
	 */
	void SetEnabled(bool isEnabled) {
		m_isEnabled = isEnabled;
	}
};

/**
 * checks if its a valid key for a int input line.
 */
template<>
inline bool InputLine<int>::IsValidKey(int key) {
	return {
			key >= 48
		and key <= 57 
	};
}
/**
 * checks if its a valid key for a float input line.
 */
template<>
inline bool InputLine<float>::IsValidKey(int key) {
	bool valid{ (key >= 48 and key <= 57) // numbers
		or key == 44 // comma
		or key == 46 }; // dot

	//check for multiple commas/dots
	if ('.' == key or ',' == key) {
		if (m_value.size() == 0) {
			valid = false;
		}

		for (char const &c : m_value) {
			if ('.' == c or ',' == c) {
				valid = false;
				break;
			}
		}
	}

	return valid;
}
/**
 * checks if its a valid key for a double input line.
 */
template<>
inline bool InputLine<double>::IsValidKey(int key) {
	bool valid{ (key >= 48 and key <= 57) // numbers
		or key == 44 // comma
		or key == 46 }; // dot

	//check for multiple commas/dots
	if ('.' == key or ',' == key) {
		if (m_value.size() == 0) {
			valid = false;
		}

		for (char const& c : m_value) {
			if ('.' == c or ',' == c) {
				valid = false;
				break;
			}
		}
	}

	return valid;
}
/**
 * checks if its a valid key for a string input line.
 */
template<>
inline bool InputLine<std::string>::IsValidKey(int key) {
	return {
			key >= 32
		and key <= 126 
	};
}

/**
 * returns the value for a int input line.
 */
template<>
[[nodiscard]] inline int InputLine<int>::GetValue() {
	StripString(m_value);
	if (m_value.size() == 0) {
		return 0;
	}
	return std::stoi(m_value);
}
/**
 * returns the value for a float input line.
 */
template<>
[[nodiscard]] inline float InputLine<float>::GetValue() {
	StripString(m_value);
	if (m_value.size() == 0) {
		return 0.0f;
	}
	for (char c : m_value) {
		if (c == ',') {
			c = '.';
			break;
		}
	}
	return std::stof(m_value);
}
/**
 * returns the value for a double input line.
 */
template<>
[[nodiscard]] inline double InputLine<double>::GetValue() {
	StripString(m_value);
	if (m_value.size() == 0) {
		return 0.0;
	}
	for (char& c : m_value) {
		if (c == ',') {
			c = '.';
			break;
		}
	}
	return std::stod(m_value);
}
/**
 * returns the value for a string input line.
 */
template<>
[[nodiscard]] inline std::string InputLine<std::string>::GetValue() {
	StripString(m_value);
	return m_value;
}

/**
 * sets the value for a string input line.
 * need of this overload because std::to_string doesn't provides an overload for an std::string.
 */
template<>
inline void InputLine<std::string>::SetValue(std::string value) {
	m_value = value;
	m_onValueChanced();
}
/**
 * sets the value for a string input line.
 * need of this overload because std::to_string doesn't provides an overload for an std::string.
 */
template<>
inline void InputLine<std::string>::ExtendValue(std::string value) {
	m_value += value;
	m_onValueChanced();
}
