//
// Purpur Tentakel
// 17.01.2024
//

#pragma once

#include "SpaceObjectRepresentation.hpp"
#include "TargetType.hpp"

namespace utl {
    struct DestinationRepresentation final : public SpaceObjectRepresentation {
        TargetType type;
    };
} // namespace utl
