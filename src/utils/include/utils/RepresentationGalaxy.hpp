//
// Purpur Tentakel
// 17.01.2024
//

#pragma once

#include "RepresentationSpaceObject.hpp"
#include <vector>

namespace utl {
    struct RepresentationGalaxy final {
        std::vector<RepresentationPlanet> planets{};
        std::vector<RepresentationTargetPoint> targetPoints{};
        std::vector<RepresentationFleet> fleets{};
        vec2pos_ty size{};
    };
} // namespace utl
