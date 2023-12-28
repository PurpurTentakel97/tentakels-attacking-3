//
// Purpur Tentakel
// 25.08.2022
//

#pragma once
#include "EventMain.hpp"

namespace eve {
    class EventListener {
        friend class EventManager;

    private:
        virtual void OnEvent(Event const& event) = 0;

    public:
        virtual ~EventListener() = default;
    };
} // namespace eve
