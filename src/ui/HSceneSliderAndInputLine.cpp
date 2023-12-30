//
// Purpur Tentakel
// 27.10.2022
//

#include "HSceneSliderAndInputLine.hpp"
#include <helper/HRandom.hpp>
#include <memory>
#include <ui_lib/ButtonClassic.hpp>
#include <ui_lib/InputLine.hpp>
#include <ui_lib/Slider.hpp>


namespace ui {
    void SliderAndInputLine::Initialize(unsigned int focusID) {
        m_inputLine = std::make_shared<uil::InputLine<int>>(
                focusID,
                GetElementPosition(0.77f, 0.0f),
                GetElementSize(0.13f, 1.0f),
                uil::Alignment::TOP_LEFT,
                5
        );
        m_inputLine->SetOnEnter([this]() { this->BtnPressed(); });
        m_inputLine->SetValue(m_currentValue);
        ValidateCurrentValue();
        m_slided = true;
        m_inputLine->SetPlaceholderText("%");
        m_elements.push_back(m_inputLine);

        ++focusID;

        m_btn = std::make_shared<uil::ClassicButton>(
                focusID,
                GetElementPosition(0.9f, 0.0f),
                GetElementSize(0.1f, 1.0f),
                uil::Alignment::TOP_LEFT,
                "Set",
                app::SoundType::CLICKED_RELEASE_STD
        );
        m_btn->SetOnClick([this]() { this->BtnPressed(); });
        m_btn->SetEnabled(false);
        m_elements.push_back(m_btn);

        m_slider = std::make_shared<uil::Slider>(
                GetElementPosition(0.0f, 0.1f),
                GetElementSize(0.75f, 0.8f),
                uil::Alignment::TOP_LEFT,
                true,
                10.0f
        );
        m_slider->SetOnSlide([this](float position) { Slide(position); });
        SetSliderValue();
        m_elements.push_back(m_slider);
    }

    void SliderAndInputLine::BtnPressed() {
        SaveValue();
        m_slided = false;
        SetSliderValue();
        m_btn->SetEnabled(false);
    }

    void SliderAndInputLine::SaveValue() {
        ValidateCurrentValue();
        m_onSave(m_currentValue);
    }

    void SliderAndInputLine::Slide(float const position) {
        m_currentValue = static_cast<int>(
                (static_cast<float>(m_maxValue - m_minValue) * position / 100.0f) + static_cast<float>(m_minValue)
        );
        m_inputLine->SetValue(m_currentValue);
        SaveValue();
        m_slided = true;
    }

    void SliderAndInputLine::ValidateCurrentValue() {
        m_currentValue = m_inputLine->GetValue();

        if (m_currentValue < m_minValue) {
            m_currentValue = m_minValue;
        } else if (m_currentValue > m_maxValue) {
            m_currentValue = m_maxValue;
        }

        m_inputLine->SetValue(m_currentValue);
    }

    void SliderAndInputLine::SetSliderValue() const {
        float const percent{ static_cast<float>(m_currentValue - m_minValue)
                             / static_cast<float>(m_maxValue - m_minValue) * 100.0f };
        m_slider->SetButtonPosition(percent);
    }

    SliderAndInputLine::SliderAndInputLine(
            unsigned int const focusID,
            Vector2 const pos,
            Vector2 const size,
            uil::Alignment const alignment,
            int const minValue,
            int const maxValue,
            int const initialValue
    )
        : Scene{ pos, size, alignment },
          m_minValue{ minValue },
          m_maxValue{ maxValue } {

        m_currentValue = initialValue;
        Initialize(focusID);
    }

    void SliderAndInputLine::CheckAndUpdate(Vector2 const& mousePosition, app::AppContext_ty_c appContext) {

        if (!m_isEnabled) {
            return;
        }

        Scene::CheckAndUpdate(mousePosition, appContext);


        if (m_inputLine->HasValueChanced()) {
            if (!m_slided) {
                m_btn->SetEnabled(true);
            } else {
                m_slided = false;
            }
        }
    }

    void SliderAndInputLine::SetEnabled(bool const isEnabled) {
        m_isEnabled = isEnabled;
        m_slider->SetEnabled(isEnabled);
        m_inputLine->SetEnabled(isEnabled);
        if (isEnabled) {
            if (m_currentValue != m_inputLine->GetValue()) {
                m_btn->SetEnabled(isEnabled);
            }
        } else {
            m_btn->SetEnabled(isEnabled);
        }
    }

    void SliderAndInputLine::SetOnSave(std::function<void(int)> onSave) {
        m_onSave = std::move(onSave);
    }

    void SliderAndInputLine::SetValue(int const value) {
        m_currentValue = value;
        ValidateCurrentValue();
        m_inputLine->SetValue(m_currentValue);
        m_slider->SetButtonPosition(static_cast<float>(m_currentValue));
        m_slided = true;
    }

    void SliderAndInputLine::RandomValue() {
        auto& random{ hlp::Random::GetInstance() };
        m_currentValue = static_cast<int>(random.random(static_cast<size_t>(m_maxValue - m_minValue))) + m_minValue;
        m_inputLine->SetValue(m_currentValue);
        SetSliderValue();
        SaveValue();
    }
} // namespace ui
