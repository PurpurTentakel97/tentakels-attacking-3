//
// Purpur Tentakel
// 15.08.2022
//

#pragma once
#include "EventListener.hpp"
#include <algorithm>
#include <vector>


/**
 * manages the listener.
 * provides all events to the listeners.
 */
 class  EventManager final {
public:
	/**
	 * adds a listener so it can receive all events.
	 */
	void AddListener(EventListener* eventListener) {
		m_listeners.push_back(eventListener);
	}

	/**
	 * remove's a listener so events gets no longer provided to this listener.
	 */
	void RemoveListener(EventListener* eventListener) {
		m_listeners.erase(std::remove(
			m_listeners.begin(), m_listeners.end(), eventListener),
			m_listeners.end());
	}

	/**
	 * provides the current event to all listeners. 
	 */
	void InvokeEvent(Event const& event) const {
		for (auto const listener : m_listeners) {
			listener->OnEvent(event);
		}
	}

private:
	std::vector<EventListener*> m_listeners{ }; ///< contains all active listeners
};
