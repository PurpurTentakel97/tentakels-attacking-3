//
// Purpur Tentakel
// 17.01.2024
//

#pragma once
#include "Vec2.hpp"
#include <alias/AliasUtils.hpp>

namespace utl {
    struct SpaceObjectRepresentation {
        bool isDiscovered;
        usize ID;
        usize playerID;
        usize shipCount;
        vec2pos_ty position;
    };
} // namespace utl
