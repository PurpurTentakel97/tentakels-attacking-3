//
// Purpur Tentakel
// 23.10.2022
//

#include "HFocusEvents.h"
#include "AppContext.h"
#include "HFocusEvents.h"
#include "event/EventsUI.hpp"

void AddFocusLayer(bool isPopUp) {
	if (isPopUp) {
		NewFocusPopUpLayerEvent const event{ };
		AppContext::GetInstance().eventManager.InvokeEvent(event);
	}
	else {
		NewFocusLayerEvent const event{ };
		AppContext::GetInstance().eventManager.InvokeEvent(event);
	}
}
void DeleteFocusLayer(bool isPopUp) {
	if (isPopUp) {
		DeleteFocusPopUpLayerEvent const event{ };
		AppContext::GetInstance().eventManager.InvokeEvent(event);
	}
	else {
		DeleteFocusLayerEvent const event{ };
		AppContext::GetInstance().eventManager.InvokeEvent(event);
	}
}

void AddFocusElement(Focusable_ty_raw focusable, bool isPopUp) {
	if (isPopUp) {
		NewFocusPopUpElementEvent const event{ focusable };
		AppContext::GetInstance().eventManager.InvokeEvent(event);
	}
	else {
		NewFocusElementEvent const event{ focusable };
		AppContext::GetInstance().eventManager.InvokeEvent(event);
	}
}
void DeleteFocusElement(Focusable_ty_raw focusable, bool isPopUp) {
	if (isPopUp) {
		DeleteFocusPopUpElementEvent const event{ focusable };
		AppContext::GetInstance().eventManager.InvokeEvent(event);
	}
	else {
		DeleteFocusElementEvent const event{ focusable };
		AppContext::GetInstance().eventManager.InvokeEvent(event);
	}
}

void SelectNextFocusElement() {
	SelectNextFocusElementEvent const event{ };
	AppContext::GetInstance().eventManager.InvokeEvent(event);
}
void SelectFocusElement(Focusable_ty_raw focusable, bool isPopUp) {
	if (isPopUp) {
		SelectFocusPopUpElementEvent const event{ focusable };
		AppContext::GetInstance().eventManager.InvokeEvent(event);
	}
	else {
		SelectFocusElementEvent const event{ focusable };
		AppContext::GetInstance().eventManager.InvokeEvent(event);
	}
}
