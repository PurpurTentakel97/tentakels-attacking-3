//
// PurpurTentakel
// 09.03.24
//

#pragma once

#include "RepresentationGalaxy.hpp"
#include "RepresentationPlayer.hpp"

namespace utl{
    struct RepresentationLogicSave final{
        RepresentationGalaxy main;
        RepresentationGalaxy start;
        RepresentationGalaxy current;
        std::vector<RepresentationPlayer> all_player;
        std::vector<RepresentationPlayer> current_player;
    };
}
