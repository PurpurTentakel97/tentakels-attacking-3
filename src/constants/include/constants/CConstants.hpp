//
// Purpur Tentakel
// 27.10.2022
//

#pragma once

#include "CFiles.hpp"
#include "CTextProcessing.hpp"
#include "G_Fight.hpp"
#include "G_Fleet.hpp"
#include "G_Game_Events.hpp"
#include "G_Global.hpp"
#include "G_Planet.hpp"
#include "G_Player.hpp"
#include "G_Sound.hpp"
#include "G_Version.hpp"
#include "G_Window.hpp"
#include "G_World.hpp"
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
        G_Window g_window;
        G_World g_world;

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

        // window
        Vector2 currentResolutionVec{ 800.0f, 600.0f };
        utl::vec2pos_ty nativeResolutionVec{ 800, 600 };

        [[nodiscard]] utl::usize GetConfigValueCount() const;
    };
} // namespace cst
