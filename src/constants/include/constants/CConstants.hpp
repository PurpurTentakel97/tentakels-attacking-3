//
// Purpur Tentakel
// 27.10.2022
//

#pragma once

#include "CFiles.hpp"
#include "G_Player.hpp"
#include "G_Sound.hpp"
#include "CTextProcessing.hpp"
#include "CWindow.hpp"
#include "CWorld.hpp"
#include "G_Fight.hpp"
#include "G_Fleet.hpp"
#include "G_Game_Events.hpp"
#include "G_Global.hpp"
#include "G_Planet.hpp"
#include "G_Version.hpp"
#include "HelperGameEvents.hpp"
#include "HelperWindow.hpp"

namespace cst {
    struct Constants final {
        // config related
        G_Version g_version;
        G_Game_Events g_game_events;
        G_Fight g_fight;
        G_Fleet g_fleet;
        G_Global g_global;
        G_Planet g_planet;
        G_Player g_player;
        G_Sound g_sound;
        Window window;
        World world;

        // config helper
        HelperGameEvents h_game_events;
        HelperWindow h_window;

        // non config related
        TextProcessing textProcessing;
        Files files;

        // game
        bool isGameRunning{ false };
        bool isGamePaused{ true };
        bool isGameSaved{ true };

        // input
        bool acceptInputTriggered{ false };

        [[nodiscard]] utl::usize GetConfigValueCount() const;
    };
} // namespace cst
