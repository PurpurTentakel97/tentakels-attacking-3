//
// PurpurTentakel
// 16.02.22
//

#pragma once
#include "SpaceObject.h"

class Fleet final : public SpaceObject {
private:
	SpaceObject_ty m_target;

public:
	/**
	 * ctor without ships.
	 * only initialization
	 */
	Fleet(unsigned int ID, vec2pos_ty position, Player_ty player, SpaceObject_ty target);
	/**
	 * ctor.
	 * only initialization.
	 */
	Fleet(unsigned int ID, vec2pos_ty position, size_t ships, Player_ty player, SpaceObject_ty target);

	/**
	 * returns if the current space object is a planet.
	 */
	[[nodiscard]] bool IsFleet() const override;

	/**
	 * returns the direct target of the fleet.
	 */
	[[nodiscard]] SpaceObject_ty GetTarget() const;
	/**
	 * returns the actual target of the fleet.
	 */
	[[nodiscard]] std::pair<bool, SpaceObject_ty> GetFairTarget() const;
	/**
	 * sets a new target.
	 */
	void SetTarget(SpaceObject_ty target);

	/**
	 * returns if the fleet is arrived at the direct target.
	 */
	[[nodiscard]] bool IsArrived() const;
	/**
	 * returns if the fleet arrived at the actual target it is moving to.
	 */
	[[nodiscard]] bool IsFarArrived() const;

	/**
	 * returns if the direct target is friendly.
	 */
	[[nodiscard]] bool IsFriendly() const;
	/**
	 * returns if the actual target is friendly.
	 */
	[[nodiscard]] bool IsFarFriendly() const;

	/**
	 * moves the fleet to the target.
	 */
	void Update(Galaxy_ty_raw galaxy) override;
};
