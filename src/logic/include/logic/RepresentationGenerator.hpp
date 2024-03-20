//
// PurpurTentakel
// 19.01.24
//

#pragma once

#include "Galaxy.hpp"

namespace lgk {
    [[nodiscard]] utl::RepresentationBlackHole GenSingleBlackHoleRep(BlackHole_ty_c blackHole, int galaxyWidth);

    [[nodiscard]] utl::RepresentationSpaceObject GenSingleSpaceObjectRep(SpaceObject_ty_c spaceObject);

    [[nodiscard]] utl::RepresentationGalaxy GenGalaxyRep(Galaxy const* galaxy);

    [[nodiscard]] utl::RepresentationPlayer GenPlayerRep(Player const* player);
} // namespace lgk
