//
// Purpur Tentakel
// 07.11.2022
//

#include "Planet.hpp"
#include "Player.hpp"
#include <app/AppContext.hpp>
#include <helper/HPrint.hpp>
#include <helper/HRandom.hpp>


namespace lgk {
    Planet::Planet(utl::usize const ID,
                   utl::vec2pos_ty_ref_c position,
                   Player_ty player,
                   bool const isHomePlanet,
                   utl::usize planetNumber)
        : Planet{ ID, position, std::move(player), isHomePlanet, planetNumber, 0 } { }

    Planet::Planet(utl::usize const ID,
                   utl::vec2pos_ty_ref_c position,
                   Player_ty player,
                   bool const isHomePlanet,
                   utl::usize planetNumber,
                   utl::usize ships)
        : SpaceObject{ ID, position, ships, std::move(player) },
          m_isHomePlanet{ isHomePlanet },
          m_planetNumber{ planetNumber } {

        app::AppContext_ty_c appContext{ app::AppContext::GetInstance() };

        if (m_isHomePlanet) {
            m_production = appContext.constants.g_planet.get_home_world_production();
            m_ships      = m_production * appContext.constants.g_planet.get_starting_human_ships_multiplier();
        } else {
            auto& random{ hlp::Random::GetInstance() };
            utl::usize const r{ random.random(appContext.constants.g_planet.get_max_production()
                                              - appContext.constants.g_planet.get_min_production()) };
            m_production = r + appContext.constants.g_planet.get_min_production();
            m_ships      = m_production * appContext.constants.g_planet.get_starting_global_ships_multiplier();
        }

        m_maxShips = appContext.constants.g_planet.get_max_ships_factor() * m_production;
    }

    bool Planet::IsHomePlanet() const {
        return m_isHomePlanet;
    }

    bool Planet::IsPlanet() const {
        return true;
    }

    utl::usize Planet::GetProduction() const {
        return m_production;
    }

    utl::usize Planet::GetPlanetNumber() const {
        return m_planetNumber;
    }

    void Planet::SetProductionProblemYears(utl::usize years) {
        m_productionProblemYears = years;
    }

    utl::usize Planet::GetProductionProblemYears() const {
        return m_productionProblemYears;
    }

    void Planet::Update(Galaxy_ty_raw) {
        if (m_productionProblemYears > 0) {
            --m_productionProblemYears;
            return;
        }

        m_ships += m_production;
        if (not m_player->IsHumanPlayer() and m_ships > m_maxShips) {
            m_ships = m_maxShips;
        }
        hlp::Print(hlp::PrintType::ONLY_DEBUG,
                   "planet produced -> id: {} -> is human: {} -> ships: {}",
                   m_ID,
                   m_player->IsHumanPlayer(),
                   m_ships);
    }
} // namespace lgk
