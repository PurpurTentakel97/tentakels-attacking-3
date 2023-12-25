//
// Purpur Tentakel
// 07.11.2022
//

#pragma once
#include "SpaceObject.h"

/**
 * the planet ia a space object.
 */
class Planet final : public SpaceObject {
private:
	using vec2pos = vec2pos_ty; ///< the type of the position
	bool m_isHomePlanet{ }; ///< contains if this planet is a home planet
	bool m_isDestroyed{ false }; ///< contains if the planet is destroyed
	int m_planetNumber; ///< contains the planet number
	size_t m_maxShips; ///< contains the max amount of ships the planet can hold by non human players
	size_t m_production; ///< contains the production hat gets add every round

public:
	/**
	 * ctor.
	 * initialize all values.
	 */
	Planet(unsigned int ID, vec2pos position, Player_ty player,
		bool isHomePlanet, int m_planetNumber);
	/**
	 * ctor.
	 * initialize all values.
	 * with ships
	 */
	Planet(unsigned int ID, vec2pos position, Player_ty player,
		bool isHomePlanet, int m_planetNumber, size_t ships);

	/**
	 * returns if the planet is a home planet.
	 */
	[[nodiscard]] bool IsHomePlanet() const;

	/**
	 * returns if the current space object is a planet.
	 */
	[[nodiscard]] bool IsPlanet() const override;

	/**
	 * returns the production count.
	 */
	[[nodiscard]] size_t GetProduction() const;
	/**
	 * returns the planet number.
	 */
	[[nodiscard]] int GetPlanetNumber() const;

	/**
	 * sets if the planet is destroyed.
	 */
	void SetDestroyed(bool isDestroyed);
	/**
	 * returns if the planet is destroyed.
	 */
	[[nodiscard]] bool IsDestroyed() const;

	/**
	 * products ships.
	 */
	void Update(Galaxy_ty_raw galaxy) override;
};
