//
// Purpur Tentakel
// 04.09.2022
//

#pragma once

#include <CustomRaylib.hpp>

class Focusable {
private:
    unsigned int m_focusID;
    bool m_isFocus{ false };
    bool m_wasLastFocus{ false };

protected:
    bool m_isNestedFocus{ false };

public:
    explicit Focusable(unsigned int ID);

    virtual ~Focusable();

    [[nodiscard]] bool IsFocused() const;

    void SetFocus(bool focus);

    [[nodiscard]] bool GotFocused() const;

    [[nodiscard]] bool IsNestedFocus() const;

    void SetNestedFocus(bool nestedFocus);

    [[nodiscard]] virtual bool IsEnabled() const = 0;

    [[nodiscard]] unsigned int GetFocusID() const;

    void SetFocusID(unsigned int focusID) noexcept;

    [[nodiscard]] virtual Rectangle GetCollider() const = 0;
};
