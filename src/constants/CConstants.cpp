//
// Purpur Tentakel
// 09.06.2023
//

#include "CConstants.hpp"
#include <helper/HPrint.hpp>

namespace cst {
    void Constants::LoadGame([[maybe_unused]] utl::SaveState const& saveState) {
        hlp::Print(hlp::PrintType::INFO, "Load Constants Here");
    }

    void Constants::SaveGame(utl::SaveState& saveState) const {
        saveState.g_save_version.set_game_version(g_version.get_game_version());
        saveState.g_save_version.set_save_game_version(g_version.get_save_game_version());
    }

    utl::usize Constants::GetConfigValueCount() const {
        return g_version.get_load_config_entry_count() + g_fight.get_load_config_entry_count()
             + g_fleet.get_load_config_entry_count() + g_game_events.get_load_config_entry_count()
             + g_global.get_load_config_entry_count() + g_planet.get_load_config_entry_count()
             + g_player.get_load_config_entry_count() + g_sound.get_load_config_entry_count()
             + g_window.get_load_config_entry_count() + g_world.get_load_config_entry_count();
    }
} // namespace cst
