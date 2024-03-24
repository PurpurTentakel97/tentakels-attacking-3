//
// Purpur Tentakel
// 24.03.2024
// This is a generated file. Do not edit this file.
//

#include "G_Save_Enum.hpp"
#include <utility>


namespace utl {
    std::string SToS(G_Save_Enum const& type) {
        switch (type) {
            case G_Save_Enum::G_SAVE: return "save";

            case G_Save_Enum::G_SAVE_VERSION: return "save_version";

            case G_Save_Enum::G_SAVE_VERSION_TOTAL_SAVE_ENTRY_COUNT: return "total_save_entry_count";
            case G_Save_Enum::G_SAVE_VERSION_LOAD_SAVE_ENTRY_COUNT: return "load_save_entry_count";
            case G_Save_Enum::G_SAVE_VERSION_SAVE_GAME_VERSION: return "save_game_version";
        }
    std::unreachable();
    }
} // namespace utl
