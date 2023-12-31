//
// Purpur Tentakel
// 04.09.2022
//

#pragma once

#include <CustomRaylib.hpp>
#include <alias/AliasUtils.hpp>


namespace uil {
    class Focusable {
    private:
        utl::usize m_focusID;
        bool m_isFocus{ false };
        bool m_wasLastFocus{ false };

    protected:
        bool m_isNestedFocus{ false };

    public:
        explicit Focusable(utl::usize ID);

        virtual ~Focusable();

        [[nodiscard]] bool IsFocused() const;

        void SetFocus(bool focus);

        [[nodiscard]] bool GotFocused() const;

        [[nodiscard]] bool IsNestedFocus() const;

        void SetNestedFocus(bool nestedFocus);

        [[nodiscard]] virtual bool IsEnabled() const = 0;

        [[nodiscard]] utl::usize GetFocusID() const;

        void SetFocusID(utl::usize focusID) noexcept;

        [[nodiscard]] virtual Rectangle GetCollider() const = 0;
    };
} // namespace uil
