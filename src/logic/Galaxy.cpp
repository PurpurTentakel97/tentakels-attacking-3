//
// PurpurTentakel
// 08.11.22
//

#include "Galaxy.hpp"
#include "GetTarget.hpp"
#include "Player.hpp"
#include "RepresentationGenerator.hpp"
#include <app/AppContext.hpp>
#include <event/EventsUI.hpp>
#include <helper/HPrint.hpp>
#include <helper/HRandom.hpp>
#include <stdexcept>
#include <utils/FleetInstructionType.hpp>
#include <utils/ResultsUpdate.hpp>
#include <utils/ResultFleet.hpp>
#include <vector>

namespace lgk {
    // help Lambdas
    static auto popup = [](std::string const& text) {
        eve::ShowMessagePopUpEvent const popupEvent{
            app::AppContext::GetInstance().languageManager.Text("logic_galaxy_invalid_input_headline"), text, []() {}
        };
        app::AppContext::GetInstance().eventManager.InvokeEvent(popupEvent);
    };

    // helper
    utl::usize Galaxy::GetNextID() const {

        if (m_objects.empty()) {
            return 1;
        }

        utl::usize nextID{ 1 };
        while (true) {
            bool freeID{ true };
            for (auto& o : m_objects) {
                if (nextID == o->GetID()) {
                    freeID = false;
                    break;
                }
            }

            if (freeID) {
                return nextID;
            }

            ++nextID;
        }
    }

    void Galaxy::InitializePlanets(utl::usize planetCount,
                                   std::vector<Player_ty> const& players,
                                   Player_ty const& neutralPlayer) {

        auto const currentPlanet{ GenerateHomePlanets(players) };
        if (m_validGalaxy) {
            GenerateOtherPlanets(planetCount, currentPlanet, neutralPlayer);
        }
    }

    utl::usize Galaxy::GenerateHomePlanets(std::vector<Player_ty> const& players) {

        auto& random{ hlp::Random::GetInstance() };
        app::AppContext_ty_c appContext{ app::AppContext::GetInstance() };
        utl::usize currentPlanet{ 1 };


        for (auto& p : players) {
            utl::usize counter{ 0 };
            while (true) {
                utl::vec2pos_ty_c newPosition{
                    static_cast<int>(random.random(static_cast<std::mt19937_64::result_type>(m_size.x))),
                    static_cast<int>(random.random(static_cast<std::mt19937_64::result_type>(m_size.y)))
                };

                auto const newPlanet = std::make_shared<Planet>(GetNextID(), newPosition, p, true, currentPlanet);

                if (IsValidNewPlanet(newPlanet, appContext)) {
                    m_objects.push_back(newPlanet);
                    m_planets.push_back(newPlanet);
                    ++currentPlanet;
                    break;
                }

                ++counter;

                if (counter > 10) {
                    m_validGalaxy = false;
                    return 0;
                }
            }
        }

        return currentPlanet;
    }

    void Galaxy::GenerateOtherPlanets(utl::usize const planetCount, utl::usize currentPlanet, Player_ty const& player) {

        app::AppContext_ty_c appContext{ app::AppContext::GetInstance() };
        auto& random{ hlp::Random::GetInstance() };


        for (; static_cast<utl::usize>(currentPlanet) <= planetCount; ++currentPlanet) {
            utl::usize counter{ 0 };
            while (true) {
                utl::vec2pos_ty_c newPosition{
                    static_cast<int>(random.random(static_cast<std::mt19937_64::result_type>(m_size.x))),
                    static_cast<int>(random.random(static_cast<std::mt19937_64::result_type>(m_size.y)))
                };

                auto const newPlanet = std::make_shared<Planet>(GetNextID(), newPosition, player, false, currentPlanet);

                if (IsValidNewPlanet(newPlanet, appContext)) {
                    m_objects.push_back(newPlanet);
                    m_planets.push_back(newPlanet);
                    break;
                }

                ++counter;

                if (counter > 10) {
                    m_validGalaxy = false;
                    return;
                }
            }
        }
    }

    bool Galaxy::IsValidNewPlanet(Planet_ty const& newPlanet, app::AppContext_ty_c appContext) const {
        bool validPlanet{ true };

        // works because Home Planets are generated first.
        auto const factor = newPlanet->IsHomePlanet() ? appContext.constants.planet.homeworldSpacing
                                                      : appContext.constants.planet.globalSpacing;
        double const spacing{ m_size.Length() * static_cast<double>(factor) };

        for (auto& p : m_planets) {
            double const currentSpacing{ (p->GetPos() - newPlanet->GetPos()).Length() };
            if (currentSpacing < spacing) {
                validPlanet = false;
                break;
            }
        }

        return validPlanet;
    }

    void Galaxy::DeletePlanet(Planet_ty const& planet) {
        m_planets.erase(std::remove_if(m_planets.begin(),
                                       m_planets.end(),
                                       [planet](Planet_ty_c currentPlanet) {
                                           return planet->GetID() == currentPlanet->GetID();
                                       }),
                        m_planets.end());
        m_objects.erase(
                std::remove_if(m_objects.begin(),
                               m_objects.end(),
                               [planet](SpaceObject_ty const& object) { return planet->GetID() == object->GetID(); }),
                m_objects.end());

        app::AppContext::GetInstance().aliasManager.DeleteSpaceObjectAlias(planet->GetID());

        hlp::Print(hlp::PrintType::ONLY_DEBUG,
                   "delete fleet -> id: {} -> player: {} -> ships: {}",
                   planet->GetID(),
                   planet->GetPlayer()->GetID(),
                   planet->GetShipCount());
    }

    // Fleet
    bool Galaxy::IsValidFleet(utl::usize const ID) const {

        for (auto const& f : m_fleets) {
            if (f->GetID() == ID) {
                return true;
            }
        }
        return false;
    }

    Fleet_ty Galaxy::GetFleetByID(utl::usize const ID) const {
        for (auto const& f : m_fleets) {
            if (f->GetID() == ID) {
                return f;
            }
        }

        throw std::runtime_error("no fleet with this ID: " + std::to_string(ID));
    }

    [[nodiscard]] Fleet_ty Galaxy::TryGetExistingFleetByOriginAndDestination(SpaceObject_ty const& origin,
                                                                             SpaceObject_ty const& destination) const {

        for (auto const& f : m_fleets) {
            if (f->GetPos() == origin->GetPos()) {
                if (f->GetTarget()->GetID() == destination->GetID()) {
                    return f;
                }
            }
        }

        return nullptr;
    }

