//
// Purpur Tentakel
// 17.01.2024
//

#pragma once

#include "SpaceObjectRepresentation.hpp"

namespace utl {
    struct PlanetRepresentation final : public SpaceObjectRepresentation {
        bool isDestroyed;
        bool isHumanPlayer;
        usize production;
    };
} // namespace utl
