//
// Purpur Tentakel
// 09.06.2023
//

#include "CConstants.hpp"

namespace cst {
    utl::usize Constants::GetConfigValueCount() const {
        return g_version.get_load_config_entry_count() + g_fight.get_load_config_entry_count()
             + g_fleet.get_load_config_entry_count() + g_game_events.get_load_config_entry_count()
             + g_global.get_load_config_entry_count();
    }
} // namespace cst
