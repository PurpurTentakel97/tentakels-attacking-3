//
// Purpur Tentakel
// 12.07.2023
//

#include "CGameEvents.hpp"

namespace cst {
    void GameEvents::SetFlag(GameEventType const type, bool const active) {
        if (active) {
            events |= type;
        } else {
            if ((type & GameEventType::GLOBAL) == GameEventType::GLOBAL) {
                events = static_cast<GameEventType>(0b11000000);
                return;
            }
            events &= ~type;
        }
    }

    bool GameEvents::IsFlag(GameEventType const type) const {
        return (events & type) == type;
    }
} // namespace cst