    utl::ResultFleet Galaxy::AddFleetFromPlanet(eve::SendFleetInstructionEvent const* event,
                                                Player_ty const& currentPlayer) {
        // check origin id
        if (event->GetOrigin() > m_planets.size()) {
            popup(app::AppContext::GetInstance().languageManager.Text("logic_galaxy_input_origin_planet_high_text"));
            hlp::Print(hlp::PrintType::ONLY_DEBUG, "ID to high for a planet: {}", event->GetOrigin());
            return { nullptr, nullptr, nullptr, false };
        }

        // check origin
        auto const originPlanet{ GetPlanetByID(event->GetOrigin()) };
        if (originPlanet->GetPlayer() != currentPlayer) {
            popup(app::AppContext::GetInstance().languageManager.Text("logic_galaxy_not_your_origin_planet_text"));
            hlp::Print(hlp::PrintType::ONLY_DEBUG, "origin planet does not belong to current player");
            return { nullptr, nullptr, nullptr, false };
        }
        if (originPlanet->GetShipCount() < event->GetShipCount()) {
            popup(app::AppContext::GetInstance().languageManager.Text("logic_galaxy_not_enough_ships_on_planet_text",
                                                                      event->GetOrigin()));
            hlp::Print(hlp::PrintType::ONLY_DEBUG,
                       "ship count on origin planet too low -> current: {} -> requested: {}",
                       originPlanet->GetShipCount(),
                       event->GetShipCount());
            return { nullptr, nullptr, nullptr, false };
        }

        // get destination
        auto const destination = GetOrGenerateDestination(event->GetDestination(),
                                                          static_cast<int>(event->GetDestinationX()),
                                                          static_cast<int>(event->GetDestinationY()),
                                                          currentPlayer);

        if (destination->IsPlanet()) {
            if (destination->GetID() == originPlanet->GetID()) {
                popup(app::AppContext::GetInstance().languageManager.Text("logic_galaxy_are_same_planets_text"));
                hlp::Print(hlp::PrintType::ONLY_DEBUG,
                           "origin and destination are the same -> origin: {} -> destination: {}",
                           originPlanet->GetID(),
                           destination->GetID());
                return { nullptr, nullptr, nullptr, false };
            }
        }
        if (destination->GetPlayer() != currentPlayer and not destination->IsPlanet()) {
            if (not destination->IsDiscovered()) {
                popup(app::AppContext::GetInstance().languageManager.Text("logic_galaxy_destination_blocked_text"));
                hlp::Print(hlp::PrintType::ONLY_DEBUG, "chosen destination is blocked");
                return { nullptr, nullptr, nullptr, false };
            }
        }
        if (auto const fleet = TryGetExistingFleetByOriginAndDestination(originPlanet, destination)) {
            *originPlanet -= event->GetShipCount();
            *fleet += event->GetShipCount();
            hlp::Print(hlp::PrintType::ONLY_DEBUG,
                       "moved ships in existing fleet -> origin: {} -> fleet: {} -> ships: {}",
                       originPlanet->GetID(),
                       fleet->GetID(),
                       event->GetShipCount());
            return { originPlanet, fleet, nullptr, true };
        }

        // create fleet
        auto const fleet = std::make_shared<Fleet>(
                GetNextID(), originPlanet->GetPos(), event->GetShipCount(), currentPlayer, destination);

        m_objects.push_back(fleet);
        m_fleets.push_back(fleet);

        // remove fleet ships from origin planet
        *originPlanet -= *fleet;

        hlp::Print(hlp::PrintType::ONLY_DEBUG,
                   "generated a new fleet -> id: {} -> player: {} -> position: {} -> target: {} -> ships: {}",
                   fleet->GetID(),
                   fleet->GetPlayer()->GetID(),
                   fleet->GetPos().ToString(),
                   fleet->GetTarget()->GetID(),
                   fleet->GetShipCount());

        return { originPlanet, fleet, destination, true };
    }

    utl::ResultFleet Galaxy::AddFleetFromFleet(eve::SendFleetInstructionEvent const* const event,
                                               Player_ty const& currentPlayer) {
        // check if origin ID is existing
        if (not IsValidFleet(event->GetOrigin())) {
            popup(app::AppContext::GetInstance().languageManager.Text("logic_galaxy_not_existing_fleet_text",
                                                                      event->GetOrigin()));
            hlp::Print(hlp::PrintType::ONLY_DEBUG, "id not valid for a fleet: ", event->GetOrigin());
            return { nullptr, nullptr, nullptr, false };
        }

        // check origin
        auto const& origin{ GetFleetByID(event->GetOrigin()) };
        if (origin->GetPlayer() != currentPlayer) {
            popup(app::AppContext::GetInstance().languageManager.Text("logic_galaxy_not_your_origin_fleet_text"));
            hlp::Print(hlp::PrintType::ONLY_DEBUG, "the origin fleet does not belong to the current player");
            return { nullptr, nullptr, nullptr, false };
        }
        if (origin->GetShipCount() < event->GetShipCount()) {
            popup(app::AppContext::GetInstance().languageManager.Text("logic_galaxy_not_enough_ships_in_fleet_text",
                                                                      event->GetOrigin()));
            hlp::Print(hlp::PrintType::ONLY_DEBUG,
                       "ship count on origin fleet too low -> current: {} -> requested: {}",
                       origin->GetShipCount(),
                       event->GetShipCount());
            return { nullptr, nullptr, nullptr, false };
        }
        if (origin->GetEngineProblemYears() > 0) {
            popup(app::AppContext::GetInstance().languageManager.Text(
                    "logic_fleet_currently_broken_text", origin->GetID(), origin->GetEngineProblemYears()));
            hlp::Print(hlp::PrintType::ONLY_DEBUG,
                       "Fleet {} is broken for the next {} years.",
                       origin->GetID(),
                       origin->GetEngineProblemYears());
            return { nullptr, nullptr, nullptr, false };
        }

        // get destination
        auto const destination{ GetOrGenerateDestination(event->GetDestination(),
                                                         static_cast<int>(event->GetDestinationX()),
                                                         static_cast<int>(event->GetDestinationY()),
                                                         currentPlayer) };

        // check destination
        if (destination->GetPlayer() != currentPlayer and not destination->IsPlanet()) {
            if (not destination->IsDiscovered()) {
                popup(app::AppContext::GetInstance().languageManager.Text("logic_galaxy_destination_blocked_text"));
                hlp::Print(hlp::PrintType::ONLY_DEBUG, "chosen destination is blocked");
                return { nullptr, nullptr, nullptr, false };
            }
        }

        // shift ships directly
        if (destination->GetPos() == origin->GetPos()) {
            *origin -= event->GetShipCount();
            *destination += event->GetShipCount();
            hlp::Print(hlp::PrintType::ONLY_DEBUG,
                       "moved ships directly -> origin: {} -> destination: {} -> ships: {}",
                       origin->GetID(),
                       destination->GetID(),
                       event->GetShipCount());
            return { origin, nullptr, destination, true };
        }
        if (auto const fleet{ TryGetExistingFleetByOriginAndDestination(origin, destination) }) {
            *origin -= event->GetShipCount();
            *fleet += event->GetShipCount();
            hlp::Print(hlp::PrintType::ONLY_DEBUG,
                       "moved ships in existing fleet -> origin: {} -> fleet: {} -> ships: {}",
                       origin->GetID(),
                       fleet->GetID(),
                       event->GetShipCount());
            return { origin, fleet, nullptr, true };
        }

        // redirect fleet
        if (origin->GetShipCount() == event->GetShipCount()) {
            origin->SetTarget(destination);
            hlp::Print(hlp::PrintType::ONLY_DEBUG, "new target for fleet: {}", destination->GetID());
            return { origin, nullptr, destination, true };
        }

        // create fleet
        auto const fleet = std::make_shared<Fleet>(
                GetNextID(), origin->GetPos(), event->GetShipCount(), currentPlayer, destination);

        if (destination->IsFleet()) {
            auto const result{ hlp::TryGetTarget(fleet.get(), fleet->GetTarget()) };
            if (not result.first) { // not valid
                popup(app::AppContext::GetInstance().languageManager.Text("logic_galaxy_fleet_round_robin_text"));
                hlp::Print(hlp::PrintType::ONLY_DEBUG, "new fleet would generate a round robin");
                return { nullptr, nullptr, nullptr, false };
            }
        }

        m_objects.push_back(fleet);
        m_fleets.push_back(fleet);

        // remove fleet ships from origin planet
        *origin -= *fleet;

        hlp::Print(hlp::PrintType::ONLY_DEBUG,
                   "generated a new fleet -> id: {} -> player: {} -> position: {} -> target: {} -> ships: {}",
                   fleet->GetID(),
                   fleet->GetPlayer()->GetID(),
                   fleet->GetPos().ToString(),
                   fleet->GetTarget()->GetID(),
                   fleet->GetShipCount());

        return { origin, fleet, destination, true };
    }

