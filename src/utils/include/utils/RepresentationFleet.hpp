//
// Purpur Tentakel
// 17.01.2024
//

#pragma once

#include "RepresentationDestination.hpp"
#include "RepresentationSpaceObject.hpp"

namespace utl {
    struct RepresentationFleet final : public RepresentationSpaceObject {
        RepresentationDestination destRepresentation;
    };
} // namespace utl
