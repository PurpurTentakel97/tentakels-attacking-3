//
// Purpur Tentakel
// 23.10.2022
//

#pragma once

#include <alias/AliasUiLib.hpp>

namespace hlp {
    void AddFocusLayer(bool isPopUp = false);

    void DeleteFocusLayer(bool isPopUp = false);

    void AddFocusElement(uil::Focusable_ty_raw focusable, bool isPopUp = false);

    void DeleteFocusElement(uil::Focusable_ty_raw focusable, bool isPopUp = false);

    void SelectNextFocusElement();

    void SelectFocusElement(uil::Focusable_ty_raw focusable, bool isPopUp = false);
} // namespace hlp
