//
// Purpur Tentakel
// 06.09.2022
//

#pragma once

#include "Focusable.hpp"
#include "UIElement.hpp"
#include <alias/AliasUtils.hpp>
#include <app/AppContext.hpp>
#include <functional>
#include <helper/HInput.hpp>
#include <helper/HTextProcessing.hpp>
#include <string>

namespace uil {
    template<class T>
    class InputLine final : public UIElement, public Focusable {
    protected:
        bool m_isEnabled{ true };
        bool m_shouldClearByFocus{ false };
        bool m_isClearNextInput{ false };
        bool m_alreadyCleared{ false };
        utl::usize m_charLimit;
        std::string m_value;
        std::string m_oldValue;
        std::string m_placeholderText;
        double m_backspacePressTime{ 0.0 };
        std::function<void()> m_onEnter{ []() {} };
        std::function<void()> m_onValueChanced{ []() {} };

        bool AddChar(int const key) {
            bool const validAdd{ m_charLimit > m_value.size() };

            if (validAdd) {
                m_value += static_cast<char>(key);

                eve::PlaySoundEvent const event{ app::SoundType::TEXT };
                app::AppContext::GetInstance().eventManager.InvokeEvent(event);

                m_onValueChanced();
            }

            return validAdd;
        }

        void RemoveChar() {
            if (not m_value.empty()) {
                m_value.pop_back();

                eve::PlaySoundEvent const event{ app::SoundType::TEXT };
                app::AppContext::GetInstance().eventManager.InvokeEvent(event);

                m_onValueChanced();
            }
        }

        [[nodiscard]] bool IsValidKey(int const key) = delete;

    public:
        InputLine(
                utl::usize const focusID,
                Vector2 const pos,
                Vector2 const size,
                Alignment const alignment,
                utl::usize const charLimit
        )
            : UIElement{ pos, size, alignment },
              Focusable{ focusID },
              m_charLimit{ charLimit } { }

        void CheckAndUpdate(Vector2 const& mousePosition, app::AppContext_ty_c appContext) override {

            UIElement::CheckAndUpdate(mousePosition, appContext);

            if (!m_isEnabled) {
                return;
            }

            bool const hover{ CheckCollisionPointRec(mousePosition, m_collider) };
            bool const validSelect{ !IsFocused() and hover and IsMouseButtonPressed(MOUSE_LEFT_BUTTON) };

            if (validSelect) {
                eve::SelectFocusElementEvent const event{ this };
                appContext.eventManager.InvokeEvent(event);
            }

            if (!IsFocused()) {
                m_alreadyCleared = false;
                return;
            }

            bool const enter{ hlp::IsOnlyEnterConfirmInputPressed() };
            if (enter) {
                m_onEnter();
            }

            if (IsKeyPressed(KEY_BACKSPACE)) {
                RemoveChar();
                m_backspacePressTime = GetTime();
                return;
            }

            if (IsKeyDown(KEY_BACKSPACE)) {
                if (m_backspacePressTime < GetTime() - 0.5) {
                    RemoveChar();
                    return;
                }
            }

            while (true) {
                auto const key{ GetCharPressed() };

                if (key <= 0) {
                    break;
                }

                if (not m_alreadyCleared) {
                    if (m_shouldClearByFocus and GotFocused()) {
                        Clear();
                        m_alreadyCleared = true;
                    }
                }
                if (m_isClearNextInput) {
                    Clear();
                    m_isClearNextInput = false;
                }

                if (!IsValidKey(key)) {
                    continue;
                }

                if (!AddChar(key)) {
                    eve::ShowMessagePopUpEvent const event{
                        appContext.languageManager.Text("ui_input_line_popup_max_input_title"),
                        appContext.languageManager.Text("ui_input_line_popup_max_input_text"),
                        []() {}
                    };
                    appContext.eventManager.InvokeEvent(event);
                    break;
                }
            }
        }

        void Render(app::AppContext_ty_c appContext) override {

            // Update here to make sure its after call of HasValueChanced();
            m_oldValue = m_value;

            DrawRectangleRec(m_collider, GREY_100);

            if (m_isEnabled) {
                DrawRectangleLinesEx(m_collider, 2.0f, PURPLE);
            }

            float const posX{ m_collider.x + 10.0f };
            float const posY{ m_collider.y + m_collider.height * 0.1f };
            float const fontSize{ m_collider.height * 0.8f };
            std::string printableInput{};

            if (not m_value.empty()) {
                printableInput = hlp::GetPrintableTextInCollider(m_value, fontSize, m_collider, appContext);
                DrawTextEx(
                        *(appContext.assetManager.GetFont()),
                        printableInput.c_str(),
                        Vector2(posX, posY),
                        fontSize,
                        0,
                        WHITE
                );
            } else {
                std::string const printablePlaceholder{
                    hlp::GetPrintablePlaceholderTextInCollider(m_placeholderText, fontSize, m_collider, appContext)
                };
                DrawTextEx(
                        *(appContext.assetManager.GetFont()),
                        printablePlaceholder.c_str(),
                        Vector2(posX, posY),
                        fontSize,
                        0,
                        GRAY
                );
            }


            if (IsFocused()) {
                utl::usize const time{ static_cast<utl::usize>(GetTime() * 2.0) };
                Vector2 textLength =
                        MeasureTextEx(*(appContext.assetManager.GetFont()), printableInput.c_str(), fontSize, 0.0f);

                if (time % 2 == 0) {
                    DrawTextEx(
                            *(appContext.assetManager.GetFont()),
                            &cst::TextProcessing::cursor,
                            Vector2(posX + cst::TextProcessing::cursorOffset + textLength.x,
                                    posY + m_collider.height * 0.05f),
                            fontSize,
                            0,
                            PURPLE
                    );
                }
            }
        }