    utl::ResultFleet Galaxy::AddFleetFromTargetPoint(eve::SendFleetInstructionEvent const* const event,
                                                     Player_ty const& currentPlayer) {
        // check if origin ID is existing
        if (not IsValidTargetPoint(event->GetOrigin())) {
            popup(app::AppContext::GetInstance().languageManager.Text("logic_galaxy_not_existing_target_point_text",
                                                                      event->GetOrigin()));
            hlp::Print(hlp::PrintType::ONLY_DEBUG, "id not valid for a target point: {}", event->GetOrigin());
            return { nullptr, nullptr, nullptr, false };
        }

        // check origin
        auto const& origin{ GetTargetPointByID(event->GetOrigin()) };
        if (origin->GetPlayer() != currentPlayer) {
            popup(app::AppContext::GetInstance().languageManager.Text(
                    "logic_galaxy_not_your_origin_target_point_text"));
            hlp::Print(hlp::PrintType::ONLY_DEBUG, "the origin target point does not belong to the current player");
            return { nullptr, nullptr, nullptr, false };
        }
        if (origin->GetShipCount() < event->GetShipCount()) {
            popup(app::AppContext::GetInstance().languageManager.Text(
                    "logic_galaxy_not_enough_ships_at_target_point_text", event->GetOrigin()));
            hlp::Print(hlp::PrintType::ONLY_DEBUG,
                       "ship count on origin target point to low -> current: {} -> requested: {}",
                       origin->GetShipCount(),
                       event->GetShipCount());
            return { nullptr, nullptr, nullptr, false };
        }

        // get destination
        auto const destination{ GetOrGenerateDestination(event->GetDestination(),
                                                         static_cast<int>(event->GetDestinationX()),
                                                         static_cast<int>(event->GetDestinationY()),
                                                         currentPlayer) };

        if (destination->GetPlayer() != currentPlayer and not destination->IsPlanet()) {
            if (not destination->IsDiscovered()) {
                popup(app::AppContext::GetInstance().languageManager.Text("logic_galaxy_destination_blocked_text"));
                hlp::Print(hlp::PrintType::ONLY_DEBUG, "chosen destination is blocked");
                return { nullptr, nullptr, nullptr, false };
            }
        }

        if (origin->GetPos() == destination->GetPos()) {
            *origin -= event->GetShipCount();
            *destination += event->GetShipCount();
            hlp::Print(hlp::PrintType::ONLY_DEBUG,
                       "moved ships directly -> origin: {} -> destination: {} -> ships: {}",
                       origin->GetID(),
                       destination->GetID(),
                       event->GetShipCount());
            return { origin, nullptr, destination, true };
        }
        if (auto const& fleet = TryGetExistingFleetByOriginAndDestination(origin, destination)) {
            *origin -= event->GetShipCount();
            *destination += event->GetShipCount();
            hlp::Print(hlp::PrintType::ONLY_DEBUG,
                       "moved ships in existing fleet -> origin: {} -> fleet: {} -> ships: {}",
                       origin->GetID(),
                       fleet->GetID(),
                       event->GetShipCount());
            return { origin, nullptr, destination, true };
        }

        // get fleet
        auto const fleet = std::make_shared<Fleet>(
                GetNextID(), origin->GetPos(), event->GetShipCount(), currentPlayer, destination);

        m_objects.push_back(fleet);
        m_fleets.push_back(fleet);

        // manage ships
        *origin -= *fleet;

        hlp::Print(hlp::PrintType::ONLY_DEBUG,
                   "generated a new fleet -> id: {} -> player: {} -> position: {} -> target: {} -> ships: {}",
                   fleet->GetID(),
                   fleet->GetPlayer()->GetID(),
                   fleet->GetPos().ToString(),
                   fleet->GetTarget()->GetID(),
                   fleet->GetShipCount());

        return { origin, fleet, destination, true };
    }

    std::vector<Fleet_ty> Galaxy::GetFleetsOfTarget(SpaceObject_ty const& object) const {
        std::vector<Fleet_ty> vec{};

        for (auto const& fleet : m_fleets) {
            if (fleet->GetTarget()->GetID() == object->GetID()) {
                vec.push_back(fleet);
            }
        }

        return vec;
    }

    void Galaxy::DeleteFleet(std::vector<Fleet_ty> const& fleets) {
        auto const& containsFleet{ [fleets](Fleet_ty const& fleet) -> bool {
            for (auto const& fleet_r : fleets) {
                if (fleet->GetID() == fleet_r->GetID()) {
                    return true;
                }
            }
            return false;
        } };
        auto const& containsObject{ [fleets](SpaceObject_ty const& object) -> bool {
            for (auto const& fleet : fleets) {
                if (object->GetID() == fleet->GetID()) {
                    return true;
                }
            }
            return false;
        } };

        for (auto const& fleet : fleets) {
            hlp::Print(hlp::PrintType::ONLY_DEBUG,
                       "delete fleet -> id: {} -> player: {} -> ships: {}",
                       fleet->GetID(),
                       fleet->GetPlayer()->GetID(),
                       fleet->GetShipCount());
        }

        auto const newStart1{ std::remove_if(m_fleets.begin(), m_fleets.end(), containsFleet) };
        m_fleets.erase(newStart1, m_fleets.end());

        auto const newStart2{ std::remove_if(m_objects.begin(), m_objects.end(), containsObject) };
        m_objects.erase(newStart2, m_objects.end());

        for (auto const& f : fleets) {
            app::AppContext::GetInstance().aliasManager.DeleteSpaceObjectAlias(f->GetID());
        }
    }

