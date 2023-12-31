//
// Purpur Tentakel
// 22.12.2023
//

#pragma once

#include "Focusable.hpp"
#include "UIElement.hpp"
#include <alias/AliasUtils.hpp>
#include <functional>
#include <helper/HConcepts.hpp>
#include <string>
#include <type_traits>
#include <variant>

namespace uil {
    class NewTableCell final : public UIElement, public Focusable {
    public:
        using variant_ty = std::variant<int, double, std::monostate, std::string, Color>;
        using callback_ty = std::function<void(NewTableCell&)>;
        using index_ty = std::pair<utl::usize, utl::usize>;
        using index_callback_ty = std::function<index_ty(NewTableCell const&)>;

    private:
        std::string m_strValue{};
        variant_ty m_value{ std::monostate{} };
        variant_ty m_oldValue{ std::monostate{} };
        callback_ty m_callback{ [](NewTableCell&) {} };
        index_callback_ty m_indexCallback;

        Vector2 m_textRenderOffset{ 0.0f, 0.0f };
        float m_textSize{ 50.0f };
        bool m_isEnabled{ true };
        bool m_renderHovered{ false };

        void setStringValue();

        template<typename T>
        [[nodiscard]] T specificValue(variant_ty const& value) const {
            if (auto const* ptr = std::get_if<T>(&value)) {
                return *ptr;
            } else {
                throw std::runtime_error{ "type mismatch while getting value of Table Cell" };
            }
        }

        [[nodiscard]] index_ty index() const;

        void set_text_offset();

    public:
        NewTableCell(unsigned int ID, Vector2 pos, Vector2 size, index_callback_ty callback);

        [[nodiscard]] bool isEmpty() const;

        template<typename T>
        [[nodiscard]] constexpr bool isA() const {
            return std::holds_alternative<T>(m_value);
        }

        template<typename T>
        [[nodiscard]] constexpr bool isAOld() const {
            return std::holds_alternative<T>(m_oldValue);
        }

        template<typename T>
        [[nodiscard]] T value() const {
            return specificValue<T>(m_value);
        }
        template<typename T>
        [[nodiscard]] T oldValue() const {
            return specificValue<T>(m_oldValue);
        }

        [[nodiscard]] std::string strValue() const;

        template<CellValueType T>
        void setValue(T const& value) {
            m_oldValue = m_value;
            m_value = value;
            setStringValue();
            m_callback(*this);
        }

        void setValueVariant(variant_ty const& value);

        void clear();

        void setCallback(callback_ty const& callback);

        [[nodiscard]] bool is_hovered(Vector2 const& mousePosition) const;

        void set_hovered(bool hovered);

        [[nodiscard]] Vector2 needed_cell_size(float text_size);

        // Focusable
        [[nodiscard]] bool IsEnabled() const override;

        void setEnabled(bool isEnabled);

        [[nodiscard]] Rectangle GetCollider() const override;

        // UIElement
        void SetSize(Vector2 size) override;

        void CheckAndUpdate(Vector2 const& mousePosition, app::AppContext_ty_c appContext) override;

        void Render(app::AppContext_ty_c appContext) override;
    };
} // namespace uil
