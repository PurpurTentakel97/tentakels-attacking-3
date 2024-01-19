//
// Purpur Tentakel
// 17.01.2024
//

#pragma once

#include "RepresentationSpaceObject.hpp"
#include "TargetType.hpp"

namespace utl {
    struct RepresentationDestination final : public RepresentationSpaceObject {
        TargetType type;
    };
} // namespace utl