    void Galaxy::DeleteFleet(Fleet_ty const& fleet) {
        m_fleets.erase(
                std::remove_if(m_fleets.begin(),
                               m_fleets.end(),
                               [fleet](Fleet_ty_c currentFleet) { return fleet->GetID() == currentFleet->GetID(); }),
                m_fleets.end());
        m_objects.erase(
                std::remove_if(m_objects.begin(),
                               m_objects.end(),
                               [fleet](SpaceObject_ty const& object) { return fleet->GetID() == object->GetID(); }),
                m_objects.end());

        app::AppContext::GetInstance().aliasManager.DeleteSpaceObjectAlias(fleet->GetID());

        hlp::Print(hlp::PrintType::ONLY_DEBUG,
                   "delete fleet -> id: {} -> player: {} -> ships: {}",
                   fleet->GetID(),
                   fleet->GetPlayer()->GetID(),
                   fleet->GetShipCount());
    }

    bool Galaxy::IsValidTargetPoint(utl::usize const ID) const {
        for (auto const& tp : m_targetPoints) {
            if (tp->GetID() == ID) {
                return true;
            }
        }
        return false;
    }

    TargetPoint_ty Galaxy::GetTargetPointByID(utl::usize const ID) const {
        for (auto const& tp : m_targetPoints) {
            if (tp->GetID() == ID) {
                return tp;
            }
        }

        throw std::runtime_error("no Target Point with ID " + std::to_string(ID));
    }

    SpaceObject_ty Galaxy::GetOrGenerateDestination(utl::usize const ID,
                                                    int const X,
                                                    int const Y,
                                                    Player_ty const& currentPlayer) {

        for (auto& object : m_objects) {

            if (object->GetID() == ID) {
                return object;
            }

            auto const pos = object->GetPos();
            if (pos.x == X && pos.y == Y) {
                auto const remove{ (object->IsTargetPoint() or object->IsPlanet())
                                   or (object->IsFleet() and object->GetPlayer() == currentPlayer) };
                if (remove) {
                    return object;
                }
            }
        }

        utl::vec2pos_ty_c point{ X, Y };
        auto const targetPoint = std::make_shared<TargetPoint>(GetNextID(), point, currentPlayer);

        m_objects.push_back(targetPoint);
        m_targetPoints.push_back(targetPoint);

        return targetPoint;
    }

    void Galaxy::CheckDeleteTargetPoints() {
        // get
        std::vector<TargetPoint_ty> toDelete{};
        for (auto const& t : m_targetPoints) {
            if (t->GetShipCount() > 0) {
                continue;
            }
            auto const& origins{ GetFleetsOfTarget(t) };
            if (not origins.empty()) {
                continue;
            }
            toDelete.push_back(t);
            hlp::Print(hlp::PrintType::ONLY_DEBUG,
                       "delete target point -> id: {} -> ships: {} -> origin count: {}",
                       t->GetID(),
                       t->GetShipCount(),
                       origins.size());
        }

        // delete
        auto const containsTargetPoint{ [toDelete](SpaceObject_ty const& d_t) -> bool {
            for (auto const& o_t : toDelete) {
                if (d_t->GetID() == o_t->GetID()) {
                    return true;
                }
            }
            return false;
        } };

        auto const start1{ std::remove_if(m_targetPoints.begin(), m_targetPoints.end(), containsTargetPoint) };
        m_targetPoints.erase(start1, m_targetPoints.end());

        auto const start2{ std::remove_if(m_objects.begin(), m_objects.end(), containsTargetPoint) };
        m_objects.erase(start2, m_objects.end());

        for (auto const& t : toDelete) {
            app::AppContext::GetInstance().aliasManager.DeleteSpaceObjectAlias(t->GetID());
        }
    }

    // black hole
    BlackHole_ty Galaxy::AddBlackHoleWithoutCheck(utl::vec2pos_ty position, Player_ty invalid_player) {
        auto const blackHole = std::make_shared<BlackHole>(GetNextID(), position, std::move(invalid_player));
        m_objects.push_back(blackHole);
        m_blackHoles.push_back(blackHole);
        return blackHole;
    }

    // update
    std::vector<Fleet_ty> Galaxy::UpdateFleetTargets(std::vector<Fleet_ty> const& fleets,
                                                     SpaceObject_ty const& currentFleet,
                                                     SpaceObject_ty const& target) {
        std::vector<Fleet_ty> emptyFleets{};
        for (auto const& fleet : fleets) {
            if (fleet->GetPlayer() == currentFleet->GetPlayer()) {
                fleet->SetTarget(target);
                hlp::Print(hlp::PrintType::ONLY_DEBUG,
                           "redirect fleet -> id: {} -> old target: {} -> new target: {}",
                           fleet->GetID(),
                           currentFleet->GetID(),
                           target->GetID());
            } else {
                auto targetPoint = std::make_shared<TargetPoint>(GetNextID(), fleet->GetPos(), fleet->GetPlayer());
                targetPoint->TransferShipsFrom(fleet.get());
                m_objects.push_back(targetPoint);
                m_targetPoints.push_back(targetPoint);
                emptyFleets.push_back(fleet);
                hlp::Print(
                        hlp::PrintType::ONLY_DEBUG,
                        "created a new target point for fleet -> fleet id: {} -> target point id: {} -> fleet ships: "
                        "{} -> "
                        "target point ships: {}",
                        fleet->GetID(),
                        targetPoint->GetID(),
                        fleet->GetShipCount(),
                        targetPoint->GetShipCount());

                auto origins{ GetFleetsOfTarget(fleet) };
                auto results{ UpdateFleetTargets(origins, fleet, targetPoint) };
                if (not results.empty()) {
                    for (auto const& result : results) {
                        emptyFleets.push_back(result);
                    }
                }
            }
        }
        return emptyFleets;
    }

