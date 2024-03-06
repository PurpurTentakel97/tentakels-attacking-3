//
// Purpur Tentakel
// 09.06.2023
//

#include "CConstants.hpp"

namespace cst {
    utl::usize Constants::GetConfigValueCount() const {
        return g_version.get_load_config_entry_count() + g_fight.get_load_config_entry_count()
             + g_fleet.get_load_config_entry_count() + g_game_events.get_load_config_entry_count()
             + g_global.get_load_config_entry_count() + g_planet.get_load_config_entry_count()
             + g_player.get_load_config_entry_count() + g_sound.get_load_config_entry_count()
             + g_window.get_load_config_entry_count() + g_world.get_load_config_entry_count();
    }
} // namespace cst
