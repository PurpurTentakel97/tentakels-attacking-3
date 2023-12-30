//
// Purpur Tentakel
// 29.08.2022
//

#pragma once

#include "ButtonSlider.hpp"


namespace uil {

    class Slider final : public UIElement {
    private:
        bool m_isEnabled{ true };
        bool m_isHorizontal;
        bool m_isPressed{ false };
        bool m_isScroll{ false };
        float m_absoluteDimension{ 1.0f };
        float m_btnOffset{ 0.0f };

        SliderButton m_btn;
        std::function<void(float)> m_onSlide{ [](float) {} };

        void CalculateInitialButton();

        void CalculateOnSlide() const;

        void Slide();

        void SlideIfPressed();

        void MoveButtonIfColliderIsPressed(Vector2 const& mousePosition);

        void SlideIfScroll();

        void SetOffset(Vector2 mousePosition);

    public:
        Slider(Vector2 pos, Vector2 size, Alignment alignment, bool isHorizontal, float absoluteDimension);

        void CheckAndUpdate(Vector2 const& mousePosition, app::AppContext_ty_c appContext) override;

        void Render(app::AppContext_ty_c appContext) override;

        void Resize(app::AppContext_ty_c appContext) override;

        void SetOnSlide(std::function<void(float)> onSlide);

        void SetButtonPosition(float position);

        void SetScrolling(bool isScroll);

        [[nodiscard]] bool IsScrolling() const;

        void SetAbsoluteDimension(float absolutDimension);

        [[nodiscard]] float GetAbsoluteDimension() const;

        void SetEnabled(bool isEnabled);

        [[nodiscard]] bool IsColliding(Vector2 point) const;
    };
} // namespace uil
