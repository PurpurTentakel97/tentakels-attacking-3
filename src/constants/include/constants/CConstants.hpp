//
// Purpur Tentakel
// 27.10.2022
//

#pragma once

#include "G_Fight.hpp"
#include "G_Version.hpp"
#include "CFiles.hpp"
#include "CFleet.hpp"
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
        Fleet fleet;
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
