//
// Purpur Tentakel
// 17.03.2024
// This is a generated file. Do not edit this file.
//

#pragma once

#include <string>


namespace app {
    enum class G_Save_Enum {
        G_SAVE,

        G_VERSION,

        G_VERSION_GAME_VERSION,
        G_VERSION_SAVE_VERSION,
    };

    [[nodiscard]] std::string SToS(G_Save_Enum const& type);

} // namespace app