    std::vector<utl::ResultMerge> Galaxy::CheckArrivingFriendlyFleets() {
        std::vector<utl::ResultMerge> mergeResult{};
        for (auto const& fleet : m_fleets) {

            if (fleet->GetShipCount() == 0) {
                continue;
            } // no ships to transfer

            // arriving directly at the far target where the fleet is flying to at the update
            if (fleet->IsFarFriendly() and fleet->IsFarArrived()) {
                auto [valid, target]{ hlp::TryGetTarget(fleet.get(), fleet->GetTarget()) };

                if (valid) {
                    auto const shipCount{ fleet->GetShipCount() };
                    target->TransferShipsFrom(fleet.get());
                    mergeResult.emplace_back(GenPlayerRep(fleet->GetPlayer().get()),
                                             GenSingleSpaceObjectRep(fleet),
                                             GenSingleSpaceObjectRep(fleet->GetTarget()),
                                             shipCount);

                    hlp::Print(hlp::PrintType::ONLY_DEBUG,
                               "fleet arrived far -> id: {} -> target: {} -> ships: {}",
                               fleet->GetID(),
                               target->GetID(),
                               shipCount);
                } else {
                    hlp::Print(hlp::PrintType::ONLY_DEBUG,
                               "far fleet target was not valid while arriving at far target -> fleet id {}",
                               fleet->GetID());
                }
            }
            // arriving at the direct target of the fleet
            else if (fleet->IsFriendly() and fleet->IsArrived()) {

                auto target{ fleet->GetTarget() };
                auto const shipCount{ fleet->GetShipCount() };
                target->TransferShipsFrom(fleet.get());
                mergeResult.emplace_back(GenPlayerRep(fleet->GetPlayer().get()),
                                         GenSingleSpaceObjectRep(fleet),
                                         GenSingleSpaceObjectRep(fleet->GetTarget()),
                                         shipCount);

                hlp::Print(hlp::PrintType::ONLY_DEBUG,
                           "fleet arrived direct -> id: {} -> target: {} -> ships: {}",
                           fleet->GetID(),
                           target->GetID(),
                           shipCount);
            }
        }
        return mergeResult;
    }

    std::vector<utl::ResultMerge> Galaxy::CheckMergingFriendlyFleets() {
        std::vector<utl::ResultMerge> mergeResult{};

        for (auto const& fleet_lhs : m_fleets) {
            // clang-format off
            auto const skip_lhs = fleet_lhs->GetShipCount()          == 0
                               or fleet_lhs->GetEngineProblemYears() >  0;
            // clang-format on
            if (skip_lhs) {
                continue;
            }
            for (auto const& fleet_rhs : m_fleets) {
                // clang-format off
                auto const skip_rhs = fleet_lhs->GetID()                 == fleet_rhs->GetID()
                                   or fleet_rhs->GetShipCount()          == 0
                                   or fleet_rhs->GetEngineProblemYears() >  0;
                // clang-format on
                if (skip_rhs) {
                    continue;
                }

                auto [valid_lhs, target_lhs]{ fleet_lhs->GetFairTarget() };
                if (not valid_lhs) {
                    target_lhs = fleet_lhs->GetTarget();
                }
                auto [valid_rhs, target_rhs]{ fleet_rhs->GetFairTarget() };
                if (not valid_rhs) {
                    target_rhs = fleet_rhs->GetTarget();
                }

                bool const merge_able{ fleet_lhs->GetPlayer() == fleet_rhs->GetPlayer()
                                       and target_lhs->GetID() == target_rhs->GetID()
                                       and fleet_lhs->IsInFightRange(fleet_rhs) };

                if (merge_able) {
                    mergeResult.emplace_back(GenPlayerRep(fleet_lhs->GetPlayer().get()),
                                             GenSingleSpaceObjectRep(fleet_lhs),
                                             GenSingleSpaceObjectRep(fleet_rhs),
                                             fleet_rhs->GetShipCount());
                    fleet_lhs->TransferShipsFrom(fleet_rhs.get());

                    hlp::Print(
                            hlp::PrintType::ONLY_DEBUG,
                            "fleets merged -> fleet lhs id: {} -> fleet rhs id: {} -> ships lhs: {} -> ships rhs: {}",
                            fleet_lhs->GetID(),
                            fleet_rhs->GetID(),
                            fleet_lhs->GetShipCount(),
                            fleet_rhs->GetShipCount());
                }
            }
        }

        return mergeResult;
    }

    void Galaxy::CheckDeleteFleetsWithoutShips() {
        std::vector<Fleet_ty> toDelete{};
        for (auto const& fleet : m_fleets) {
            if (fleet->GetShipCount() != 0) {
                continue;
            }

            auto const& origins{ GetFleetsOfTarget(fleet) };
            auto results{ UpdateFleetTargets(origins, fleet, fleet->GetTarget()) };
            if (not results.empty()) {
                for (auto const& result : results) {
                    toDelete.push_back(result);
                }
            }

            toDelete.push_back(fleet);
        }
        DeleteFleet(toDelete);
    }

    std::vector<utl::ResultFight> Galaxy::SimulateFight() {
        // Fleet Planet
        hlp::Print(hlp::PrintType::ONLY_DEBUG, "-> -> fights fleet against planet");
        std::vector<utl::ResultFight> results{ SimulateFightFleetPlanet() };

        // Fleet TargetPoint
        hlp::Print(hlp::PrintType::ONLY_DEBUG, "-> -> fights fleet against target point");
        std::vector<utl::ResultFight> singleResult{ SimulateFightFleetTargetPoint() };
        std::copy(singleResult.begin(), singleResult.end(), std::back_inserter(results));

        // Fleet Fleet
        hlp::Print(hlp::PrintType::ONLY_DEBUG, "-> -> fights fleet against fleet");
        singleResult = { SimulateFightFleetFleet() };
        std::copy(singleResult.begin(), singleResult.end(), std::back_inserter(results));

        // planet Fleet
        hlp::Print(hlp::PrintType::ONLY_DEBUG, "-> -> fight planet against fleet");
        singleResult = { SimulateFightPlanetFleet() };
        std::copy(singleResult.begin(), singleResult.end(), std::back_inserter(results));

        // TargetPoint Fleet
        hlp::Print(hlp::PrintType::ONLY_DEBUG, "-> -> fight target point against fleet");
        singleResult = { SimulateFightTargetPointFleet() };
        std::copy(singleResult.begin(), singleResult.end(), std::back_inserter(results));

        // TargetPoint TargetPoint
        hlp::Print(hlp::PrintType::ONLY_DEBUG, "-> -> fight target point against target point");
        singleResult = { SimulateFightTargetPointTargetPoint() };
        std::copy(singleResult.begin(), singleResult.end(), std::back_inserter(results));

        // planet TargetPoint
        hlp::Print(hlp::PrintType::ONLY_DEBUG, "-> -> fight planet against target point");
        singleResult = { SimulateFightPlanetTargetPoint() };
        std::copy(singleResult.begin(), singleResult.end(), std::back_inserter(results));

        return results;
    }

    std::vector<utl::ResultFight> Galaxy::SimulateFightFleetPlanet() {
        std::vector<utl::ResultFight> results{};
        for (auto const& fleet : m_fleets) {
            for (auto const& planet : m_planets) {
                if (fleet->GetPos() == planet->GetPos()) {
                    auto const result{ Fight(planet, fleet) };
                    if (result.IsValid()) {
                        results.push_back(result);

                        if (planet->GetShipCount() == 0) {
                            planet->SetPlayer(fleet->GetPlayer());
                            planet->TransferShipsFrom(fleet.get());
                        }
                    }
                }
            }
        }

        return results;
    }

