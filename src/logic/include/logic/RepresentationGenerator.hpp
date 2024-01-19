//
// PurpurTentakel
// 19.01.24
//

#pragma once

#include "Galaxy.hpp"
#include <utils/RepresentationGalaxy.hpp>

namespace lgk {
    [[nodiscard]] utl::RepresentationGalaxy GenGalaxyRep(Galaxy const* galaxy);
}
