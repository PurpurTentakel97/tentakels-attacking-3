//
// Purpur Tentakel
// 06.10.2022
//

#include "Line.hpp"


namespace uil {
    Line::Line(Vector2 const start, Vector2 const end, float const thick, Color const color)
        : UIElement{ start, end - start, Alignment::DEFAULT },
          m_start{ start },
          m_end{ end },
          m_thick{ thick },
          m_color{ color } { }

    void Line::Render(app::AppContext_ty_c) {
        DrawLineEx(
                Vector2(m_collider.x, m_collider.y),
                Vector2(m_collider.x + m_collider.width, m_collider.y + m_collider.height),
                m_thick,
                m_color
        );
    }

    void Line::Update() {
        SetPosition(m_start);
        SetSize(m_end - m_start);
    }

    Vector2 Line::GetStart() const {
        return m_start;
    }

    void Line::SetStart(Vector2 const start) {
        m_start = start;
    }

    Vector2 Line::GetEnd() const {
        return m_end;
    }

    void Line::SetEnd(Vector2 const end) {
        m_end = end;
    }

    float Line::GetThick() const {
        return m_thick;
    }

    void Line::SetThick(float const thick) {
        m_thick = thick;
    }

    Color Line::GetColor() const {
        return m_color;
    }

    void Line::SetColor(Color const color) {
        m_color = color;
    }
} // namespace uil
