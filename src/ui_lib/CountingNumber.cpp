//
// Purpur Tentakel
// 27.06.2023
//

#include "CountingNumber.hpp"
#include "Text.hpp"
#include <app/AppContext.hpp>


namespace uil {
    void CountingNumber::HandleCountingOutNumbers() {
        if (not m_isCounting) {
            m_isCounting = true;
            m_startCountingTime = GetTime();
            UpdateColor();
        }

        if (m_isCounting and (GetTime() > m_startCountingTime + m_timeInS)) {
            m_isCounting = false;
            m_isCountingOutNumbers = false;
            UpdateColor();
            m_callback(m_countingType, m_startNumber, m_currentNumber, m_timeInS);
        }
    }

    void CountingNumber::HandleCounting() {
        if (m_currentNumber != m_targetNumber and not m_isCounting) {
            m_isCounting = true;
            m_startCountingTime = GetTime();
            UpdateColor();
        }
        if (not m_isCounting) {
            return;
        }

        switch (m_countingType) {
            default:
            case LINEAR:
                HandleLinearCounting();
                break;
            case ASYMPTOTIC:
                HandleAsymptoticCounting();
                break;
        }

        if ((m_targetNumber - m_startNumber) >= 0) {
            if (m_targetNumber < m_currentNumber) {
                m_currentNumber = m_targetNumber;
            }
        } else {
            if (m_targetNumber > m_currentNumber) {
                m_currentNumber = m_targetNumber;
            }
        }

        if (m_currentNumber == m_targetNumber and m_isCounting) {
            m_isCounting = false;
            m_callback(m_countingType, m_startNumber, m_currentNumber, m_timeInS);
            UpdateColor();
        }
    }

    void CountingNumber::HandleLinearCounting() {
        double const percent{ (GetTime() - m_startCountingTime) / m_timeInS };
        int nextNumber = { m_startNumber + static_cast<int>((m_targetNumber - m_startNumber) * percent) };

        SetNewNumber(nextNumber);
    }

    void CountingNumber::HandleAsymptoticCounting() {
        double const percent{ std::sqrt((GetTime() - m_startCountingTime) / m_timeInS) };
        int nextNumber = { m_startNumber + static_cast<int>((m_targetNumber - m_startNumber) * percent) };

        SetNewNumber(nextNumber);
    }

    void CountingNumber::SetNewNumber(int const number) {
        m_currentNumber = number;
        m_text->SetText(std::to_string(m_currentNumber));
    }

    void CountingNumber::UpdateColor() {
        if (m_isCounting) {
            m_text->SetColor(m_countingColor);
        } else {
            m_text->SetColor(m_defaultColor);
        }
    }

    CountingNumber::CountingNumber(
            Vector2 const pos,
            Vector2 const size,
            Alignment const alignment,
            Alignment const textAlignment,
            float const textHeight,
            int const startNumber
    )
        : UIElement{ pos, size, alignment },
          m_startNumber{ startNumber },
          m_currentNumber{ startNumber },
          m_targetNumber{ startNumber } {
        m_text = std::make_shared<Text>(pos, size, alignment, textAlignment, textHeight, std::to_string(startNumber));
    }

    void CountingNumber::SetCountingColor(Color const color) {
        m_countingColor = color;
        UpdateColor();
    }
    void CountingNumber::SetDefaultColor(Color const color) {
        m_defaultColor = color;
        UpdateColor();
    }

    bool CountingNumber::IsCounting() const {
        return m_isCounting;
    }

    void CountingNumber::SetCallback(callback_ty callback) {
        m_callback = std::move(callback);
    }

    void CountingNumber::CountTo(Type const type, int const target, double const timeIsS) {
        m_countingType = type;
        m_targetNumber = target;
        m_timeInS = timeIsS;
        m_startNumber = m_currentNumber;
        if (target == m_currentNumber) {
            m_timeInS /= 3;
            m_isCountingOutNumbers = true;
        }
    }

    void CountingNumber::SetTo(int const target) {
        m_targetNumber = target;
        m_currentNumber = m_targetNumber;
        m_text->SetText(std::to_string(m_currentNumber));
        m_isCounting = false;
        m_isCountingOutNumbers = false;
        UpdateColor();
    }

    int CountingNumber::GetCurrentNumber() const {
        return m_currentNumber;
    }

    int CountingNumber::GetTargetNumber() const {
        return m_targetNumber;
    }

    void CountingNumber::CheckAndUpdate(Vector2 const& mousePosition, app::AppContext_ty_c appContext) {
        if (m_isCountingOutNumbers) {
            HandleCountingOutNumbers();
        } else {
            HandleCounting();
        }
        m_text->CheckAndUpdate(mousePosition, appContext);
    }

    void CountingNumber::Render(app::AppContext_ty_c appContext) {
        m_text->Render(appContext);
    }

    void CountingNumber::Resize(app::AppContext_ty_c appContext) {
        UIElement::Resize(appContext);
        m_text->Resize(appContext);
    }
} // namespace uil
