//
// Purpur Tentakel
// 07.04.2023
//

#include "TableCellAbstract.hpp"


namespace uil {
    AbstractTableCell::AbstractTableCell(Vector2 pos, Vector2 size, Alignment alignment, unsigned int focusID)
        : UIElement{ pos, size, alignment },
          Focusable{ focusID },
          m_textSize{ 0.0f },
          m_textPosition{ 0.0f, 0.0f } { }

    void AbstractTableCell::SetBackgroundColor(Color color) {
        m_backgroundColor = color;
    }
    Color AbstractTableCell::GetBackgroundColor() const {
        return m_backgroundColor;
    }

    void AbstractTableCell::SetEditable(bool IsEditable) noexcept {
        m_isEditable = IsEditable;
    }
    bool AbstractTableCell::IsEditable() const noexcept {
        return m_isEditable;
    }
    bool AbstractTableCell::IsEnabled() const noexcept {
        return m_isEditable;
    }

    Rectangle AbstractTableCell::GetCollider() const noexcept {
        return m_collider;
    }
    bool AbstractTableCell::IsColliding(Vector2 point) const {
        return CheckCollisionPointRec(point, m_collider);
    }

    void AbstractTableCell::SetTextColor(Color color) {
        m_textColor = color;
    }
    Color AbstractTableCell::GetTextColor() const {
        return m_textColor;
    }

    void AbstractTableCell::Render(app::AppContext_ty_c) {

        DrawRectangleRec(m_collider, m_backgroundColor);

        DrawRectangleLinesEx(m_collider, 1.0f, WHITE);
    }
} // namespace uil
