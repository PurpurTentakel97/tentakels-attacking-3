//
// Purpur Tentakel
// 23.05.2023
//

#include "HLogicAlias.hpp"
#include <memory>

struct HFleetResult final {
	SpaceObject_ty origin;
	Fleet_ty fleet;
	SpaceObject_ty destination;
	bool valid;
};
