//
// Purpur Tentakel
// 01.01.2024
//


#include "NewInputLine.hpp"

#include "helper/HInput.hpp"
#include "helper/HTextProcessing.hpp"
#include <sstream>


namespace uil {
    void NewInputLine::UpdateValue() {
        try {
            m_oldValue = m_value;
            if (IsA<std::string>()) {
                m_value = m_strValue;
            } else if (IsA<utl::usize>()) {
                std::stringstream s{ m_strValue };
                utl::usize dummy{};
                s >> dummy;
                m_value = dummy;
            } else if (IsA<double>()) {
                std::stringstream s{ m_strValue };
                double dummy{};
                s >> dummy;
                m_value = dummy;
            }
        } catch (std::exception const&) { }
    }

    bool NewInputLine::AddChar(utl::usize key) {
        auto const validAdd{ m_charLimit > m_strValue.size() };

        if (not validAdd) {
            return false;
        }

        m_strValue += static_cast<char>(key);

        eve::PlaySoundEvent const event{ app::SoundType::TEXT };
        app::AppContext::GetInstance().eventManager.InvokeEvent(event);

        UpdateValue();
        m_onValueChanced(*this);

        return true;
    }

    void NewInputLine::RemoveChar() {
        if (m_strValue.empty()) {
            return;
        }

        m_strValue.pop_back();

        eve::PlaySoundEvent const event{ app::SoundType::TEXT };
        app::AppContext::GetInstance().eventManager.InvokeEvent(event);

        UpdateValue();
        m_onValueChanced(*this);
    }

    bool NewInputLine::IsValidKey(utl::usize key) const {
        if (IsA<utl::usize>()) {
            auto const isInteger{ key >= m_keyLockup.at(KeyType::FIRST_NUMBER)
                                  and key <= m_keyLockup.at(KeyType::LAST_NUMBER) };
            return isInteger;

        } else if (IsA<double>()) {
            auto const isInteger{ key >= m_keyLockup.at(KeyType::FIRST_NUMBER)
                                  and key <= m_keyLockup.at(KeyType::LAST_NUMBER) };
            auto const isSpecialCharacter{ key == m_keyLockup.at(KeyType::DOT)
                                           or key == m_keyLockup.at(KeyType::COMMA) };
            auto const isFloatingPoint{ isInteger or isSpecialCharacter };

            if (not isFloatingPoint) {
                return false;
            }

            if (isSpecialCharacter) {
                if (m_strValue.empty()) {
                    return false;
                }

                for (char const& c : m_strValue) {
                    if (c == m_keyLockup.at(KeyType::COMMA) or c == m_keyLockup.at(KeyType::DOT)) {
                        return false;
                    }
                }
            }
            return true;

        } else if (IsA<std::string>()) {
            auto const isChar{ key >= m_keyLockup.at(KeyType::FIRST_CHAR)
                               and key <= m_keyLockup.at(KeyType::LAST_CHAR) };
            return isChar;
        }
        assert(false and "invalid datatype");
        return false;
    }

    void NewInputLine::UpdateStringValue() {
        if (IsA<std::string>()) {
            m_strValue = std::get<std::string>(m_value);
        } else if (IsA<utl::usize>()) {
            m_strValue = std::to_string(std::get<utl::usize>(m_value));
        } else {
            m_strValue = std::to_string(std::get<double>(m_value));
        }
    }

    NewInputLine::NewInputLine(
            utl::usize const focusID,
            Vector2 const pos,
            Vector2 const size,
            Alignment const alignment,
            utl::input_variant_ty const& startValue
    )
        : NewInputLine{ focusID, pos, size, alignment, startValue, 20 } {};

    NewInputLine::NewInputLine(
            utl::usize const focusID,
            Vector2 const pos,
            Vector2 const size,
            Alignment const alignment,
            utl::input_variant_ty const& startValue,
            utl::usize const charLimit
    )
        : UIElement{ pos, size, alignment },
          Focusable{ focusID },
          m_value{ startValue },
          m_oldValue{ startValue },
          m_charLimit{ charLimit } {

        UpdateStringValue();
    }

    void NewInputLine::SetPlaceholderText(std::string placeholderText) {
        m_placeholderText = std::move(placeholderText);
    }

    std::string NewInputLine::PlaceholderText() const {
        return m_placeholderText;
    }

    bool NewInputLine::HasValue() const {
        return not m_strValue.empty();
    }

    bool NewInputLine::HasValueChanced() const {
        return m_value != m_valueLastFrame;
    }

    std::string NewInputLine::GetStrValue() const {
        return m_strValue;
    }

    void NewInputLine::Clear() {
        m_strValue.clear();
        UpdateValue();
    }

    void NewInputLine::SetOnEnter(NewInputLine::on_enter_callback_ty callback) {
        m_onEnter = std::move(callback);
    }

