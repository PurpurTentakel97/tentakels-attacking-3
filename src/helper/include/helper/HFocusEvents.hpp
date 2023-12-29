//
// Purpur Tentakel
// 23.10.2022
//

#pragma once

#include <alias/AliasUiLib.hpp>

namespace hlp {
    void AddFocusLayer(bool isPopUp = false);

    void DeleteFocusLayer(bool isPopUp = false);

    void AddFocusElement(Focusable_ty_raw focusable, bool isPopUp = false);

    void DeleteFocusElement(Focusable_ty_raw focusable, bool isPopUp = false);

    void SelectNextFocusElement();

    void SelectFocusElement(Focusable_ty_raw focusable, bool isPopUp = false);
} // namespace hlp
