//
// Purpur Tentakel
// 07.11.2022
//

#include "Planet.h"
#include "helper/HRandom.h"
#include "AppContext.h"
#include "Player.h"
#include "helper/HPrint.h"

Planet::Planet(unsigned int ID, vec2pos position, Player_ty player,
	bool isHomePlanet, int planetNumber)
	: Planet{ID, position, player, isHomePlanet, planetNumber, 0 } { }

Planet::Planet(unsigned int ID, vec2pos position, Player_ty player,
	bool isHomePlanet, int planetNumber, size_t ships)
	: SpaceObject{ ID, position, ships,  player }, m_isHomePlanet{ isHomePlanet },
	m_planetNumber{ planetNumber } {

	AppContext const & appContext{ AppContext::GetInstance() };

	if (m_isHomePlanet) {
		m_production = appContext.constants.planet.homeworldProduction;
		m_ships = m_production * appContext.constants.planet.startingHumanShipsMultiplicator;
	}
	else {
		Random& random{ Random::GetInstance() };
		size_t const r{ static_cast<size_t>(random.random(
			appContext.constants.planet.maxProduction -
			appContext.constants.planet.minProduction
		)) };
		m_production = r + appContext.constants.planet.minProduction;
		m_ships = m_production * appContext.constants.planet.startingGlobalShipsMultiplicator;
	}

	m_maxShips = appContext.constants.planet.maxShipsFactor * m_production;
}

bool Planet::IsHomePlanet() const {
	return m_isHomePlanet;
}

bool Planet::IsPlanet() const {
	return true;
}

size_t Planet::GetProduction() const {
	return m_production;
}

void Planet::SetDestroyed(bool isDestroyed) {
	m_isDestroyed = isDestroyed;
}
bool Planet::IsDestroyed() const {
	return m_isDestroyed;
}

int Planet::GetPlanetNumber() const{
	return m_planetNumber;
}

void Planet::Update(Galaxy_ty_raw) {
	m_ships += m_production;
	if (not m_player->IsHumanPlayer() and m_ships > m_maxShips) {
		m_ships = m_maxShips;
	}
	Print(
		PrintType::ONLY_DEBUG,
		"planet produced -> id: {} -> is human: {} -> ships: {}",
		m_ID,
		m_player->IsHumanPlayer(),
		m_ships
	);
}