    void NewInputLine::SetOnValueChanced(NewInputLine::on_value_chanced_callback_ty callback) {
        m_onValueChanced = std::move(callback);
    }

    bool NewInputLine::IsClearByFocus() const {
        return m_isClearByFocus;
    }

    void NewInputLine::SetClearByFocus(bool const clear) {
        m_isClearByFocus = clear;
    }

    bool NewInputLine::IsClearByNextInput() const {
        return m_isClearNextInput;
    }

    void NewInputLine::SetClearByNextInput(bool const clear) {
        m_isClearNextInput = clear;
    }

    void NewInputLine::SetEnabled(bool const enabled) {
        m_isEnabled = enabled;
    }

    double NewInputLine::BackspacePressTime() const {
        return m_backspacePressTime;
    }

    void NewInputLine::SetBackspacePressTime(double const time) {
        m_backspacePressTime = time;
    }

    utl::usize NewInputLine::CharLimit() const {
        return m_charLimit;
    }

    void NewInputLine::SetCharLimit(utl::usize const limit) {
        m_charLimit = limit;
    }

    bool NewInputLine::IsEnabled() const {
        return m_isEnabled;
    }

    Rectangle NewInputLine::GetCollider() const {
        return m_collider;
    }

    void NewInputLine::CheckAndUpdate(Vector2 const& mousePosition, app::AppContext_ty_c appContext) {
        UIElement::CheckAndUpdate(mousePosition, appContext);

        if (not m_isEnabled) {
            return;
        }

        auto const isHover{ CheckCollisionPointRec(mousePosition, m_collider) };
        auto const isSelect{ (not IsFocused()) and isHover and IsMouseButtonPressed(MOUSE_BUTTON_LEFT) };

        if (isSelect) {
            eve::SelectFocusElementEvent const event{ this };
            appContext.eventManager.InvokeEvent(event);
        }

        if (not IsFocused()) {
            m_alreadyCleared = false;
            return;
        }

        auto const isEnter{ hlp::IsOnlyEnterConfirmInputPressed() };
        if (isEnter) {
            m_onEnter(*this);
        }

        if (IsKeyPressed(KEY_BACKSPACE)) {
            RemoveChar();
            m_currentBackspacePressTime = GetTime();
            return;
        }

        if (IsKeyDown(KEY_BACKSPACE)) {
            if (m_currentBackspacePressTime < GetTime() - m_backspacePressTime) {
                RemoveChar();
                return;
            }
        }

        while (true) {
            auto const key{ static_cast<utl::usize>(GetCharPressed()) };

            if (key == 0) {
                break;
            }

            if (not m_alreadyCleared) {
                if (m_isClearByFocus and GotFocused()) {
                    Clear();
                    m_alreadyCleared = true;
                }
            }
            if (m_isClearNextInput) {
                Clear();
                m_isClearNextInput = false;
            }

            if (not IsValidKey(key)) {
                continue;
            }

            if (not AddChar(key)) {
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

    void NewInputLine::Render(app::AppContext_ty_c appContext) {

        // update here to make sure it's after all calls of HasValueChanced
        m_valueLastFrame = m_value;

        DrawRectangleRec(m_collider, GREY_100);

        if (m_isEnabled) {
            DrawRectangleLinesEx(m_collider, 2.0f, PURPLE);
        }

        Vector2 const pos{ m_collider.x + 10.0f, m_collider.y + m_collider.height * 0.1f };
        auto const fontSize{ m_collider.height * 0.8f };
        std::string printableInput{};

        if (m_strValue.empty()) {
            auto const printablePlaceholder{
                hlp::GetPrintablePlaceholderTextInCollider(m_placeholderText, fontSize, m_collider, appContext)
            };
            DrawTextEx(*(appContext.assetManager.GetFont()), printablePlaceholder.c_str(), pos, fontSize, 0, GRAY);
        } else {
            printableInput = hlp::GetPrintableTextInCollider(m_strValue, fontSize, m_collider, appContext);
            DrawTextEx(*(appContext.assetManager.GetFont()), printableInput.c_str(), pos, fontSize, 0, WHITE);
        }

        if (IsFocused()) {
            auto const time{ static_cast<utl::usize>(GetTime() * 2.0f) };
            auto const textLength =
                    MeasureTextEx(*(appContext.assetManager.GetFont()), printableInput.c_str(), fontSize, 0.0f);

            if (time % 2 == 0) {
                DrawTextEx(
                        *(appContext.assetManager.GetFont()),
                        &cst::TextProcessing::cursor,
                        Vector2(pos.x + cst::TextProcessing::cursorOffset + textLength.x,
                                pos.y + m_collider.height * 0.05f),
                        fontSize,
                        0,
                        PURPLE
                );
            }
        }
    }
} // namespace uil
