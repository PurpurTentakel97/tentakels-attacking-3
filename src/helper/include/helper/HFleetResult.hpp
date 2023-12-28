//
// Purpur Tentakel
// 23.05.2023
//

#include "HLogicAlias.hpp"
#include <memory>


namespace hlp {
    struct HFleetResult final {
        SpaceObject_ty origin;
        Fleet_ty fleet;
        SpaceObject_ty destination;
        bool valid;
    };
} // namespace hlp
