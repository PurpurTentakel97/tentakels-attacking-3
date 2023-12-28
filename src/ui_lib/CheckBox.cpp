//
// Purpur Tentakel
// 23.10.2022
//

#include "CheckBox.hpp"
#include <app/AppContext.hpp>
#include <event/EventsUI.hpp>
#include <helper/HInput.hpp>

void CheckBox::Check(app::AppContext_ty_c appContext) {
    if (m_isChecked) {
        eve::PlaySoundEvent const event{ SoundType::CLICKED_RELEASE_STD };
        appContext.eventManager.InvokeEvent(event);
    } else {
        eve::PlaySoundEvent const event{ SoundType::CLICKED_PRESS_STD };
        appContext.eventManager.InvokeEvent(event);
    }

    m_isChecked = !m_isChecked;

    m_onCheck(m_ID, m_isChecked);
}

CheckBox::CheckBox(unsigned int const focusID, Vector2 const pos, float const height, Alignment const alignment, unsigned int const checkBoxID)
	: UIElement{ pos, { 0.0f, height }, alignment }, Focusable{ focusID },
	m_ID{ checkBoxID } {

    app::AppContext_ty appContext{ app::AppContext::GetInstance() };
    Resolution_ty_c resolution{ appContext.GetResolution() };
    m_size.x = resolution.y / resolution.x * m_size.y;
    UpdateCollider();

    m_texture = appContext.assetManager.GetTexture(AssetType::CHECK);
    m_textureRec = { 0.0f, 0.0f, static_cast<float>(m_texture->width), static_cast<float>(m_texture->height) };
}

void CheckBox::SetOnCheck(std::function<void(unsigned int, bool)> onCheck) {
    m_onCheck = std::move(onCheck);
}

unsigned int CheckBox::GetID() const {
    return m_ID;
}

void CheckBox::SetChecked(bool const isChecked) {
    m_isChecked = isChecked;
}

bool CheckBox::IsChecked() const {
    return m_isChecked;
}

void CheckBox::SetEnabled(bool const isEnabled) {
    m_isEnabled = isEnabled;
}

bool CheckBox::IsEnabled() const {
    return m_isEnabled;
}

Rectangle CheckBox::GetCollider() const {
    return UIElement::GetCollider();
}

void CheckBox::CheckAndUpdate(Vector2 const& mousePosition, app::AppContext_ty_c appContext) {

    UIElement::CheckAndUpdate(mousePosition, appContext);

    bool check{ false };

    if (IsFocused()) {
        if (hlp::IsConfirmInputPressed()) {
            if (m_isEnabled) {
                check = true;
            } else {
                eve::PlaySoundEvent const event{ SoundType::CLICKED_DISABLED_STD };
                appContext.eventManager.InvokeEvent(event);
            }
        }
    }

    if (CheckCollisionPointRec(mousePosition, m_collider)) {
        m_isHovered = true;

        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            if (m_isEnabled) {
                check = true;
            } else {
                eve::PlaySoundEvent const event{ SoundType::CLICKED_DISABLED_STD };
                appContext.eventManager.InvokeEvent(event);
            }
        }
    } else {
        m_isHovered = false;
    }

    if (check) {
        Check(appContext);
    }
}

void CheckBox::Render(app::AppContext_ty_c) {
    DrawRectangleLinesEx(m_collider, 3.0f, WHITE);

    if (m_isChecked) {
        DrawTexturePro(*m_texture, m_textureRec, m_collider, Vector2(0.0f, 0.0f), 0.0f, WHITE);
    }

    if (!m_isEnabled) {
        DrawRectangleRec(m_collider, GREY_50);
    }

    if (m_isHovered) {
        DrawRectangleRec(m_collider, GREY_50);
    }
}

void CheckBox::Resize(app::AppContext_ty_c appContext) {

    Resolution_ty_c resolution{ appContext.GetResolution() };
    m_size.x = resolution.y / resolution.x * m_size.y;

    UIElement::Resize(appContext);
}
