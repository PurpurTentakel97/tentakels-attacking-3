//
// Purpur Tentakel
// 17.01.2024
//

#pragma once

#include "DestinationRepresentation.hpp"
#include "SpaceObjectRepresentation.hpp"

namespace utl {
    struct FleetRepresentation final : public SpaceObjectRepresentation {
        DestinationRepresentation destRepresentation;
    };
} // namespace utl
