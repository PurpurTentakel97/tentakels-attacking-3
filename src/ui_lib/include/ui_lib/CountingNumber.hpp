//
// Purpur Tentakel
// 27.06.2023
//

#pragma once
#include "UIElement.hpp"
#include <helper/HUIAlias.hpp>

/**
 * provides a number that can count in a amount of time to a new number.
 * the callback gets called when the counting is finished.
 * the number can be displayed in different colors while counting in default. 
 */
class CountingNumber : public UIElement {
public:
    /**
	 * contains possible counting types.
	 */
    enum Type {
        LINEAR,
        ASYMPTOTIC,
    };

private:
    Text_ty m_text; ///< contains the text that gets displayed

    bool m_isCounting{ false };    ///< contains if the number is currently counting
    Type m_countingType{ LINEAR }; ///< contains the current counting type
    int m_startNumber;             ///< contains the number the current counting stated with.
    int m_currentNumber;           ///< contains the current number. this number gets displayed
    int m_targetNumber;            ///< contains the number the current counting will end.

    double m_timeInS{ 0.0f };                ///< contains the time the current counting will take.
    double m_startCountingTime{ GetTime() }; ///< contains the time in seconds the current counting started

    Color m_countingColor{ RED };  ///< contains the color the text gets displayd with while counting
    Color m_defaultColor{ WHITE }; ///< cointains the color the text gets displayed with while not counting

    using callback_ty = std::function<void(Type, int, int, double)>;
    callback_ty m_callback{ [](Type, int, int, double) -> void {} }; ///< gets called when the counting has finidhed

    bool m_isCountingOutNumbers{ false }; ///< contains if the current counting has same start and end.


    /**
	 * handles the "counting" when the target and the start number are the same from th beginning of the count.
 	 */
    void HandleCountingOutNumbers();
    /**
	 * handles wether the number should count and how.
	 */
    void HandleCounting();
    /**
	 * hands the linear counting.
	 */
    void HandleLinearCounting();
    /**
	 * handles the asymptotic counting.
	 * this counting will start fast and gets slower over time.
	 */
    void HandleAsymptoticCounting();
    /**
	 * sets the new number in this class and the text.
	 */
    void SetNewNumber(int number);
    /**
	 * updates the color within the text.
	 */
    void UpdateColor();

public:
    CountingNumber(
            Vector2 pos,
            Vector2 size,
            Alignment alignment,
            Alignment textAlignment,
            float textHeight,
            int startNumber
    );

    /**
	 * sets the color for rendering while counting.
	 */
    void SetCountingColor(Color color);
    /**
	 * sets the color for rendering without counting.
	 */
    void SetDefaultColor(Color color);
    /**
	 * returns if the number is currently counting.
	 */
    [[nodiscard]] bool IsCounting() const;
    /**
	 * sets the callback function that gets called when the counting process is finished.
	 */
    void SetCallback(callback_ty callback);
    /**
	 * counts in a certain type to a other number in a provided time in s.
	 */
    void CountTo(Type type, int target, double timeIsS);
    /**
	 * sets the number immediately without callback and stop all counting.
	 */
    void SetTo(int target);
    /**
	 * returns the current number.
	 * differs from target number while counting.
	 */
    [[nodiscard]] int GetCurrentNumber() const;
    /**
	 * return the target number.
	 * differs from current number while counting.
	 */
    [[nodiscard]] int GetTargetNumber() const;


    /**
	 * 
	 */
    void CheckAndUpdate(Vector2 const& mousePosition, AppContext_ty_c appContext) override;
    /**
	 *
	 */
    void Render(AppContext_ty_c appContext) override;
    /**
	 * 
	 */
    void Resize(AppContext_ty_c appCntext) override;
};
