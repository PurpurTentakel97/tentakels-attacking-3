//
// Purpur Tentakel
// 17.01.2024
//

#pragma once

#include "RepresentationSpaceObject.hpp"

namespace utl {
    struct RepresentationFleet final : public RepresentationSpaceObject {
        RepresentationSpaceObject destRepresentation;
    };
} // namespace utl
