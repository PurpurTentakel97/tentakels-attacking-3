//
// Purpur Tentakel
// 22.12.2023
//

#pragma once

#include "Focusable.hpp"
#include "NewTable.hpp"
#include "UIElement.hpp"
#include <alias/AliasUiLib.hpp>
#include <alias/AliasUtils.hpp>
#include <functional>
#include <string>
#include <utils/Concepts.hpp>


namespace uil {
    class NewTableCell final : public UIElement, public Focusable {
    public:
        friend class NewTable;

    public:
        using callback_ty = std::function<void(NewTableCell&)>;

    private:
        utl::input_variant_col_ty m_value;
        utl::input_variant_col_ty m_oldValue{};
        std::string m_strValue{};
        bool m_isEditable{ true };
        Color m_backgroundColor{ BLACK };
        Color m_textColor{ WHITE };
        float m_textSize{ 0.0f };
        Vector2 m_textPosition{ 0.0f, 0.0f };
        callback_ty m_onValueChanced{ [](NewTableCell&) {} };
        uil::NewTable_ty m_table;

        void SetStringValue();

        void Clicked(app::AppContext_ty_c appContext);

        void UpdateTextSize();

        [[nodiscard]] bool IsColliding(Vector2 const& point) const;

    public:
        NewTableCell(utl::usize focusID,
                     Vector2 pos,
                     Vector2 size,
                     Alignment alignment,
                     utl::input_variant_col_ty startValue,
                     uil::NewTable_ty table);

        // value
        template<utl::InputValueTypeCol T>
        [[nodiscard]] bool IsA() const {
            return std::holds_alternative<T>(m_value);
        }

        template<utl::InputValueTypeCol T>
        [[nodiscard]] bool IsAOld() const {
            return std::holds_alternative<T>(m_oldValue);
        }

        [[nodiscard]] std::string ValueStr() const {
            return m_strValue;
        }

        template<utl::InputValueTypeCol T>
        [[nodiscard]] T Value() const {
            if (not IsA<T>()) {
                throw std::runtime_error{ "wrong datatype while accessing current value of cell" };
            }
            return std::get<T>(m_value);
        }

        template<utl::InputValueTypeCol T>
        [[nodiscard]] T ValueOld() const {
            if (not IsAOld<T>()) {
                throw std::runtime_error{ "wrong datatype while accessing old value of cell" };
            }
            return std::get<T>(m_oldValue);
        }

        template<utl::InputValueTypeCol T>
        void SetValue(T const value) {
            if (not IsA<T>()) {
                throw std::runtime_error{ "wrong datatype while setting a new value in cell" };
            }
            m_oldValue = m_value;
            m_value    = value;
            m_onValueChanced(*this);
            m_table->ResizeTable();
        }

        template<utl::InputValueTypeCol T>
        void SetNewType(T const value) {
            m_oldValue = m_value;
            m_value    = value;
            m_onValueChanced(*this);
            m_table->ResizeTable();
        }

        // getter setter
        [[nodiscard]] bool IsEditable() const;
        void SetEditable(bool editable);

        [[nodiscard]] float TextSize() const;
        void SetTextSize(float size);

        [[nodiscard]] Color BackgroundColor() const;
        void SetBackgroundColor(Color color);

        [[nodiscard]] Color TextColor() const;
        void SetTextColor(Color color);

        void SetOnValueChanced(callback_ty callback);

        // Focusable
        [[nodiscard]] bool IsEnabled() const override;

        [[nodiscard]] Rectangle GetCollider() const override;

        // UIElement
        void CheckAndUpdate(Vector2 const& mousePosition, app::AppContext_ty_c appContext) override;

        void Render(app::AppContext_ty_c appContext) override;
    };
} // namespace uil

//#include "Focusable.hpp"
//#include "UIElement.hpp"
//#include "utils/Concepts.hpp"
//#include <alias/AliasUtils.hpp>
//#include <functional>
//#include <string>
//#include <type_traits>
//#include <variant>
//
//namespace uil {
//    class NewTableCell final : public UIElement, public Focusable {
//    public:
//        using callback_ty = std::function<void(NewTableCell&)>;
//        using index_ty = std::pair<utl::usize, utl::usize>;
//        using index_callback_ty = std::function<index_ty(NewTableCell const&)>;
//
//    private:
//        std::string m_strValue{};
//        utl::input_variant_col_ty m_value{ "" };
//        utl::input_variant_col_ty m_oldValue{ "" };
//        callback_ty m_callback{ [](NewTableCell&) {} };
//        index_callback_ty m_indexCallback;
//
//        Vector2 m_textRenderOffset{ 0.0f, 0.0f };
//        float m_textSize{ 50.0f };
//        bool m_isEnabled{ true };
//        bool m_renderHovered{ false };
//
//        void setStringValue();
//
//        template<typename T>
//        [[nodiscard]] T specificValue(utl::input_variant_col_ty const& value) const {
//            if (auto const* ptr = std::get_if<T>(&value)) {
//                return *ptr;
//            } else {
//                throw std::runtime_error{ "type mismatch while getting value of Table Cell" };
//            }
//        }
//
//        [[nodiscard]] index_ty index() const;
//
//        void set_text_offset();
//
//    public:
//        NewTableCell(utl::usize ID, Vector2 pos, Vector2 size, index_callback_ty callback);
//
//        [[nodiscard]] bool isEmpty() const;
//
//        template<typename T>
//        [[nodiscard]] constexpr bool isA() const {
//            return std::holds_alternative<T>(m_value);
//        }
//
//        template<typename T>
//        [[nodiscard]] constexpr bool isAOld() const {
//            return std::holds_alternative<T>(m_oldValue);
//        }
//
//        template<typename T>
//        [[nodiscard]] T value() const {
//            return specificValue<T>(m_value);
//        }
//        template<typename T>
//        [[nodiscard]] T oldValue() const {
//            return specificValue<T>(m_oldValue);
//        }
//
//        [[nodiscard]] std::string strValue() const;
//
//        template<utl::InputValueTypeCol T>
//        void setValue(T const& value) {
//            m_oldValue = m_value;
//            m_value = value;
//            setStringValue();
//            m_callback(*this);
//        }
//
//        void setValueVariant(utl::input_variant_col_ty const& value);
//
//        void clear();
//
//        void setCallback(callback_ty const& callback);
//
//        [[nodiscard]] bool is_hovered(Vector2 const& mousePosition) const;
//
//        void set_hovered(bool hovered);
//
//        [[nodiscard]] Vector2 needed_cell_size(float text_size);
//
//        // Focusable
//        [[nodiscard]] bool IsEnabled() const override;
//
//        void setEnabled(bool isEnabled);
//
//        [[nodiscard]] Rectangle GetCollider() const override;
//
//        // UIElement
//        void SetSize(Vector2 size) override;
//
//        void CheckAndUpdate(Vector2 const& mousePosition, app::AppContext_ty_c appContext) override;
//
//        void Render(app::AppContext_ty_c appContext) override;
//    };
//} // namespace uil
