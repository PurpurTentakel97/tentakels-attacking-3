//
// Purpur Tentakel
// 04.09.2022
//

#pragma once
#include "CustomRaylib.h"

/**
 * provides the focusable implementation for every ui element that should be focusable.
 */
class Focusable {
private:
	unsigned int m_focusID; ///< contains the unique (per layer) id
	bool m_isFocus{ false }; ///< contains if this focusable is currently in focus
	bool m_wasLastFocus{ false }; ///< contains if this focussable was focused last time

protected:
	bool m_isNestedFocus{ false }; ///< contains if there is a nested focus

public:
	/**
	 * ctor.
	 * only initialization.
	 */
	Focusable(unsigned int ID);
	/**
	 * dtor
	 * deletes this in the focus system if its still exists.
	 */
	~Focusable();
	
	/**
	 * returns if this element currently focused.
	 */
	[[nodiscard]] bool IsFocused() const;
	/**
	 * sets if this element is in focus.
	 */
	void SetFocus(bool focus);
	/**
	 * returns if the this focusable got focused last focus change.
	 */
	[[nodiscard]] bool GotFocused() const;
	/**
	 * returns if this element has an nested focus.
	 */
	[[nodiscard]] bool IsNestedFocus() const;
	/**
	 * sets if this element has an nested focus.
	 */
	void SetNestedFocus(bool nestedFocus);

	/**
	 * returns if the current elements is enabled.
	 */
	[[nodiscard]] virtual bool IsEnabled() const = 0;

	/**
	 * returns the unique (per layer) id.
	 */
	[[nodiscard]] unsigned int GetFocusID() const;
	/**
	 * sets a new focus ID. 
	 * be careful with this member function. it may break the app if the focus ID is doubling after that.
	 */
	void SetFocusID(unsigned int focusID) noexcept;
	/**
	 * returns thr current collider.
	 */
	[[nodiscard]] virtual Rectangle GetCollider() const = 0;
};
