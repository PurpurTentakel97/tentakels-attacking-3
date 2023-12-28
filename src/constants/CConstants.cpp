//
// Purpur Tentakel
// 09.06.2023
//

#include "CConstants.hpp"

namespace cst {
    int Constants::GetConfigValueCount() {
        return Global::configVersionCount + Fight::configEntryCount + Fleet::configEntryCount
               + GameEvents::configEntryCount + Global::configEntryCount + Planet::configEntryCount
               + Player::configEntryCount + Sound::configEntryCount + Window::configEntryCount
               + World::configEntryCount;
    }
} // namespace cst
