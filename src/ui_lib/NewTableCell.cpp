//
// Purpur Tentakel
// 22.12.2023
//

#include "NewTableCell.hpp"
#include <helper/HInput.hpp>
#include <helper/HPrint.hpp>
#include <utils/Colors.hpp>

namespace uil {

    static auto const wrongDatatypePrint{ [](std::string const& operation) {
        hlp::Print(hlp::PrintType::ERROR, "invalid datatype in Table cell while {}", operation);
    } };

    void NewTableCell::SetStringValue() {
        if (IsA<std::string>()) {
            m_strValue = Value<std::string>();
        } else if (IsA<Color>()) {
            m_strValue = utl::Colors::AsString(Value<Color>());
        } else if (IsA<double>()) {
            m_strValue = std::to_string(Value<double>());
        } else if (IsA<utl::usize>()) {
            m_strValue = std::to_string(Value<utl::usize>());
        } else {
            wrongDatatypePrint("set string value");
        }
    }
    void NewTableCell::Clicked(app::AppContext_ty_c appContext) {
        if (not IsEditable()) {
            return;
        }

        if (IsA<std::string>()) {
            eve::ShowStringInputLinePopupEvent const event{
                appContext.languageManager.Text("ui_table_cell_edit_entry_popup"),
                Value<std::string>(),
                [this](std::string const& value) { this->SetValue(value); }
            };
            appContext.eventManager.InvokeEvent(event);
        } else if (IsA<Color>()) {
            eve::ShowColorInputLinePopupEvent const event{ appContext.languageManager.Text(
                                                                   "ui_table_cell_edit_entry_popup"),
                                                           Value<Color>(),
                                                           [this](Color value) { this->SetValue(value); } };
            appContext.eventManager.InvokeEvent(event);
        } else if (IsA<double>()) {
            eve::ShowDoubleInputLinePopupEvent const event{ appContext.languageManager.Text(
                                                                    "ui_table_cell_edit_entry_popup"),
                                                            Value<double>(),
                                                            [this](double value) { this->SetValue(value); } };
            appContext.eventManager.InvokeEvent(event);
        } else if (IsA<utl::usize>()) {
            eve::ShowUSizeInputLinePopupEvent const event{ appContext.languageManager.Text(
                                                                   "ui_table_cell_edit_entry_popup"),
                                                           Value<utl::usize>(),
                                                           [this](utl::usize value) { this->SetValue(value); } };
            appContext.eventManager.InvokeEvent(event);
        } else {
            wrongDatatypePrint("calling the edit popup");
        }
    }
    void NewTableCell::UpdateTextSize() {
        m_textSize = m_collider.height / 1.5f;
        auto const margin{ (m_collider.height - m_textSize) / 2 };
        m_textPosition = { m_collider.x + (m_collider.width * 0.05f), m_collider.y + margin };
    }
    bool NewTableCell::IsColliding(Vector2 const& point) const {
        return CheckCollisionPointRec(point, m_collider);
    }
    NewTableCell::NewTableCell(utl::usize focusID,
                               Vector2 pos,
                               Vector2 size,
                               Alignment alignment,
                               utl::input_variant_col_ty startValue,
                               uil::NewTable_ty table)
        : UIElement{ pos, size, alignment },
          Focusable{ focusID },
          m_value{ std::move(startValue) },
          m_table{ std::move(table) } {

        SetStringValue();
        UpdateTextSize();
    }

    bool NewTableCell::IsEditable() const {
        return m_isEditable;
    };
    void NewTableCell::SetEditable(bool const editable) {
        m_isEditable = editable;
    }

    float NewTableCell::TextSize() const {
        return m_textSize;
    }
    void NewTableCell::SetTextSize(float const size) {
        m_textSize = size;
    }

    Color NewTableCell::BackgroundColor() const {
        return m_backgroundColor;
    }
    void NewTableCell::SetBackgroundColor(Color const color) {
        m_backgroundColor = color;
    }

    Color NewTableCell::TextColor() const {
        return m_textColor;
    }
    void NewTableCell::SetTextColor(Color const color) {
        m_textColor = color;
    }

    void NewTableCell::SetOnValueChanced(NewTableCell::callback_ty callback) {
        m_onValueChanced = std::move(callback);
    }

    // Focusable
    bool NewTableCell::IsEnabled() const {
        return m_isEditable;
    };
    Rectangle NewTableCell::GetCollider() const {
        return m_collider;
    }
    // UIElement
    void NewTableCell::CheckAndUpdate(Vector2 const& mousePosition, app::AppContext_ty_c appContext) {
        UIElement::CheckAndUpdate(mousePosition, appContext);

        if (not IsEditable()) {
            return;
        }

        auto const edit{ IsFocused() and hlp::IsConfirmInputPressed() };
        if (edit) {
            Clicked(appContext);
        }
    }
    void NewTableCell::Render(app::AppContext_ty_c appContext) {

        DrawRectangleRec(m_collider, m_backgroundColor);
        DrawRectangleLinesEx(m_collider, 1.0f, WHITE);

        if (IsA<Color>()) {
            auto constexpr offset{ 2.0f };
            DrawRectangle(static_cast<int>(m_collider.x + offset),
                          static_cast<int>(m_collider.y + offset),
                          static_cast<int>(m_collider.width - (2.0f * offset)),
                          static_cast<int>(m_collider.height - (2.0f * offset)),
                          Value<Color>());
        } else {
            DrawTextEx(*appContext.assetManager.GetFont(),
                       m_strValue.c_str(),
                       m_textPosition,
                       m_textSize,
                       0.0f,
                       m_textColor);
        }
    }
} // namespace uil


