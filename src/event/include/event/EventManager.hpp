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
    private:
        std::vector<EventListener*> m_listeners{};

    public:
        void AddListener(EventListener* const eventListener);

        void RemoveListener(EventListener* const eventListener);

        void InvokeEvent(Event const& event) const;
    };
} // namespace eve
