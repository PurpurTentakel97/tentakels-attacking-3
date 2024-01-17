//
// PurpurTentakel
// 25.05.23
//

#pragma once

#include <alias/AliasLogic.hpp>
#include <memory>
#include <utility>

namespace hlp {
    [[nodiscard]] std::pair<bool, lgk::SpaceObject_ty>
    TryGetTarget(lgk::Fleet_ty_raw fleet, lgk::SpaceObject_ty_c target);
}
