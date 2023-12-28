//
// Purpur Tentakel
// 01.12.2022
//

#include "DropDownElement.hpp"
#include <app/AppContext.hpp>
#include <helper/HInput.hpp>
#include <helper/HTextProcessing.hpp>

void DropDownElement::CreateToRender() {
    Resolution_ty_c resolution{ app::AppContext::GetInstance().GetResolution() };
    m_toRender = m_text;
    hlp::StripString(m_toRender);
    m_fontSize = hlp::GetElementTextHeight(m_size, resolution.y);
    m_toRender = hlp::GetPrintableTextInCollider(m_toRender, m_fontSize, m_collider, app::AppContext::GetInstance());

    m_textPosition = { m_collider.x + 5.0f, m_collider.y + (m_collider.height - m_fontSize) / 2 };
}

void DropDownElement::UpdateCollider() {
    UIElement::UpdateCollider();
    CreateToRender();
}

void DropDownElement::UpdateColliderReverse() {
    UIElement::UpdateColliderReverse();
    CreateToRender();
}

DropDownElement::DropDownElement(
        Vector2 const pos,
        Vector2 const size,
        Alignment const alignment,
        unsigned int const focusID,
        unsigned int const ID,
        std::string text,
        std::function<Rectangle(Rectangle)> getTemporaryCollider
)
    : UIElement{ pos, size, alignment },
      Focusable{ focusID },
      m_ID{ ID },
      m_text{ std::move(text) },
      m_getTemporaryCollider{ std::move(getTemporaryCollider) } {

    CreateToRender();
}

void DropDownElement::CheckAndUpdate(Vector2 const& mousePosition, app::AppContext_ty_c appContext) {

    UIElement::CheckAndUpdate(mousePosition, appContext);

    Rectangle const temporaryCollider{ m_getTemporaryCollider(m_collider) };

    m_hover = CheckCollisionPointRec(mousePosition, temporaryCollider);

    if (m_hover && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
        m_onClick(m_ID);
    }
    if (IsFocused() && hlp::IsConfirmInputPressed()) {
        m_onClick(m_ID);
    }
}

void DropDownElement::Render(app::AppContext_ty_c appContext) {

    DrawRectangleRec(m_collider, GREY_100);

    DrawRectangleLinesEx(m_collider, 1.0f, WHITE);

    DrawTextPro(
            *(appContext.assetManager.GetFont()),
            m_toRender.c_str(),
            m_textPosition,
            { 0.0f, 0.0f },
            0.0f,
            m_fontSize,
            0.0f,
            WHITE
    );

    if (m_hover) {
        DrawRectangleRec(m_collider, GREY_50);
    }
}

bool DropDownElement::IsEnabled() const {
    return m_isEnabled;
}

void DropDownElement::SetEnabled(bool const isEnabled) {
    m_isEnabled = isEnabled;
}

void DropDownElement::SetText(std::string text) {
    m_text = std::move(text);
    CreateToRender();
}

std::string DropDownElement::GetText() const {
    return m_text;
}

unsigned int DropDownElement::GetID() const {
    return m_ID;
}

void DropDownElement::SetOnClick(std::function<void(unsigned int)> onClick) {
    m_onClick = std::move(onClick);
}

Rectangle DropDownElement::GetCollider() const {
    return m_collider;
}