        void SetPlaceholderText(std::string placeholderText) {
            m_placeholderText = std::move(placeholderText);
        }

        void SetValue(T const value) {
            m_value = std::to_string(value);
            m_onValueChanced();
        }

        void ExtendValue(T const& value) {
            m_value += std::to_string(value);
            m_onValueChanced();
        }

        [[nodiscard]] T GetValue() = delete;

        void Clear() {
            m_value.clear();
            m_onValueChanced();
        }


        [[nodiscard]] Rectangle GetCollider() const override {
            return UIElement::GetCollider();
        }

        [[nodiscard]] bool HasValue() const {
            return !m_value.empty();
        }

        [[nodiscard]] bool HasValueChanced() const {
            return m_value != m_oldValue;
        }

        void SetOnEnter(std::function<void()> onEnter) {
            m_onEnter = std::move(onEnter);
        }

        void SetOnValueChanced(std::function<void()> onValueChanged) {
            m_onValueChanced = std::move(onValueChanged);
        }

        void SetShouldClearByFocus(bool const isShouldClearByFocus) {
            m_shouldClearByFocus = isShouldClearByFocus;
        }

        [[nodiscard]] bool IsShouldClearByFocus() const {
            return m_shouldClearByFocus;
        }

        void ClearByNextInput() {
            m_isClearNextInput = true;
        }

        [[nodiscard]] bool IsEnabled() const override {
            return m_isEnabled;
        }

        void SetEnabled(bool const isEnabled) {
            m_isEnabled = isEnabled;
        }
    };


    template<>
    inline bool InputLine<int>::IsValidKey(int const key) {
        return key >= 48 and key <= 57;
    }

    template<>
    inline bool InputLine<float>::IsValidKey(int const key) {
        bool valid{ (key >= 48 and key <= 57) // numbers
                    or key == 44              // comma
                    or key == 46 };           // dot

        //check for multiple commas/dots
        if ('.' == key or ',' == key) {
            if (m_value.empty()) {
                valid = false;
            }

            for (char const& c : m_value) {
                if ('.' == c or ',' == c) {
                    valid = false;
                    break;
                }
            }
        }

        return valid;
    }

    template<>
    inline bool InputLine<double>::IsValidKey(int const key) {
        bool valid{ (key >= 48 and key <= 57) // numbers
                    or key == 44              // comma
                    or key == 46 };           // dot

        //check for multiple commas/dots
        if ('.' == key or ',' == key) {
            if (m_value.empty()) {
                valid = false;
            }

            for (char const& c : m_value) {
                if ('.' == c or ',' == c) {
                    valid = false;
                    break;
                }
            }
        }

        return valid;
    }

    template<>
    inline bool InputLine<std::string>::IsValidKey(int const key) {
        return key >= 32 and key <= 126;
    }

    template<>
    [[nodiscard]] inline int InputLine<int>::GetValue() {
        hlp::StripString(m_value);
        if (m_value.empty()) {
            return 0;
        }
        return std::stoi(m_value);
    }

    template<>
    [[nodiscard]] inline float InputLine<float>::GetValue() {
        hlp::StripString(m_value);
        if (m_value.empty()) {
            return 0.0f;
        }
        for (char& c : m_value) {
            if (c == ',') {
                c = '.';
                break;
            }
        }
        return std::stof(m_value);
    }

    template<>
    [[nodiscard]] inline double InputLine<double>::GetValue() {
        hlp::StripString(m_value);
        if (m_value.empty()) {
            return 0.0;
        }
        for (char& c : m_value) {
            if (c == ',') {
                c = '.';
                break;
            }
        }
        return std::stod(m_value);
    }

    template<>
    [[nodiscard]] inline std::string InputLine<std::string>::GetValue() {
        hlp::StripString(m_value);
        return m_value;
    }

    template<>
    inline void InputLine<std::string>::SetValue(std::string value) {
        m_value = std::move(value);
        m_onValueChanced();
    }

    template<>
    inline void InputLine<std::string>::ExtendValue(std::string const& value) {
        m_value += value;
        m_onValueChanced();
    }
} // namespace uil
