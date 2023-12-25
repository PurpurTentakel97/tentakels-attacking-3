//
// Purpur Tentakel
// 25.08.2022
//

#pragma once
#include "MainEvent.hpp"

/**
 * pure virtual class that should be implemented by every class that should can receive events.
 */
class EventListener {
	friend class EventManager; ///< defines the event manager as friend so it can call OnEvent
private:
	virtual void OnEvent(Event const& event) = 0; ///! gets implemented by every listener to receive events
};
	