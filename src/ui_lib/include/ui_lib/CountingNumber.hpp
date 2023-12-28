//
// Purpur Tentakel
// 27.06.2023
//

#pragma once
#include "UIElement.hpp"
#include <helper/HUIAlias.hpp>


class CountingNumber : public UIElement {
public:
    enum Type {
        LINEAR,
        ASYMPTOTIC,
    };

private:
    Text_ty m_text;

    bool m_isCounting{ false };
    Type m_countingType{ LINEAR };
    int m_startNumber;
    int m_currentNumber;
    int m_targetNumber;

    double m_timeInS{ 0.0 };
    double m_startCountingTime{ GetTime() };

    Color m_countingColor{ RED };
    Color m_defaultColor{ WHITE };

    using callback_ty = std::function<void(Type, int, int, double)>;
    callback_ty m_callback{ [](Type, int, int, double) -> void {} };

    bool m_isCountingOutNumbers{ false };

    void HandleCountingOutNumbers();

    void HandleCounting();

    void HandleLinearCounting();

    void HandleAsymptoticCounting();

    void SetNewNumber(int number);

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

    void SetCountingColor(Color color);

    void SetDefaultColor(Color color);

    [[nodiscard]] bool IsCounting() const;

    void SetCallback(callback_ty callback);

    void CountTo(Type type, int target, double timeIsS);

    void SetTo(int target);

    [[nodiscard]] int GetCurrentNumber() const;

    [[nodiscard]] int GetTargetNumber() const;

    void CheckAndUpdate(Vector2 const& mousePosition, AppContext_ty_c appContext) override;

    void Render(AppContext_ty_c appContext) override;

    void Resize(AppContext_ty_c appContext) override;
};
