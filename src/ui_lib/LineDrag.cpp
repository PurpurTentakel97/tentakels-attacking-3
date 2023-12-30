//
// Purpur Tentakel
// 30.05.2023
//

#include "LineDrag.hpp"
#include <alias/AliasCustomRaylib.hpp>
#include <app/AppContext.hpp>


namespace uil {
    LineDrag::LineDrag(float const thick, Color const color, std::function<void(Vector2, Vector2)> callback)
		: UIElement{ {0.0f,0.0f}, {0.0f,0.0f}, Alignment::DEFAULT },
		m_start{ 0.0f,0.0f }, m_end{ 0.0f,0.0f }, m_thick{ thick }, m_color{ color }, m_callback{ std::move(callback) } { }

    Vector2 LineDrag::GetStart() const {
        return m_start;
    }

    Vector2 LineDrag::GetEnd() const {
        return m_end;
    }

    void LineDrag::SetThick(float const thick) {
        m_thick = thick;
    }

    float LineDrag::GetThick() const {
        return m_thick;
    }

    void LineDrag::SetColor(Color const color) {
        m_color = color;
    }

    Color LineDrag::GetColor() const {
        return m_color;
    }

    void LineDrag::SetCallback(std::function<void(Vector2, Vector2)> callback) {
        m_callback = std::move(callback);
    }

    void LineDrag::ClearCallback() {
        m_callback = [](Vector2, Vector2) {};
    }

    void LineDrag::CheckAndUpdate(Vector2 const& mousePosition, app::AppContext_ty_c appContext) {
        cst::Resolution_ty_c resolution{ appContext.GetResolution() };
        if (m_render) {
            if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) {
                m_render = false;
                m_callback(m_start, m_end);
            } else {
                m_end = { mousePosition.x / resolution.x, mousePosition.y / resolution.y };
                SetSize(m_end - m_start);
            }
        } else {
            if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
                m_render = true;
                m_start = { mousePosition.x / resolution.x, mousePosition.y / resolution.y };
                m_end = m_start;
                SetPosition(m_start);
                SetSize(m_end - m_start);
            }
        }
    }

    void LineDrag::Render(app::AppContext_ty_c) {
        if (m_render) {
            DrawLineEx(
                    Vector2{ m_collider.x, m_collider.y },
                    Vector2{ m_collider.x + m_collider.width, m_collider.y + m_collider.height },
                    m_thick,
                    m_color
            );
        }
    }
} // namespace uil
