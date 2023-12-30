//
// Purpur Tentakel
// 22.12.2023
//

#include "NewTableCell.hpp"
#include <alias/AliasCustomRaylib.hpp>


namespace uil {
    void NewTableCell::setStringValue() {
        if (isA<std::string>()) {
            m_strValue = value<std::string>();
        } else if (isA<int>()) {
            m_strValue = std::to_string(value<int>());
        } else if (isA<double>()) {
            m_strValue = std::to_string(value<double>());
        } else if (isA<Color>() or isA<std::monostate>()) {
            m_strValue.clear();
        } else {
            throw std::runtime_error{ "invalid datatype while setting string value in table cell." };
        }
    }

    NewTableCell::index_ty NewTableCell::index() const {
        return m_indexCallback(*this);
    }

    void NewTableCell::set_text_offset() {
        Vector2 constexpr ratio{ 0.05f, 0.25f };
        cst::Resolution_ty_c resolution{ app::AppContext::GetInstance().GetResolution() };

        m_textRenderOffset = Vector2{
            m_size.x * ratio.x * resolution.x,
            m_size.y * ratio.y * resolution.y,
        };
    }

    NewTableCell::NewTableCell(unsigned int const ID, Vector2 const pos, Vector2 const size, index_callback_ty callback)
        : UIElement{ pos, size, Alignment::DEFAULT },
          Focusable{ ID },
          m_indexCallback{ std::move(callback) } {
        set_text_offset();
    }

    bool NewTableCell::isEmpty() const {
        return isA<std::monostate>();
    }

    std::string NewTableCell::strValue() const {
        return m_strValue;
    }

    void NewTableCell::setValueVariant(variant_ty const& value) {
        m_oldValue = m_value;
        m_value = value;
        setStringValue();
        m_callback(*this);
    }

    void NewTableCell::clear() {
        setValue(std::monostate());
    }

    void NewTableCell::setCallback(callback_ty const& callback) {
        m_callback = callback;
    }

    bool NewTableCell::IsEnabled() const {
        return m_isEnabled;
    }

    void NewTableCell::setEnabled(bool const isEnabled) {
        m_isEnabled = isEnabled;
    }

    bool NewTableCell::is_hovered(Vector2 const& mousePosition) const {
        return CheckCollisionPointRec(mousePosition, m_collider);
    }

    void NewTableCell::set_hovered(bool const hovered) {
        m_renderHovered = hovered;
    }

    Rectangle NewTableCell::GetCollider() const {
        return m_collider;
    }

    Vector2 NewTableCell::needed_cell_size(float const text_size) {
        Vector2 constexpr ratio{ 0.05f, 0.25f };
        app::AppContext_ty_c appContext{ app::AppContext::GetInstance() };

        auto const text = m_strValue.empty() ? "   " : m_strValue.c_str();
        auto result{ MeasureTextEx(*appContext.assetManager.GetFont(), text, text_size, 0.0f) };

        result.x = (result.x / (1 - 2 * ratio.x)) / appContext.GetResolution().x;
        result.y = (result.y / (1 - 2 * ratio.y)) / appContext.GetResolution().y;

        m_textSize = text_size;
        return result;
    }

    void NewTableCell::CheckAndUpdate(Vector2 const& mousePosition, app::AppContext_ty_c appContext) {
        UIElement::CheckAndUpdate(mousePosition, appContext);
    }

    void NewTableCell::SetSize(Vector2 const size) {
        UIElement::SetSize(size);
        set_text_offset();
    }

    void NewTableCell::Render(app::AppContext_ty_c) {
        DrawRectangleRec(m_collider, BLACK);

        if (isA<std::monostate>()) { /*nothing to do here*/
        } else if (isA<Color>()) {
            DrawRectangleRec(
                    { m_collider.x + m_textRenderOffset.x / 2,
                      m_collider.y + m_textRenderOffset.y / 2,
                      m_collider.width - m_textRenderOffset.x,
                      m_collider.height - m_textRenderOffset.y },
                    value<Color>()
            );
        } else {
            auto const size{ m_textSize < m_collider.height / 2 ? m_textSize : m_collider.height / 2 };
            DrawTextEx(
                    *app::AppContext::GetInstance().assetManager.GetFont(),
                    m_strValue.c_str(),
                    { m_collider.x + m_textRenderOffset.x, m_collider.y + m_textRenderOffset.y },
                    size,
                    0.0f,
                    WHITE
            );
        }

        if (m_renderHovered) {
            DrawRectangleRec(m_collider, GREY_50);
            m_renderHovered = false;
        }

        DrawRectangleLinesEx(m_collider, 1.0f, WHITE);
    }
} // namespace uil
