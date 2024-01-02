//
// Purpur Tentakel
// 01.01.2024
//

#pragma once

#include "Focusable.hpp"
#include "UIElement.hpp"

#include "alias/AliasUtils.hpp"
#include <cassert>
#include <string>


namespace uil {
    class InputLine final : public UIElement, public Focusable {
        using on_enter_callback_ty = std::function<void(InputLine&)>;
        using on_value_chanced_callback_ty = std::function<void(InputLine&)>;

    private:
        enum class KeyType {
            FIRST_NUMBER,
            LAST_NUMBER,
            FIRST_CHAR,
            LAST_CHAR,
            DOT,
            COMMA,
        };
        bool m_isEnabled{ true };
        bool m_isClearByFocus{ false };
        bool m_isClearNextInput{ false };
        bool m_alreadyCleared{ false };

        utl::usize m_charLimit;
        utl::input_variant_ty m_value;
        utl::input_variant_ty m_valueLastFrame{};
        utl::input_variant_ty m_oldValue;
        std::string m_strValue{};
        std::string m_placeholderText{};

        double m_currentBackspacePressTime{ 0.0 };
        double m_backspacePressTime{ 0.5 };
        on_enter_callback_ty m_onEnter{ [](InputLine&) {} };
        on_value_chanced_callback_ty m_onValueChanced{ [](InputLine&) {} };

        static inline std::unordered_map<KeyType, utl::usize> const m_keyLockup{
            { KeyType::FIRST_NUMBER,  48 },
            {  KeyType::LAST_NUMBER,  57 },
            {   KeyType::FIRST_CHAR,  32 },
            {    KeyType::LAST_CHAR, 126 },
            {        KeyType::COMMA,  44 },
            {          KeyType::DOT,  46 },
        };

        void UpdateValue();

        [[nodiscard]] bool AddChar(utl::usize key);

        void RemoveChar();

        [[nodiscard]] bool IsValidKey(utl::usize key) const;

        void UpdateStringValue();

    public:
        InputLine(
                utl::usize focusID,
                Vector2 pos,
                Vector2 size,
                Alignment alignment,
                utl::input_variant_ty const& startValue
        );

        InputLine(
                utl::usize focusID,
                Vector2 pos,
                Vector2 size,
                Alignment alignment,
                utl::input_variant_ty const& startValue,
                utl::usize cherLimit
        );

        // values
        void SetPlaceholderText(std::string placeholderText);

        [[nodiscard]] std::string PlaceholderText() const;

        [[nodiscard]] bool HasValue() const;

        [[nodiscard]] bool HasValueChanced() const;

        template<utl::InputValueType T>
        [[nodiscard]] bool IsA() const {
            return std::holds_alternative<T>(m_value);
        }

        template<utl::InputValueType T>
        [[nodiscard]] bool isAOld() const {
            return std::holds_alternative<T>(m_oldValue);
        }

        template<utl::InputValueType T>
        void SetValue(T value) {
            if (not IsA<T>()) {
                throw std::runtime_error("types not matching while setting a new value for input line");
            }
            m_oldValue = m_value;
            m_value = value;
            UpdateStringValue();
            m_onValueChanced(*this);
        }

        template<utl::InputValueType T>
        void ChangeValueType(T value) {
            m_oldValue = m_value;
            m_value = value;
            UpdateStringValue();
            m_onValueChanced(*this);
        }

        template<utl::InputValueType T>
        T Value() const {
            if (not IsA<T>()) {
                throw std::runtime_error("type mismatch in input line while getting value");
            }
            return std::get<T>(m_value);
        }

        template<utl::InputValueType T>
        T GetOldValue() const {
            auto const value = std::get_if<T>(m_oldValue);
            if (not value) {
                throw std::runtime_error("type mismatch in input line while getting old value");
            }
            return value;
        }

        [[nodiscard]] std::string GetStrValue() const;

        void Clear();

        // callbacks
        void SetOnEnter(on_enter_callback_ty callback);

        void SetOnValueChanced(on_value_chanced_callback_ty callback);

        // configuration
        [[nodiscard]] bool IsClearByFocus() const;

        void SetClearByFocus(bool clear);

        [[nodiscard]] bool IsClearByNextInput() const;

        void SetClearByNextInput(bool clear);

        void SetEnabled(bool enabled);

        [[nodiscard]] double BackspacePressTime() const;

        void SetBackspacePressTime(double time);

        [[nodiscard]] utl::usize CharLimit() const;

        void SetCharLimit(utl::usize limit);

        // Focusable
        [[nodiscard]] bool IsEnabled() const override;

        [[nodiscard]] Rectangle GetCollider() const override;

        // UI Element
        void CheckAndUpdate(Vector2 const& mousePosition, app::AppContext_ty_c appContext) override;

        void Render(app::AppContext_ty_c appContext) override;
    };
} // namespace uil
