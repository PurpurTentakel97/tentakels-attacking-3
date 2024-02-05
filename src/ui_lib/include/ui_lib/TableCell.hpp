//
// Purpur Tentakel
// 23.04.2023
//

#pragma once

#include "Focusable.hpp"
#include "UIElement.hpp"
#include <alias/AliasUtils.hpp>
#include <app/AppContext.hpp>
#include <event/EventsUI.hpp>
#include <helper/HInput.hpp>
#include <helper/HPrint.hpp>
#include <utils/Colors.hpp>
#include <utils/Concepts.hpp>


namespace uil {
    class TableCell final : public UIElement, public Focusable {
    public:
        using callback_ty = std::function<void(TableCell&)>;

    private:
        bool m_isEditable{ true };
        Color m_backgroundColor{ BLACK };
        float m_textSize{ 0.0f };
        Vector2 m_textPosition{ 0.0f, 0.0f };
        Color m_textColor{ WHITE };
        utl::input_variant_col_ty m_value{ "" };
        utl::input_variant_col_ty m_oldValue{ "" };
        std::string m_stringValue{};
        callback_ty m_updated{ [](TableCell&) {} };
        callback_ty m_onValueChanced{ [](TableCell&) {} };


        void CallCallbacks();

        void SetStringValue();

    public:
        TableCell(Vector2 pos, Vector2 size, Alignment alignment, utl::usize focusID, callback_ty updated);


        template<utl::InputValueTypeCol T>
        [[nodiscard]] bool IsA() const {
            return std::holds_alternative<T>(m_value);
        }

        template<utl::InputValueTypeCol T>
        [[nodiscard]] bool IsAOld() const {
            return std::holds_alternative<T>(m_oldValue);
        }

        [[nodiscard]] bool HasValue() const;

        template<utl::InputValueTypeCol T>
        [[nodiscard]] T Value() const {
            if (not IsA<T>()) {
                throw std::runtime_error("type mismatch while setting a new value into Table cell.");
            }
            return std::get<T>(m_value);
        }

        template<utl::InputValueTypeCol T>
        [[nodiscard]] T ValueOld() const {
            if (not IsA<T>()) {
                throw std::runtime_error("type mismatch while setting a new value into Table cell.");
            }
            return std::get<T>(m_oldValue);
        }

        [[nodiscard]] std::string ValueStr() const;

        template<utl::InputValueTypeCol T>
        void SetValue(T const value) {
            if (not IsA<T>()) {
                throw std::runtime_error("type mismatch while setting a new value into Table cell.");
            }
            SetType(value);
        }

        template<utl::InputValueTypeCol T>
        void SetType(T const value) {
            m_oldValue = m_value;
            m_value    = value;
            SetStringValue();
            CallCallbacks();
        }

        void CalculateTextSize();

        void SetBackgroundColor(Color color);
        [[nodiscard]] Color GetBackgroundColor() const;

        void SetTextColor(Color color);
        [[nodiscard]] Color GetTextColor() const;

        void SetEditable(bool IsEditable);
        [[nodiscard]] bool IsEditable() const;


        [[nodiscard]] bool IsColliding(Vector2 point) const;

        void Clicked(Vector2 const& mousePosition, app::AppContext_ty_c appContext);

        void SetOnValueChanced(callback_ty callback);

        // UIElement
        void CheckAndUpdate(Vector2 const& mousePosition, app::AppContext_ty_c appContext) override;

        void Render(app::AppContext_ty_c appContext) override;

        // focusable
        [[nodiscard]] bool IsEnabled() const override;

        [[nodiscard]] Rectangle GetCollider() const override;
    };


} // namespace uil