    std::vector<utl::ResultFight> Galaxy::SimulateFightFleetTargetPoint() {
        std::vector<utl::ResultFight> results{};

        for (auto const& fleet : m_fleets) {
            for (auto const& targetPoint : m_targetPoints) {
                if (fleet->GetPos() == targetPoint->GetPos()) {
                    auto const& result{ Fight(targetPoint, fleet) };
                    if (result.IsValid()) {
                        results.push_back(result);

                        if (targetPoint->GetShipCount() == 0) {
                            targetPoint->SetPlayer(fleet->GetPlayer());
                            targetPoint->TransferShipsFrom(fleet.get());
                        }
                    }
                }
            }
        }

        return results;
    }

    std::vector<utl::ResultFight> Galaxy::SimulateFightFleetFleet() {
        std::vector<utl::ResultFight> results{};
        auto& random{ hlp::Random::GetInstance() };

        for (auto const& fleet_lhs : m_fleets) {
            for (auto const& fleet_rhs : m_fleets) {
                if (fleet_lhs->GetID() == fleet_rhs->GetID()) {
                    continue;
                }

                if (fleet_lhs->IsInFightRange(fleet_rhs)) {
                    auto const isSwitch{ random.random(2) };
                    utl::ResultFight result{};
                    if (isSwitch) {
                        result = Fight(fleet_rhs, fleet_lhs);
                    } else {
                        result = Fight(fleet_lhs, fleet_rhs);
                    }

                    if (result.IsValid()) {
                        results.push_back(result);
                    }
                }
            }
        }

        return results;
    }

    std::vector<utl::ResultFight> Galaxy::SimulateFightPlanetFleet() {
        std::vector<utl::ResultFight> results{};

        if (not app::AppContext::GetInstance().constants.fight.isFightPlanetFleet) {
            hlp::Print(hlp::PrintType::ONLY_DEBUG, "-> -> -> fights planet : fleet are disabled -> no simulation");
            return results;
        }

        for (auto const& planet : m_planets) {
            for (auto const& fleet : m_fleets) {
                if (planet->IsInFightRange(fleet)) {
                    auto const& result{ Fight(planet, fleet) };
                    if (result.IsValid()) {
                        results.push_back(result);
                    }
                }
            }
        }

        return results;
    }

    std::vector<utl::ResultFight> Galaxy::SimulateFightTargetPointFleet() {
        std::vector<utl::ResultFight> results{};

        if (not app::AppContext::GetInstance().constants.fight.isFightTargetPointFleet) {
            hlp::Print(hlp::PrintType::ONLY_DEBUG,
                       "-> -> -> fights target point : fleet are disabled -> no simulation");
            return results;
        }

        for (auto const& targetPoint : m_targetPoints) {
            for (auto const& fleet : m_fleets) {
                if (targetPoint->IsInFightRange(fleet)) {
                    auto const& result{ Fight(targetPoint, fleet) };
                    if (result.IsValid()) {
                        results.push_back(result);
                    }
                }
            }
        }

        return results;
    }

    std::vector<utl::ResultFight> Galaxy::SimulateFightTargetPointTargetPoint() {
        std::vector<utl::ResultFight> results{};

        if (not app::AppContext::GetInstance().constants.fight.isFightTargetPointTargetPoint) {
            hlp::Print(hlp::PrintType::ONLY_DEBUG,
                       "-> -> -> fights target point : target point are disabled -> no simulation");
            return results;
        }

        auto& random{ hlp::Random::GetInstance() };
        for (auto const& targetPoint_lhs : m_targetPoints) {
            for (auto const& targetPoint_rhs : m_targetPoints) {
                if (targetPoint_lhs->GetID() == targetPoint_rhs->GetID()) {
                    continue;
                }

                if (targetPoint_lhs->IsInFightRange(targetPoint_rhs)) {
                    auto const isSwitch{ random.random(2) };
                    utl::ResultFight result{};
                    if (isSwitch) {
                        result = Fight(targetPoint_rhs, targetPoint_lhs);
                    } else {
                        result = Fight(targetPoint_lhs, targetPoint_rhs);
                    }

                    if (result.IsValid()) {
                        results.push_back(result);
                    }
                }
            }
        }

        return results;
    }

    std::vector<utl::ResultFight> Galaxy::SimulateFightPlanetTargetPoint() {
        std::vector<utl::ResultFight> results{};

        if (not app::AppContext::GetInstance().constants.fight.isFightPlanetTargetPoint) {
            hlp::Print(hlp::PrintType::ONLY_DEBUG,
                       "-> -> -> fights planet : target point are disabled -> no simulation");
            return results;
        }

        for (auto const& planet : m_planets) {
            for (auto const& targetPoint : m_targetPoints) {
                if (planet->IsInFightRange(targetPoint)) {
                    auto const& result{ Fight(planet, targetPoint) };
                    if (result.IsValid()) {
                        results.push_back(result);
                    }
                }
            }
        }

        return results;
    }

    utl::ResultFight Galaxy::Fight(SpaceObject_ty const& defender, SpaceObject_ty const& attacker) {
        if (defender->GetShipCount() == 0 or attacker->GetShipCount() == 0) {
            hlp::Print(hlp::PrintType::ONLY_DEBUG,
                       "fight without ships -> defender id: {} -> ships: {} -> attacker id: {} -> ships: {}",
                       defender->GetID(),
                       defender->GetShipCount(),
                       attacker->GetID(),
                       attacker->GetShipCount());
            return {};
        }

        if (defender->GetPlayer() == attacker->GetPlayer()) {
            hlp::Print(hlp::PrintType::ONLY_DEBUG,
                       "fight with same player -> defender id: {} -> attacker id: {} -> player id: {}",
                       defender->GetID(),
                       attacker->GetID(),
                       defender->GetPlayer()->GetID());
            return {};
        }

        utl::ResultFight::rounds_ty rounds{};
        rounds.emplace_back(defender->GetShipCount(), attacker->GetShipCount());
        while (true) {
            auto defenderCount{ Salve(defender) };
            if (attacker->GetShipCount() <= defenderCount) {
                rounds.emplace_back(defender->GetShipCount(), 0);
                attacker->SetShipCount(0);
                break;
            }
            *attacker -= defenderCount;
            rounds.emplace_back(defender->GetShipCount(), attacker->GetShipCount());

            auto attackerCount{ Salve(attacker) };
            if (defender->GetShipCount() <= attackerCount) {
                rounds.emplace_back(0, attacker->GetShipCount());
                defender->SetShipCount(0);
                break;
            }
            *defender -= attackerCount;
            rounds.emplace_back(defender->GetShipCount(), attacker->GetShipCount());
        }
        hlp::Print(hlp::PrintType::ONLY_DEBUG,
                   "fight -> defender id: {} -> attacker id: {} -> defender ships: {} -> attacker ships: {}",
                   defender->GetID(),
                   attacker->GetID(),
                   defender->GetShipCount(),
                   attacker->GetShipCount());
        return {
            { GenPlayerRep(defender->GetPlayer().get()), GenPlayerRep(attacker->GetPlayer().get()) },
            { GenSingleSpaceObjectRep(defender),         GenSingleSpaceObjectRep(attacker)         },
            rounds,
            true
        };
    }

