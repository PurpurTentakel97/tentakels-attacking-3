//
// Purpur Tentakel
// 27.10.2022
//

#pragma once
#include "CFight.hpp"
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
        GameEvents gameEvents;
        Fight fight;
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

        [[nodiscard]] static int GetConfigValueCount();
    };
} // namespace cst
