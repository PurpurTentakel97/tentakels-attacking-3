//
// Purpur Tentakel
// 09.06.2023
//

#include "CConstants.hpp"

int Constants::GetConfigValueCount() {
    return
        CGlobal::configVersionCount +
        CFight::configEntryCount +
        CFleet::configEntryCount +
        CGameEvents::configEntryCount +
        CGlobal::configEntryCount +
        CPlanet::configEntryCount +
        CPlayer::configEntryCount +
        CSound::configEntryCount +
        CWindow::configEntryCount +
        CWorld::configEntryCount;
}