    utl::usize Galaxy::Salve(SpaceObject_ty const& obj) {
        float const hitChance{ app::AppContext::GetInstance().constants.fight.hitChance * 100 };
        auto& random_{ hlp::Random::GetInstance() };
        utl::usize hitCount{ 0 };

        for (utl::usize i = 0; i < obj->GetShipCount(); ++i) {
            auto result{ random_.random(101) };
            if (hitChance >= static_cast<float>(result)) {
                ++hitCount;
            }
        }

        return hitCount;
    }

    Galaxy::Galaxy(utl::vec2pos_ty size,
                   utl::usize planetCount,
                   std::vector<Player_ty> const& players,
                   Player_ty const& neutralPlayer)
        : m_size{ size } {

        InitializePlanets(planetCount, players, neutralPlayer);
    }

    Galaxy::Galaxy(Galaxy const& old) : m_validGalaxy{ old.m_validGalaxy }, m_size{ old.m_size } {

        for (auto const& o : old.m_objects) {
            if (o->IsFleet()) {
                auto const object = std::make_shared<Fleet>(*std::static_pointer_cast<Fleet>(o));
                m_objects.push_back(object);
                m_fleets.push_back(object);
            } else if (o->IsPlanet()) {
                auto const object = std::make_shared<Planet>(*std::static_pointer_cast<Planet>(o));
                m_objects.push_back(object);
                m_planets.push_back(object);
            } else if (o->IsTargetPoint()) {
                auto const object = std::make_shared<TargetPoint>(*std::static_pointer_cast<TargetPoint>(o));
                m_objects.push_back(object);
                m_targetPoints.push_back(object);
            } else if (o->IsBlackHole()) {
                auto const object = std::make_shared<BlackHole>(*std::static_pointer_cast<BlackHole>(o));
                m_objects.push_back(object);
                m_blackHoles.push_back(object);
            } else {
                throw std::invalid_argument("invalid Space Object");
            }
        }
    }

    bool Galaxy::IsValid() const {
        return m_validGalaxy;
    }

    bool Galaxy::IsValidSpaceObjectID(utl::usize const ID) const {

        for (auto const& object : m_objects) {
            if (object->GetID() == ID) {
                return true;
            }
        }

        return false;
    }

    bool Galaxy::HasMovesLeft(Player_ty_c player) const {
        for (auto const& object : m_objects) {
            if (object->GetPlayer()->GetID() == player->GetID()) {
                return true;
            }
        }
        return false;
    }

    void Galaxy::SetFiltered(bool const isFiltered) {
        m_isFiltered = isFiltered;
    }

    bool Galaxy::IsFiltered() const {
        return m_isFiltered;
    }

    utl::vec2pos_ty Galaxy::GetSize() const {
        return m_size;
    }

    std::vector<Planet_ty> Galaxy::GetPlanets() const {
        return m_planets;
    }

    std::vector<Fleet_ty> Galaxy::GetFleets() const {
        return m_fleets;
    }

    std::vector<TargetPoint_ty> Galaxy::GetTargetPoints() const {
        return m_targetPoints;
    }

    Planet_ty Galaxy::GetPlanetByID(utl::usize const ID) const {
        for (auto const& planet : m_planets) {
            if (planet->GetID() == ID) {
                return planet;
            }
        }

        throw std::runtime_error("no planet with this ID: " + std::to_string(ID));
    }

    SpaceObject_ty Galaxy::GetSpaceObjectByID(utl::usize const ID) const {

        for (auto const& object : m_objects) {
            if (object->GetID() == ID) {
                return object;
            }
        }

        return nullptr;
    }

    bool Galaxy::IsValidPosition(utl::vec2pos_ty_ref_c position) const {
        for (auto const& p : m_planets) {
            if (p->GetPos() == position) {
                return false;
            }
        }
        return true;
    }

    utl::ResultFleet Galaxy::AddFleet(eve::SendFleetInstructionEvent const* const event,
                                      Player_ty const& currentPlayer) {

        // valid ID?
        if (!IsValidSpaceObjectID(event->GetOrigin())) {
            popup(app::AppContext::GetInstance().languageManager.Text("logic_galaxy_not_existing_origin_id_text",
                                                                      event->GetOrigin()));
            hlp::Print(hlp::PrintType::ONLY_DEBUG, "origin is not available: {}", event->GetOrigin());
            return { nullptr, nullptr, nullptr, false };
        }

        if (event->GetShipCount() == 0) {
            popup(app::AppContext::GetInstance().languageManager.Text("ui_popup_add_fleet_ship_count_too_low",
                                                                      event->GetShipCount()));
            hlp::Print(hlp::PrintType::ONLY_DEBUG, "ship count to low: {}", event->GetShipCount());
            return { nullptr, nullptr, nullptr, false };
        }

        switch (event->GetType()) {
            case utl::FleetInstructionType::ID: {
                // check for valid ID in general
                if (not IsValidSpaceObjectID(event->GetDestination())) {
                    popup(app::AppContext::GetInstance().languageManager.Text(
                            "logic_galaxy_not_existing_destination_id_text", event->GetDestination()));
                    hlp::Print(hlp::PrintType::ONLY_DEBUG, "destination id not available: {}", event->GetDestination());
                    return { nullptr, nullptr, nullptr, false };
                }
                break;
            }
            case utl::FleetInstructionType::COORDINATES: {
                // check for valid Coordinates in general
                bool const validCoordinates{ std::cmp_less_equal(event->GetDestinationX(), m_size.x)
                                             and std::cmp_less_equal(event->GetDestinationY(), m_size.y)
                                             and event->GetDestinationX() != 0 and event->GetDestinationY() != 0 };

                if (!validCoordinates) {
                    popup(app::AppContext::GetInstance().languageManager.Text(
                            "logic_galaxy_destination_coordinate_outside_of_map_text",
                            event->GetDestinationX(),
                            event->GetDestinationY()));
                    hlp::Print(hlp::PrintType::ONLY_DEBUG,
                               "destination coordinates out of map -> destination x: {} -> destination y: {}",
                               event->GetDestinationX(),
                               event->GetDestinationY());
                    return { nullptr, nullptr, nullptr, false };
                }
                break;
            }

            case utl::FleetInstructionType::INVALID: {
                popup(app::AppContext::GetInstance().languageManager.Text("ui_popup_add_fleet_invalid_input_send"));
                hlp::Print(hlp::PrintType::ERROR, R"(FleetInstructionType was set to "INVALID")");
                return { nullptr, nullptr, nullptr, false };
            }
        }

        // get origin and set new fleet
        auto const& origin{ GetSpaceObjectByID(event->GetOrigin()) };

        if (origin->IsPlanet()) {
            return AddFleetFromPlanet(event, currentPlayer);
        }
        if (origin->IsFleet()) {
            return AddFleetFromFleet(event, currentPlayer);
        }
        if (origin->IsTargetPoint()) {
            return AddFleetFromTargetPoint(event, currentPlayer);
        }

        popup(app::AppContext::GetInstance().languageManager.Text("logic_galaxy_cant_recognize_origin_text",
                                                                  event->GetOrigin()));
        hlp::Print(hlp::PrintType::ERROR,
                   "not able to recognize fleet input -> origin: {} -> destination: {} -> destination x: {} -> "
                   "destination y: {} -> ships: {}",
                   event->GetOrigin(),
                   event->GetDestination(),
                   event->GetDestinationX(),
                   event->GetDestinationY(),
                   event->GetShipCount());
        return { nullptr, nullptr, nullptr, false };
    }

