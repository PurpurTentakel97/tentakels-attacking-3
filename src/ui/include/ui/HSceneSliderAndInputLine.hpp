//
// Purpur Tentakel
// 27.10.2022
//

#pragma once

#include <functional>
#include <ui_lib/InputLine.hpp>
#include <ui_lib/Scene.hpp>


namespace ui {
    class SliderAndInputLine : public uil::Scene {
    private:
        uil::Slider_ty m_slider;
        uil::InputLine_int_ty m_inputLine;
        uil::ClassicButton_ty m_btn;
        std::function<void(utl::usize)> m_onSave{ [](utl::usize) {} };

        bool m_isEnabled{ true };
        bool m_slided{ false };
        utl::usize m_minValue;
        utl::usize m_maxValue;
        utl::usize m_currentValue;

        void Initialize(utl::usize focusID);

        void BtnPressed();

        void SaveValue();

        void Slide(float position);

        void ValidateCurrentValue();

        void SetSliderValue() const;

    public:
        SliderAndInputLine(
                utl::usize focusID,
                Vector2 pos,
                Vector2 size,
                uil::Alignment alignment,
                utl::usize minValue,
                utl::usize maxValue,
                utl::usize currentValue
        );

        void CheckAndUpdate(Vector2 const& mousePosition, app::AppContext_ty_c appContext) override;

        void SetEnabled(bool isEnabled);

        void SetOnSave(std::function<void(utl::usize)> onSave);

        void SetValue(utl::usize value);

        void RandomValue();
    };
} // namespace ui
