//
// PurpurTentakel
// 25.05.23
//

#pragma once
#include <utility>
#include <memory>
#include "HLogicAlias.hpp"

[[nodiscard]] std::pair<bool, SpaceObject_ty> TryGetTarget(
	Fleet_ty_raw fleet, SpaceObject_ty_c target);
