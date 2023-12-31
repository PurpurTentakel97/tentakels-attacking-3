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
            app::AppContext::GetInstance().eventManager.InvokeEvent(event);
        } else {
            eve::NewFocusLayerEvent const event{};
            app::AppContext::GetInstance().eventManager.InvokeEvent(event);
        }
    }

    void DeleteFocusLayer(bool const isPopUp) {
        if (isPopUp) {
            eve::DeleteFocusPopUpLayerEvent const event{};
            app::AppContext::GetInstance().eventManager.InvokeEvent(event);
        } else {
            eve::DeleteFocusLayerEvent const event{};
            app::AppContext::GetInstance().eventManager.InvokeEvent(event);
        }
    }

    void AddFocusElement(uil::Focusable_ty_raw focusable, bool const isPopUp) {
        if (isPopUp) {
            eve::NewFocusPopUpElementEvent const event{ focusable };
            app::AppContext::GetInstance().eventManager.InvokeEvent(event);
        } else {
            eve::NewFocusElementEvent const event{ focusable };
            app::AppContext::GetInstance().eventManager.InvokeEvent(event);
        }
    }

    void DeleteFocusElement(uil::Focusable_ty_raw focusable, bool const isPopUp) {
        if (isPopUp) {
            eve::DeleteFocusPopUpElementEvent const event{ focusable };
            app::AppContext::GetInstance().eventManager.InvokeEvent(event);
        } else {
            eve::DeleteFocusElementEvent const event{ focusable };
            app::AppContext::GetInstance().eventManager.InvokeEvent(event);
        }
    }

    void SelectNextFocusElement() {
        eve::SelectNextFocusElementEvent const event{};
        app::AppContext::GetInstance().eventManager.InvokeEvent(event);
    }

    void SelectFocusElement(uil::Focusable_ty_raw focusable, bool const isPopUp) {
        if (isPopUp) {
            eve::SelectFocusPopUpElementEvent const event{ focusable };
            app::AppContext::GetInstance().eventManager.InvokeEvent(event);
        } else {
            eve::SelectFocusElementEvent const event{ focusable };
            app::AppContext::GetInstance().eventManager.InvokeEvent(event);
        }
    }
} // namespace hlp
