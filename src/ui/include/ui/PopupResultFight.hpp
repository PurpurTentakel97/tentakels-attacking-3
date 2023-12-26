//
// PurpurTentakel
// 06.07.23
//

#pragma once
#include "helper/HFightResult.hpp"
#include "ui_lib/CountingNumber.h"
#include "ui_lib/PopUp.h"

class FightResultPopup : public PopUp {
private:
	HFightResult const m_result; ///< contains the result that will be shown
	size_t m_index{ 1 }; ///< contains the current index within the result
	bool m_finishedCounting{ false }; ///< contains if the popup has finished all counting calls

	using callback_ty = std::function<void()>; ///< type of the callback function
	callback_ty m_callback { []() {} }; ///< gets called when the popup closes
	
	CountingNumber_ty m_leftNumber; ///< contains the left counting number
	CountingNumber_ty m_rightNumber; ///< contains the right counting number
	
	static inline std::string s_emptyString{""}; ///< contains a empty string to initialize the popup
	Text_ty m_winText; ///< contains the text who won -> gets set when the fight is finished
	
	ClassicButton_ty m_closeBtn; ///< contains the skip/close button

	/**
	 * initialises all ui elements
	 */
	void Initialize();
	/**
	 * returns if a number is still counting.
	 * calls the numbers to count to the next number.
	 */
	void NextNumber(bool const left);
	void NextNumber(CountingNumber::Type, int, int, double, bool const left);
	/**
	 * sets the numbers to ne last entry immediately.
	 */
	void SetLastStep();
	/**
	 * sets the final text (after counting) in the popup.
	 */
	void SetEnd();

	/**
	 * handles the button callback.
	 * closes the popup or skips the counting part.
	 */
	void HandleButton();

public:
	/**
	 * ctor.
	 */
	FightResultPopup(Vector2 pos, Vector2 size, Alignment alignment,
		HFightResult const result, callback_ty callback);
};
