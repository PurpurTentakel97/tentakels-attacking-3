//
// Purpur Tentakel
// 23.10.2022
//

#include "HFocusEvents.hpp"
#include <app/AppContext.hpp>
#include <event/EventsUI.hpp>

namespace hlp {
    void AddFocusLayer(bool const isPopUp) {
        if (isPopUp) {
            eve::NewFocusPopUpLayerEvent const event{};
            AppContext::GetInstance().eventManager.InvokeEvent(event);
        } else {
            eve::NewFocusLayerEvent const event{};
            AppContext::GetInstance().eventManager.InvokeEvent(event);
        }
    }

    void DeleteFocusLayer(bool const isPopUp) {
        if (isPopUp) {
            eve::DeleteFocusPopUpLayerEvent const event{};
            AppContext::GetInstance().eventManager.InvokeEvent(event);
        } else {
            eve::DeleteFocusLayerEvent const event{};
            AppContext::GetInstance().eventManager.InvokeEvent(event);
        }
    }

    void AddFocusElement(Focusable_ty_raw focusable, bool const isPopUp) {
        if (isPopUp) {
            eve::NewFocusPopUpElementEvent const event{ focusable };
            AppContext::GetInstance().eventManager.InvokeEvent(event);
        } else {
            eve::NewFocusElementEvent const event{ focusable };
            AppContext::GetInstance().eventManager.InvokeEvent(event);
        }
    }

    void DeleteFocusElement(Focusable_ty_raw focusable, bool const isPopUp) {
        if (isPopUp) {
            eve::DeleteFocusPopUpElementEvent const event{ focusable };
            AppContext::GetInstance().eventManager.InvokeEvent(event);
        } else {
            eve::DeleteFocusElementEvent const event{ focusable };
            AppContext::GetInstance().eventManager.InvokeEvent(event);
        }
    }

    void SelectNextFocusElement() {
        eve::SelectNextFocusElementEvent const event{};
        AppContext::GetInstance().eventManager.InvokeEvent(event);
    }

    void SelectFocusElement(Focusable_ty_raw focusable, bool const isPopUp) {
        if (isPopUp) {
            eve::SelectFocusPopUpElementEvent const event{ focusable };
            AppContext::GetInstance().eventManager.InvokeEvent(event);
        } else {
            eve::SelectFocusElementEvent const event{ focusable };
            AppContext::GetInstance().eventManager.InvokeEvent(event);
        }
    }
} // namespace hlp
