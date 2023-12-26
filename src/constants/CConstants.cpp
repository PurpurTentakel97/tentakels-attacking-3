//
// Purpur Tentakel
// 09.06.2023
//

#include "CConstants.hpp"

int Constants::GetConfigValueCount() const {
    return
        global.configVersionCount +
        fight.configEntryCount +
        fleet.configEntryCount +
        gameEvents.configEntryCount +
        global.configEntryCount +
        planet.configEntryCount +
        player.configEntryCount +
        sound.configEntryCount +
        window.configEntryCount +
        world.configEntryCount;
}
