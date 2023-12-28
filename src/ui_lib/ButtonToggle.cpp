//
// Purpur Tentakel
// 16.07.2023
//

#include "ButtonToggle.hpp"
#include <AppContext.hpp>
#include <helper/HInput.hpp>

void ToggleButton::UpdateState() {
    if (m_state == State::DISABLED) {
        return;
    }

    if (IsFocused() and (IsConfirmInputDown() or CheckCollisionPointRec(GetMousePosition(), m_collider))) {
        m_state = State::PRESSED;
        return;
    }

    if (CheckCollisionPointRec(GetMousePosition(), m_collider)) {
        m_state = State::HOVER;
        return;
    }

    m_state = m_isToggled ? State::PRESSED : State::ENABLED;
}

ToggleButton::ToggleButton(
        unsigned int focusID,
        Vector2 pos,
        Vector2 size,
        Alignment alignment,
        std::string const& text,
        SoundType releaseSound
)
    : Button{ pos, size, alignment, text, releaseSound },
      Focusable{ focusID } { }

void ToggleButton::CheckAndUpdate(Vector2 const& mousePosition, AppContext_ty_c appContext) {

    switch (m_state) {
        case State::DISABLED: {
            bool play{ ((CheckCollisionPointRec(mousePosition, m_collider)
                         and IsMouseButtonPressed(MouseButton::MOUSE_BUTTON_LEFT)))
                       or (IsFocused() and IsConfirmInputPressed()) };

            if (play) {
                PlaySoundEvent const event{ SoundType::CLICKED_DISABLED_STD };
                appContext.eventManager.InvokeEvent(event);
            }
            break;
        }

        case State::HOVER: {
            if (not CheckCollisionPointRec(mousePosition, m_collider)) {
                m_state = m_isToggled ? State::PRESSED : State::ENABLED;
                PlaySoundEvent const event{ SoundType::HOVER_STD };
                appContext.eventManager.InvokeEvent(event);
            } else {
                if (IsMouseButtonPressed(MouseButton::MOUSE_BUTTON_LEFT)) {
                    m_state = State::PRESSED;
                    PlaySoundEvent const event{ SoundType::CLICKED_PRESS_STD };
                    appContext.eventManager.InvokeEvent(event);
                } else if (IsFocused() and IsConfirmInputPressed()) {
                    m_state = State::PRESSED;
                    PlaySoundEvent const event{ SoundType::CLICKED_PRESS_STD };
                    appContext.eventManager.InvokeEvent(event);
                }
            }
            break;
        }

        case State::ENABLED: {
            if (CheckCollisionPointRec(mousePosition, m_collider)) {
                m_state = State::HOVER;
                PlaySoundEvent const event{ SoundType::HOVER_STD };
                appContext.eventManager.InvokeEvent(event);
            }
            if (IsFocused() and IsConfirmInputPressed()) {
                m_state = State::PRESSED;
                PlaySoundEvent const event{ SoundType::CLICKED_PRESS_STD };
                appContext.eventManager.InvokeEvent(event);
            }
            break;
        }

        case State::PRESSED: {
            if (CheckCollisionPointRec(mousePosition, m_collider)) {
                if (IsMouseButtonPressed(MouseButton::MOUSE_BUTTON_LEFT) or (IsFocused() and IsConfirmInputPressed())) {
                    PlaySoundEvent const event{ SoundType::CLICKED_PRESS_STD };
                    appContext.eventManager.InvokeEvent(event);
                }
                if (IsMouseButtonUp(MouseButton::MOUSE_BUTTON_LEFT) and not IsConfirmInputDown()) {
                    m_state = m_isToggled ? State::PRESSED : State::HOVER;
                }
                if (IsMouseButtonReleased(MouseButton::MOUSE_BUTTON_LEFT)) {
                    m_isToggled = not m_isToggled;
                    m_onToggle(m_isToggled, false);
                    if (IsConfirmInputUp()) {
                        m_state = m_isToggled ? State::PRESSED : State::HOVER;
                    }
                    PlaySoundEvent const event{ m_sound };
                    appContext.eventManager.InvokeEvent(event);
                }
                if (IsFocused() and IsConfirmInputReleased()) {
                    m_isToggled = not m_isToggled;
                    m_onToggle(m_isToggled, true);
                    if (IsMouseButtonUp(MouseButton::MOUSE_BUTTON_LEFT)) {
                        m_state = m_isToggled ? State::PRESSED : State::HOVER;
                    }
                    PlaySoundEvent const event{ m_sound };
                    appContext.eventManager.InvokeEvent(event);
                }
            } else {
                if (IsFocused() and IsConfirmInputPressed()) {
                    PlaySoundEvent const event{ SoundType::CLICKED_PRESS_STD };
                    appContext.eventManager.InvokeEvent(event);
                }
                if (IsMouseButtonReleased(MouseButton::MOUSE_BUTTON_LEFT)) {
                    if (IsConfirmInputUp()) {
                        m_state = m_isToggled ? State::PRESSED : State::ENABLED;
                    }
                }
                if (IsFocused() and IsConfirmInputReleased()) {
                    m_isToggled = not m_isToggled;
                    m_onToggle(m_isToggled, true);
                    if (IsMouseButtonUp(MouseButton::MOUSE_BUTTON_LEFT)) {
                        m_state = m_isToggled ? State::PRESSED : State::ENABLED;
                    }
                    PlaySoundEvent const event{ m_sound };
                    appContext.eventManager.InvokeEvent(event);
                }
            }
            break;
        }

        default: {
            throw std::runtime_error("invalid toggle button state");
            break;
        }
    }
}

Rectangle ToggleButton::GetCollider() const {
    return m_collider;
}

void ToggleButton::SetEnabled(bool enabled) {
    Button::SetEnabled(enabled);
    UpdateState();
}

bool ToggleButton::IsEnabled() const {
    return m_state != State::DISABLED;
}

bool ToggleButton::IsToggled() const {
    return m_isToggled;
}

void ToggleButton::SetToggleButton(bool isToggled) {
    m_isToggled = isToggled;
    UpdateState();
}

void ToggleButton::SetOnToggle(std::function<void(bool, bool)> onToggle) {
    m_onToggle = std::move(onToggle);
}
