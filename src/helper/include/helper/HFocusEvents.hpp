//
// Purpur Tentakel
// 23.10.2022
//

#pragma once
#include "HUIAlias.hpp"

/**
 * wraps the events to add a focus layer.
 * if the bool is set the popup version in invoked.
 */
void AddFocusLayer(bool isPopUp = false);
/**
 * wraps the events to delete a focus layer.
 * if the bool is set the popup version in invoked.
 */
void DeleteFocusLayer(bool isPopUp = false);

/**
 * wraps the events to add a focus element.
 * if the bool is set the popup version in invoked.
 */
void AddFocusElement(Focusable_ty_raw focusable, bool isPopUp = false);
/**
 * wraps the events to delete a focus element.
 * if the bool is set the popup version in invoked.
 */
void DeleteFocusElement(Focusable_ty_raw focusable, bool isPopUp = false);

/**
 * wraps the event to select the next focus element.
 */
void SelectNextFocusElement();
/**
 * wraps the events to select a focus element.
 * if the bool is set the popup version in invoked.
 */
void SelectFocusElement(Focusable_ty_raw focusable, bool isPopUp = false);
