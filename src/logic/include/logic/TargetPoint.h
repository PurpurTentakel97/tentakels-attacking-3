//
// Purpur Tentakel
// 16.02.2022
//

#pragma once
#include "SpaceObject.h"

class TargetPoint : public SpaceObject {
private:

public:

	/**
	 * ctor from SpaceObject.
	 */
	using SpaceObject::SpaceObject;

	/**
	 * returns if the current space object is a planet.
	 */
	[[nodiscard]] bool IsTargetPoint() const override;

	void Update(Galaxy_ty_raw galaxy) override;
};