//#include "NewTableCell.hpp"
//#include <alias/AliasCustomRaylib.hpp>

//
//namespace uil {
//    void NewTableCell::setStringValue() {
//        if (isA<std::string>()) {
//            m_strValue = value<std::string>();
//        } else if (isA<utl::usize>()) {
//            m_strValue = std::to_string(value<utl::usize>());
//        } else if (isA<double>()) {
//            m_strValue = std::to_string(value<double>());
//        } else {
//            throw std::runtime_error{ "invalid datatype while setting string value in table cell." };
//        }
//    }
//
//    NewTableCell::index_ty NewTableCell::index() const {
//        return m_indexCallback(*this);
//    }
//
//    void NewTableCell::set_text_offset() {
//        Vector2 constexpr ratio{ 0.05f, 0.25f };
//        cst::Resolution_ty_c resolution{ app::AppContext::GetInstance().GetResolution() };
//
//        m_textRenderOffset = Vector2{
//            m_size.x * ratio.x * resolution.x,
//            m_size.y * ratio.y * resolution.y,
//        };
//    }
//
//    NewTableCell::NewTableCell(utl::usize const ID, Vector2 const pos, Vector2 const size, index_callback_ty callback)
//        : UIElement{ pos, size, Alignment::DEFAULT },
//          Focusable{ ID },
//          m_indexCallback{ std::move(callback) } {
//        set_text_offset();
//    }
//
//    bool NewTableCell::isEmpty() const {
//        return m_strValue.empty();
//    }
//
//    std::string NewTableCell::strValue() const {
//        return m_strValue;
//    }
//
//    void NewTableCell::setValueVariant(utl::input_variant_col_ty const& value) {
//        m_oldValue = m_value;
//        m_value = value;
//        setStringValue();
//        m_callback(*this);
//    }
//
//    void NewTableCell::clear() {
//        assert(false && "need to be implemented");
//    }
//
//    void NewTableCell::setCallback(callback_ty const& callback) {
//        m_callback = callback;
//    }
//
//    bool NewTableCell::IsEnabled() const {
//        return m_isEnabled;
//    }
//
//    void NewTableCell::setEnabled(bool const isEnabled) {
//        m_isEnabled = isEnabled;
//    }
//
//    bool NewTableCell::is_hovered(Vector2 const& mousePosition) const {
//        return CheckCollisionPointRec(mousePosition, m_collider);
//    }
//
//    void NewTableCell::set_hovered(bool const hovered) {
//        m_renderHovered = hovered;
//    }
//
//    Rectangle NewTableCell::GetCollider() const {
//        return m_collider;
//    }
//
//    Vector2 NewTableCell::needed_cell_size(float const text_size) {
//        Vector2 constexpr ratio{ 0.05f, 0.25f };
//        app::AppContext_ty_c appContext{ app::AppContext::GetInstance() };
//
//        auto const text = m_strValue.empty() ? "   " : m_strValue.c_str();
//        auto result{ MeasureTextEx(*appContext.assetManager.GetFont(), text, text_size, 0.0f) };
//
//        result.x = (result.x / (1 - 2 * ratio.x)) / appContext.GetResolution().x;
//        result.y = (result.y / (1 - 2 * ratio.y)) / appContext.GetResolution().y;
//
//        m_textSize = text_size;
//        return result;
//    }
//
//    void NewTableCell::CheckAndUpdate(Vector2 const& mousePosition, app::AppContext_ty_c appContext) {
//        UIElement::CheckAndUpdate(mousePosition, appContext);
//    }
//
//    void NewTableCell::SetSize(Vector2 const size) {
//        UIElement::SetSize(size);
//        set_text_offset();
//    }
//
//    void NewTableCell::Render(app::AppContext_ty_c) {
//        DrawRectangleRec(m_collider, BLACK);
//
//        if (isA<Color>()) {
//            DrawRectangleRec(
//                    { m_collider.x + m_textRenderOffset.x / 2,
//                      m_collider.y + m_textRenderOffset.y / 2,
//                      m_collider.width - m_textRenderOffset.x,
//                      m_collider.height - m_textRenderOffset.y },
//                    value<Color>()
//            );
//        } else {
//            auto const size{ m_textSize < m_collider.height / 2 ? m_textSize : m_collider.height / 2 };
//            DrawTextEx(
//                    *app::AppContext::GetInstance().assetManager.GetFont(),
//                    m_strValue.c_str(),
//                    { m_collider.x + m_textRenderOffset.x, m_collider.y + m_textRenderOffset.y },
//                    size,
//                    0.0f,
//                    WHITE
//            );
//        }
//
//        if (m_renderHovered) {
//            DrawRectangleRec(m_collider, GREY_50);
//            m_renderHovered = false;
//        }
//
//        DrawRectangleLinesEx(m_collider, 1.0f, WHITE);
//    }
//} // namespace uil
