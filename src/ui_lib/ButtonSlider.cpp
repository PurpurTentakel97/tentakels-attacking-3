//
// Purpur Tentakel
// 31.08.2022
//


#include "ButtonSlider.hpp"
#include <AppContext.hpp>

void SliderButton::CheckAndUpdate(Vector2 const& mousePosition, AppContext_ty_c appContext) {
    UIElement::CheckAndUpdate(mousePosition, appContext);
    bool const hover{ CheckCollisionPointRec(mousePosition, m_collider) };
    if (m_state == State::DISABLED) {
        if (hover && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            eve::PlaySoundEvent const event{ SoundType::CLICKED_DISABLED_STD };
            appContext.eventManager.InvokeEvent(event);
        }
        return;
    }

    if (!hover) {
        if (m_isPressed) {
            if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) {
                m_isPressed = false;
                m_state = State::ENABLED;
                eve::PlaySoundEvent const event{ SoundType::CLICKED_RELEASE_STD };
                appContext.eventManager.InvokeEvent(event);
                m_onClick();
            }
            return;
        }
        if (IsSameState(State::HOVER)) {
            m_state = State::ENABLED;
            eve::PlaySoundEvent const event{ SoundType::HOVER_STD };
            appContext.eventManager.InvokeEvent(event);
        }
        return;
    }
    if (m_isPressed) {
        m_onPress();

        if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) {
            eve::PlaySoundEvent const event{ SoundType::CLICKED_RELEASE_STD };
            appContext.eventManager.InvokeEvent(event);
            m_isPressed = false;
            m_state = hover ? State::HOVER : State::ENABLED;
            m_onClick();
            return;
        }
    } else {
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            m_isPressed = true;
            m_state = State::PRESSED;
            eve::PlaySoundEvent const event{ SoundType::CLICKED_PRESS_STD };
            appContext.eventManager.InvokeEvent(event);
            m_onPress();
            return;
        }
        if (!IsSameState(State::HOVER)) {
            m_state = State::HOVER;
            eve::PlaySoundEvent const event{ SoundType::HOVER_STD };
            appContext.eventManager.InvokeEvent(event);
            return;
        }
    }
}
