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
        CGameEvents gameEvents;
        CFight fight;
        CFleet fleet;
        CGlobal global;
        CPlanet planet;
        CPlayer player;
        CSound sound;
        CWindow window;
        CWorld world;

        // non config related
        CTextProcessing textProcessing;
        CFiles files;

        [[nodiscard]] static int GetConfigValueCount();
    };
} // namespace cst
