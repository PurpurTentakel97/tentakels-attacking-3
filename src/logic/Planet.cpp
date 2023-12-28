//
// Purpur Tentakel
// 07.11.2022
//

#include "Planet.hpp"
#include "Player.hpp"
#include <app/AppContext.hpp>
#include <helper/HPrint.hpp>
#include <helper/HRandom.hpp>

Planet::Planet(
        unsigned int const ID,
        vec2pos_ty_ref_c position,
        Player_ty player,
        bool const isHomePlanet,
        int planetNumber
)
    : Planet{ ID, position, std::move(player), isHomePlanet, planetNumber, 0 } { }

Planet::Planet(
        unsigned int const ID,
        vec2pos_ty_ref_c position,
        Player_ty player,
        bool const isHomePlanet,
        int planetNumber,
        size_t ships
)
    : SpaceObject{ ID, position, ships, std::move(player) },
      m_isHomePlanet{ isHomePlanet },
      m_planetNumber{ planetNumber } {

    AppContext const& appContext{ AppContext::GetInstance() };

    if (m_isHomePlanet) {
        m_production = appContext.constants.planet.homeworldProduction;
        m_ships = m_production * appContext.constants.planet.startingHumanShipsMultiplicator;
    } else {
        auto& random{ hlp::Random::GetInstance() };
        size_t const r{
            random.random(appContext.constants.planet.maxProduction - appContext.constants.planet.minProduction)
        };
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

void Planet::SetDestroyed(bool const isDestroyed) {
    m_isDestroyed = isDestroyed;
}

bool Planet::IsDestroyed() const {
    return m_isDestroyed;
}

int Planet::GetPlanetNumber() const {
    return m_planetNumber;
}

void Planet::Update(Galaxy_ty_raw) {
    m_ships += m_production;
    if (not m_player->IsHumanPlayer() and m_ships > m_maxShips) {
        m_ships = m_maxShips;
    }
    hlp::Print(
            hlp::PrintType::ONLY_DEBUG,
            "planet produced -> id: {} -> is human: {} -> ships: {}",
          m_ID,
          m_player->IsHumanPlayer(),
          m_ships);
}
