//
// Purpur Tentakel
// 04.01.2024
//

#include "TableCell.hpp"
#include "utils/Colors.hpp"

namespace uil {
    void TableCell::CallCallbacks() {
        m_updated(*this);
        m_onValueChanced(*this);
    }

    void TableCell::SetStringValue() {
        if (IsA<std::string>()) {
            m_stringValue = Value<std::string>();
        } else if (IsA<utl::usize>()) {
            m_stringValue = std::to_string(Value<utl::usize>());
        } else if (IsA<double>()) {
            m_stringValue = std::to_string(Value<double>());
        } else if (IsA<Color>()) {
            m_stringValue = utl::Colors::AsString(Value<Color>());
        } else {
            assert(false and "unreachable");
        }
    }

    TableCell::TableCell(Vector2 const pos,
                         Vector2 const size,
                         Alignment const alignment,
                         utl::usize const focusID,
                         TableCell::callback_ty updated)
        : UIElement{ pos, size, alignment },
          Focusable{ focusID },
          m_textSize{ 0.0f },
          m_textPosition{ 0.0f, 0.0f },
          m_updated{ std::move(updated) } {

        SetStringValue();
        CalculateTextSize();
    }

    bool TableCell::HasValue() const {
        return not m_stringValue.empty();
    }

    std::string TableCell::ValueStr() const {
        return m_stringValue;
    }

    void TableCell::CalculateTextSize() {
        m_textSize = m_collider.height / 1.5f;
        float const margin{ (m_collider.height - m_textSize) / 2 };
        m_textPosition = { m_collider.x + m_collider.width * 0.05f, m_collider.y + margin };
    }

    void TableCell::SetBackgroundColor(Color const color) {
        m_backgroundColor = color;
    }
    Color TableCell::GetBackgroundColor() const {
        return m_backgroundColor;
    }

    void TableCell::SetEditable(bool const IsEditable) {
        m_isEditable = IsEditable;
    }
    bool TableCell::IsEditable() const {
        return m_isEditable;
    }
    bool TableCell::IsEnabled() const {
        return m_isEditable;
    }

    Rectangle TableCell::GetCollider() const {
        return m_collider;
    }
    bool TableCell::IsColliding(Vector2 const point) const {
        return CheckCollisionPointRec(point, m_collider);
    }

    void TableCell::SetTextColor(Color const color) {
        m_textColor = color;
    }

    Color TableCell::GetTextColor() const {
        return m_textColor;
    }

    void TableCell::Clicked(Vector2 const& mousePosition, app::AppContext_ty_c appContext) {
        if (not IsEditable()) {
            return;
        }
        if (not IsColliding(mousePosition)) {
            return;
        }

        if (IsA<std::string>()) {
            eve::ShowStringPopupEvent const event{ appContext.languageManager.Text("ui_table_cell_edit_entry_popup"),
                                                   Value<std::string>(),
                                                   [this](std::string value) { SetValue(std::move(value)); } };
            appContext.eventManager.InvokeEvent(event);
        } else if (IsA<utl::usize>()) {
            eve::ShowUSizePopupEvent const event{ appContext.languageManager.Text("ui_table_cell_edit_entry_popup"),
                                                  Value<utl::usize>(),
                                                  [this](utl::usize value) { SetValue(value); } };
            appContext.eventManager.InvokeEvent(event);
        } else if (IsA<double>()) {
            eve::ShowDoublePopupEvent const event{ appContext.languageManager.Text("ui_table_cell_edit_entry_popup"),
                                                   Value<double>(),
                                                   [this](double value) { SetValue(value); } };
            appContext.eventManager.InvokeEvent(event);
        } else if (IsA<Color>()) {
            eve::ShowColorPopupEvent const event{ appContext.languageManager.Text("ui_table_cell_edit_entry_popup"),
                                                  Value<Color>(),
                                                  [this](Color value) { SetValue(value); } };
            appContext.eventManager.InvokeEvent(event);
        } else {
            assert(false and "unreachable");
        }
    }

    void TableCell::SetOnValueChanced(callback_ty callback) {
        m_onValueChanced = std::move(callback);
    };

    void TableCell::CheckAndUpdate(Vector2 const& mousePosition, app::AppContext_ty_c appContext) {

        UIElement::CheckAndUpdate(mousePosition, appContext);
        if (not IsEditable()) {
            return;
        }

        bool shouldEdit{ false };

        if (IsFocused()) {
            if (hlp::IsConfirmInputPressed()) {
                shouldEdit = true;
            }
        }

        if (shouldEdit) {
            Clicked(mousePosition, appContext);
        }
    }

    void TableCell::Render(app::AppContext_ty_c appContext) {
        DrawRectangleRec(m_collider, m_backgroundColor);

        DrawRectangleLinesEx(m_collider, 1.0f, WHITE);

        if (IsA<Color>()) {
            auto const offset{ m_collider.height / 10.0f };
            DrawRectangle(static_cast<int>(m_collider.x + offset),
                          static_cast<int>(m_collider.y + offset),
                          static_cast<int>(m_collider.width - 2.0f * offset),
                          static_cast<int>(m_collider.height - 2.0f * offset),
                          Value<Color>());
        } else {
            DrawTextEx(*appContext.assetManager.GetFont(),
                       m_stringValue.c_str(),
                       m_textPosition,
                       m_textSize,
                       0.0f,
                       m_textColor);
        }
    }

} // namespace uil
