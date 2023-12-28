//
// Purpur Tentakel
// 15.08.2022
//

#include "Button.hpp"
#include <app/AppContext.hpp>

void Button::SetTextSizeAndPosition(app::AppContext_ty_c appContext) {
    Resolution_ty_c resolution{ app::AppContext::GetInstance().GetResolution() };
    m_textSize = m_collider.height / 2;
    Vector2 textSize = MeasureTextEx(*(appContext.assetManager.GetFont()), m_text.c_str(), m_textSize, 0.0f);
    while (textSize.x + 20 > m_collider.width) {
        if (m_textSize <= 1) {
            break;
        }

        m_textSize -= 1;
        textSize = MeasureTextEx(*(appContext.assetManager.GetFont()), m_text.c_str(), m_textSize, 0.0f);
    }

    m_textPosition.x = resolution.x * m_pos.x + (resolution.x * m_size.x / 2 - textSize.x / 2);
    m_textPosition.y = resolution.y * m_pos.y + (resolution.y * m_size.y / 2 - m_textSize / 2);
}

bool Button::IsSameState(State const state) const {
    return m_state == state;
}

void Button::UpdateCollider() {
    UIElement::UpdateCollider();

    SetTextSizeAndPosition(app::AppContext::GetInstance());
}

Button::Button(
        Vector2 const pos,
        Vector2 const size,
        Alignment const alignment,
        std::string text,
        app::SoundType const releaseSound
)
    : UIElement{ pos, size, alignment },
      m_text{ std::move(text) },
      m_sound{ releaseSound } {

    m_texture = app::AppContext::GetInstance().assetManager.GetTexture(app::AssetType::BUTTON_DEFAULT);
    m_textureRec = { 0.0f,
                     0.0f,
                     static_cast<float>(m_texture->width),
                     static_cast<float>(m_texture->height) / static_cast<float>(m_buttonParts) };

    SetTextSizeAndPosition(app::AppContext::GetInstance());
}

Button::Button()
	: UIElement{ {0.0f,0.0f}, {0.0f,0.0f}, Alignment::TOP_LEFT },
	m_sound{ app::SoundType::CLICKED_RELEASE_STD }, m_textPosition{ 0.0f,0.0f },
	m_texture{ nullptr }, m_textureRec{ 0.0f,0.0f,0.0f,0.0f } {}

void Button::CheckAndUpdate(Vector2 const& mousePosition, app::AppContext_ty_c appContext) {
    UIElement::CheckAndUpdate(mousePosition, appContext);

    bool const hover{ CheckCollisionPointRec(mousePosition, m_collider) };
    if (m_state == State::DISABLED) {
        if (hover && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            eve::PlaySoundEvent const event{ app::SoundType::CLICKED_DISABLED_STD };
            appContext.eventManager.InvokeEvent(event);
        }
        return;
    }

    if (!hover) {
        if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) {
            m_isPressed = false;
        }

        if (m_isPressed) {
            m_state = State::ENABLED;
            return;
        }

        if (IsSameState(State::HOVER)) {
            eve::PlaySoundEvent const event{ app::SoundType::HOVER_STD };
            appContext.eventManager.InvokeEvent(event);
        }
        m_state = State::ENABLED;
        return;
    }

    if (m_isPressed) {
        m_onPress();
        if (!IsSameState(State::PRESSED)) {
            m_state = State::PRESSED;
            return;
        }

        if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) {
            eve::PlaySoundEvent const event{ m_sound };
            appContext.eventManager.InvokeEvent(event);
            m_state = hover ? State::HOVER : State::ENABLED;
            m_isPressed = false;
            m_onClick();
            return;
        }
    } else {
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            m_isPressed = true;
            m_state = State::PRESSED;
            eve::PlaySoundEvent const event{ app::SoundType::CLICKED_PRESS_STD };
            appContext.eventManager.InvokeEvent(event);
            m_onPress();
            return;
        }
        if (!IsSameState(State::HOVER)) {
            m_state = State::HOVER;
            eve::PlaySoundEvent const event{ app::SoundType::HOVER_STD };
            appContext.eventManager.InvokeEvent(event);
            return;
        }
    }
}

void Button::Render(app::AppContext_ty_c appContext) {
    m_textureRec.y = m_textureRec.height * static_cast<float>(m_state);
    DrawTexturePro(*m_texture, m_textureRec, m_collider, Vector2(0.0f, 0.0f), 0, WHITE);
    DrawTextEx(
            *(appContext.assetManager.GetFont()),
            m_text.c_str(),
            Vector2{ m_textPosition.x, m_textPosition.y },
            static_cast<float>(m_textSize),
            0,
            WHITE
    );
}
void Button::Resize(app::AppContext_ty_c appContext) {
    UIElement::Resize(appContext);
    SetTextSizeAndPosition(appContext);
}

void Button::SetOnClick(std::function<void()> onClick) {
    m_onClick = std::move(onClick);
}

void Button::SetOnPress(std::function<void()> onPress) {
    m_onPress = std::move(onPress);
}

void Button::SetText(std::string const& text) {
    m_text = text;
    SetTextSizeAndPosition(app::AppContext::GetInstance());
}

std::string Button::GetText() const {
    return m_text;
}

void Button::SetEnabled(bool const enabled) {
    if (enabled) {
        m_state = State::ENABLED;
    } else {
        m_state = State::DISABLED;
        m_isPressed = false;
    }
}

bool Button::IsEnabled() const {
    return m_state != State::DISABLED;
}

void Button::SetCollider(Rectangle const collider) {
    m_textPosition.x += (collider.x - m_collider.x);
    m_textPosition.y += (collider.y - m_collider.y);
    UIElement::SetCollider(collider);
}

void Button::SetPosition(Vector2 const pos) {
    UIElement::SetPosition(pos);
    SetTextSizeAndPosition(app::AppContext::GetInstance());
}
