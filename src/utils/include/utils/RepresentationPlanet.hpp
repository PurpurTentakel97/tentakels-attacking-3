//
// Purpur Tentakel
// 17.01.2024
//

#pragma once

#include "RepresentationSpaceObject.hpp"

namespace utl {
    struct RepresentationPlanet final : public RepresentationSpaceObject {
        bool isDestroyed;
        bool isHumanPlayer;
        usize production;
    };
} // namespace utl
