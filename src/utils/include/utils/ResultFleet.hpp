//
// Purpur Tentakel
// 23.05.2023
//

#pragma once

#include <alias/AliasLogic.hpp>
#include <memory>


namespace utl {
    struct ResultFleet final {
        lgk::SpaceObject_ty origin;
        lgk::Fleet_ty fleet;
        lgk::SpaceObject_ty destination;
        bool valid;
    };
} // namespace utl
