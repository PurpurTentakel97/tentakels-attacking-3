//
// Purpur Tentakel
// 17.01.2024
//

#pragma once

#include "FleetRepresentation.hpp"
#include "PlanetRepresentation.hpp"
#include "TargetPointRepresentation.hpp"
#include <vector>

namespace utl {
    struct GalaxyRepresentation final {
        std::vector<PlanetRepresentation> planets;
        std::vector<TargetPointRepresentation> targetPoints;
        std::vector<FleetRepresentation> fleets;
        vec2pos_ty size;
    };
} // namespace utl
