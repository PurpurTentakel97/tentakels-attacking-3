//
// Purpur Tentakel
// 09.06.2023
//

#include "CConstants.hpp"

namespace cst {
    utl::usize Constants::GetConfigValueCount() const {
        return g_version.get_load_config_entry_count() + g_fight.get_load_config_entry_count();
    }
    /*
    utl::usize Constants::GetConfigValueCount() const {
        return g_version.get_config_entry_count() + g_fight.get_config_entry_count() + Fleet::configEntryCount
               + GameEvents::configEntryCount + Global::configEntryCount + Planet::configEntryCount
               + Player::configEntryCount + Sound::configEntryCount + Window::configEntryCount
               + World::configEntryCount;
    }
     */
} // namespace cst
