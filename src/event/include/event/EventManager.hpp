//
// Purpur Tentakel
// 15.08.2022
//

#pragma once
#include "EventListener.hpp"
#include <algorithm>
#include <vector>


namespace eve {
    class EventManager final {
    public:
        void AddListener(EventListener* const eventListener) {
            m_listeners.push_back(eventListener);
        }

        void RemoveListener(EventListener* const eventListener) {
            m_listeners.erase(std::remove(m_listeners.begin(), m_listeners.end(), eventListener), m_listeners.end());
        }

        void InvokeEvent(Event const& event) const {
            for (auto const listener : m_listeners) {
                listener->OnEvent(event);
            }
        }

    private:
        std::vector<EventListener*> m_listeners{};
    };
} // namespace eve
