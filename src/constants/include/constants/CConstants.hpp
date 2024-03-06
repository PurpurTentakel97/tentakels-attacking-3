//
// Purpur Tentakel
// 27.10.2022
//

#pragma once

#include "CFiles.hpp"
#include "CGlobal.hpp"
#include "CPlanet.hpp"
#include "CPlayer.hpp"
#include "CSound.hpp"
#include "CTextProcessing.hpp"
#include "CWindow.hpp"
#include "CWorld.hpp"
#include "G_Fight.hpp"
#include "G_Fleet.hpp"
#include "G_Game_Events.hpp"
#include "G_Version.hpp"
#include "HelperGameEvents.hpp"

namespace cst {
    struct Constants final {
        // config related
        G_Version g_version;
        G_Game_Events g_game_events;
        G_Fight g_fight;
        G_Fleet g_fleet;
        Global global;
        Planet planet;
        Player player;
        Sound sound;
        Window window;
        World world;

        // config helper
        HelperGameEvents h_game_events;

        // non config related
        TextProcessing textProcessing;
        Files files;

        [[nodiscard]] utl::usize GetConfigValueCount() const;
    };
} // namespace cst
