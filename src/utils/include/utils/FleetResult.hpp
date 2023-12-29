//
// Purpur Tentakel
// 23.05.2023
//

#include <helper/HLogicAlias.hpp>
#include <memory>


namespace utl {
    struct FleetResult final {
        SpaceObject_ty origin;
        Fleet_ty fleet;
        SpaceObject_ty destination;
        bool valid;
    };
} // namespace utl