    void Galaxy::SetDiscoverByPlayer(utl::usize currentPlayerID) {
        // discover all space objects with player
        for (auto const& object : m_objects) {
            object->SetDiscovered(false);
        }

        for (auto const& object : m_objects) {
            if (object->GetPlayer()->GetID() == currentPlayerID) {
                object->SetDiscovered(true);
                if (object->IsTargetPoint() and object->GetShipCount() == 0) {
                    continue;
                }
                // discover all space objects nearby space objects with player
                for (auto const& object_i : m_objects) {
                    if (object_i->IsInDiscoverRange(object)) {
                        if (object_i->IsTargetPoint() and object_i->GetShipCount() == 0) {
                            continue;
                        }
                        object_i->SetDiscovered(true);
                    }
                }
            }
        }
    }

    void Galaxy::FilterByDiscovered() {
        if (m_isFiltered) {
            return;
        }

        // filter fleets and target points only by discovered
        auto const newStart{ std::remove_if(
                m_fleets.begin(), m_fleets.end(), [](Fleet_ty_c fleet) { return not fleet->IsDiscovered(); }) };
        m_fleets.erase(newStart, m_fleets.end());

        auto const newStart3{ std::remove_if(
                m_targetPoints.begin(), m_targetPoints.end(), [](TargetPoint_ty_c targetPoint) {
                    return not targetPoint->IsDiscovered();
                }) };
        m_targetPoints.erase(newStart3, m_targetPoints.end());

        // filter space objects by discovered and is not a planet
        auto const newStart4{ std::remove_if(m_objects.begin(), m_objects.end(), [](SpaceObject_ty_c object) {
            return not object->IsPlanet() and not object->IsDiscovered();
        }) };
        m_objects.erase(newStart4, m_objects.end());

        m_isFiltered = true;
    }

    void Galaxy::HandleFleetResult(utl::ResultFleet const& fleetResult, Player_ty_c currentPlayer) {
        auto add = [this](SpaceObject_ty_c obj) {
            if (obj->IsPlanet()) {
                auto const* planet = dynamic_cast<Planet_ty_raw>(obj.get());
                auto newDest       = std::make_shared<Planet>(planet->GetID(),
                                                        planet->GetPos(),
                                                        planet->GetPlayer(),
                                                        planet->IsHomePlanet(),
                                                        planet->GetPlanetNumber(),
                                                        planet->GetShipCount());
                this->m_objects.push_back(newDest);
                this->m_planets.push_back(newDest);

            } else if (obj->IsFleet()) {
                auto const* fleet = dynamic_cast<Fleet_ty_raw>(obj.get());
                auto newDest      = std::make_shared<Fleet>(
                        fleet->GetID(), fleet->GetPos(), fleet->GetShipCount(), fleet->GetPlayer(), fleet->GetTarget());
                this->m_objects.push_back(newDest);
                this->m_fleets.push_back(newDest);
            } else if (obj->IsTargetPoint()) {
                auto const* t_p = dynamic_cast<TargetPoint_ty_raw>(obj.get());
                auto newDest    = std::make_shared<TargetPoint>(
                        t_p->GetID(), t_p->GetPos(), t_p->GetShipCount(), t_p->GetPlayer());
                this->m_objects.push_back(newDest);
                this->m_targetPoints.push_back(newDest);
            }
        };
        auto handle = [this, add, currentPlayer](SpaceObject_ty_c obj) {
            if (not obj) {
                return;
            }

            if (currentPlayer->GetID() != obj->GetPlayer()->GetID()) {
                return;
            }

            auto const& my_obj{ this->GetSpaceObjectByID(obj->GetID()) };
            if (my_obj) {
                my_obj->SetShipCount(obj->GetShipCount());
                if (my_obj->IsFleet()) {
                    auto* const my_fleet{ dynamic_cast<Fleet* const>(&*my_obj) };
                    auto const* const obj_fleet{ dynamic_cast<Fleet const* const>(&*obj) };
                    if (obj_fleet) {
                        my_fleet->SetTarget(obj_fleet->GetTarget());
                    }
                }
            } else {
                add(obj);
            }
        };

        handle(fleetResult.origin);
        handle(fleetResult.fleet);
        handle(fleetResult.destination);
    }

    utl::ResultUpdate Galaxy::Update() {
        hlp::Print(hlp::PrintType::ONLY_DEBUG, "start update logic");
        hlp::Print(hlp::PrintType::ONLY_DEBUG, "-> update space objects");
        for (auto& o : m_objects) {
            o->Update(this);
        }
        hlp::Print(hlp::PrintType::ONLY_DEBUG, "-> merge arriving friendly fleets");
        std::vector<utl::ResultMerge> mergeResults{ CheckArrivingFriendlyFleets() };
        hlp::Print(hlp::PrintType::ONLY_DEBUG, "-> merge friendly fleets with other friendly fleets");
        std::vector<utl::ResultMerge> singleMergeResult{ CheckMergingFriendlyFleets() };
        std::copy(singleMergeResult.begin(), singleMergeResult.end(), std::back_inserter(mergeResults));

        hlp::Print(hlp::PrintType::ONLY_DEBUG, "-> delete fleets without ships before fights");
        CheckDeleteFleetsWithoutShips(); // Check before Fight so there will be no fight without ships
        hlp::Print(hlp::PrintType::ONLY_DEBUG, "-> simulate fights");
        std::vector<utl::ResultFight> fightResults{ SimulateFight() };
        hlp::Print(hlp::PrintType::ONLY_DEBUG, "-> delete fleets without ships after fights");
        CheckDeleteFleetsWithoutShips(); // Check after fight so all fleets that lost there ships gets deleted.
        hlp::Print(hlp::PrintType::ONLY_DEBUG, "-> delete target points out ships");
        CheckDeleteTargetPoints();

        hlp::Print(hlp::PrintType::ONLY_DEBUG, "update logic finished");

        return { mergeResults, fightResults };
    }
} // namespace lgk
