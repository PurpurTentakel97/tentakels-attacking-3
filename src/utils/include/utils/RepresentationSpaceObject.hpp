//
// Purpur Tentakel
// 17.01.2024
//

#pragma once
#include "SpaceObjectType.hpp"
#include "Vec2.hpp"
#include <alias/AliasUtils.hpp>

namespace utl {
    struct RepresentationSpaceObject {
        bool isDiscovered{};
        usize ID{};
        usize playerID{};
        usize shipCount{};
        vec2pos_ty position{};
        SpaceObjectType type{};
    };

    struct RepresentationFleet final : public RepresentationSpaceObject {
        utl::usize engineProblemYears{};
        RepresentationSpaceObject destRepresentation;
    };

    struct RepresentationPlanet final : public RepresentationSpaceObject {
        bool isHumanPlayer{};
        usize production{};
    };

    struct RepresentationTargetPoint final : public RepresentationSpaceObject { };

    struct RepresentationBlackHole final : public RepresentationSpaceObject { };
} // namespace utl
