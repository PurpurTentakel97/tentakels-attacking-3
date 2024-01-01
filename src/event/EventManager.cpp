//
// Purpur Tentakel
// 01.01.2024
//


#include "event/EventManager.hpp"

namespace eve {
    void eve::EventManager::AddListener(EventListener* const eventListener) {
        m_listeners.push_back(eventListener);
    }

    void EventManager::RemoveListener(EventListener* const eventListener) {
        auto const result = std::remove(m_listeners.begin(), m_listeners.end(), eventListener);
        if (result == m_listeners.end()) {
            return;
        }
        m_listeners.erase(result, m_listeners.end());
    }

    void EventManager::InvokeEvent(Event const& event) const {
        for (auto const listener : m_listeners) {
            listener->OnEvent(event);
        }
    }
} // namespace eve
