//
// Purpur Tentakel
// 27.10.2022
//

#pragma once

#include "G_Fight.hpp"
#include "G_Version.hpp"
#include "CFiles.hpp"
#include "G_Fleet.hpp"
#include "CGameEvents.hpp"
#include "CGlobal.hpp"
#include "CPlanet.hpp"
#include "CPlayer.hpp"
#include "CSound.hpp"
#include "CTextProcessing.hpp"
#include "CWindow.hpp"
#include "CWorld.hpp"

namespace cst {
    struct Constants final {
        // config related
        G_Version g_version;
        GameEvents gameEvents;
        G_Fight g_fight;
        G_Fleet g_fleet;
        Global global;
        Planet planet;
        Player player;
        Sound sound;
        Window window;
        World world;

        // non config related
        TextProcessing textProcessing;
        Files files;

        [[nodiscard]] utl::usize GetConfigValueCount() const;
    };
} // namespace cst
