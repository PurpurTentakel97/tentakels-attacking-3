//
// Purpur Tentakel
// 04.09.2022
//

#include "Focusable.hpp"
#include <helper/HFocusEvents.hpp>


namespace uil {
    Focusable::Focusable(utl::usize const ID) : m_focusID(ID) { }

    Focusable::~Focusable() {
        hlp::DeleteFocusElement(this);
    }

    bool Focusable::IsFocused() const {
        return m_isFocus;
    }

    void Focusable::SetFocus(bool const focus) {
        m_wasLastFocus = m_isFocus;
        m_isFocus = focus;
    }

    bool Focusable::GotFocused() const {
        return not m_wasLastFocus and m_isFocus;
    }

    bool Focusable::IsNestedFocus() const {
        return m_isNestedFocus;
    }

    void Focusable::SetNestedFocus(bool const nestedFocus) {
        m_isNestedFocus = nestedFocus;
    }

    utl::usize Focusable::GetFocusID() const {
        return m_focusID;
    }

    void Focusable::SetFocusID(utl::usize const focusID) noexcept {
        m_focusID = focusID;
    }
} // namespace uil
