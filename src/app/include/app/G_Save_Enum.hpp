//
// Purpur Tentakel
// 17.03.2024
// This is a generated file. Do not edit this file.
//

#pragma once

#include <string>


namespace app {
    enum class G_Save_Enum {
        G_GLOBAL,

        G_GLOBAL_SAVE_SECTION_COUNT,
        G_GLOBAL_TOTAL_SAVE_ENTRY_COUNT,
        G_GLOBAL_LOAD_SAVE_ENTRY_COUNT,
        G_GLOBAL_GAME_VERSION,
        G_GLOBAL_SAVE_VERSION,
    };

    [[nodiscard]] std::string SToS(G_Save_Enum const& type);

} // namespace app
