//
// Purpur Tentakel
// 04.09.2022
//

#include "ButtonClassic.hpp"
#include <app/AppContext.hpp>
#include <helper/HInput.hpp>


namespace uil {
    ClassicButton::ClassicButton(
            utl::usize const focusID,
            Vector2 const pos,
            Vector2 const size,
            Alignment const alignment,
            std::string const& text,
            app::SoundType const releaseSound
    )
        : Button{ pos, size, alignment, text, releaseSound },
          Focusable{ focusID } { }

    [[nodiscard]] bool ClassicButton::IsEnabled() const {
        return m_state != State::DISABLED;
    }

    void ClassicButton::CheckAndUpdate(Vector2 const& mousePosition, app::AppContext_ty_c appContext) {

        if (IsFocused()) {
            if (m_state == State::DISABLED) {
                if (hlp::IsConfirmInputPressed()) {
                    eve::PlaySoundEvent const event{ app::SoundType::CLICKED_DISABLED_STD };
                    appContext.eventManager.InvokeEvent(event);
                    return;
                }

                bool const disabledAction{ hlp::IsConfirmInputDown() or hlp::IsConfirmInputReleased() };
                if (disabledAction) {
                    return;
                }
            }

            if (hlp::IsConfirmInputPressed()) {
                if (m_state != State::PRESSED) {
                    m_state = State::PRESSED;
                    m_isPressed = true;
                    eve::PlaySoundEvent const event{ app::SoundType::CLICKED_PRESS_STD };
                    appContext.eventManager.InvokeEvent(event);
                    return;
                }
            }

            if (m_isPressed and hlp::IsConfirmInputDown()) {
                m_state = State::PRESSED;
                m_onPress();
                return;
            }

            if (m_isPressed and hlp::IsConfirmInputReleased()) {
                bool const hover{ CheckCollisionPointRec(mousePosition, m_collider) };
                if (!hover or !IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
                    m_state = hover ? State::HOVER : State::ENABLED;
                    m_isPressed = false;

                    eve::PlaySoundEvent const event{ m_sound };
                    appContext.eventManager.InvokeEvent(event);
                    m_onClick();
                    return;
                }
            }
        }

        Button::CheckAndUpdate(mousePosition, appContext);
    }

    Rectangle ClassicButton::GetCollider() const {
        return UIElement::GetCollider();
    }
} // namespace uil
