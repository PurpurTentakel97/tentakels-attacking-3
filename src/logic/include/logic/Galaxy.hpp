//
// PurpurTentakel
// 08.11.22
//

#pragma once
#include "Fleet.hpp"
#include "Planet.hpp"
#include "TargetPoint.hpp"
#include <event/EventGenerel.hpp>
#include <helper/HVec2.hpp>
#include <memory>
#include <vector>

struct HFleetResult;
struct HFightResult;


class Galaxy final {
private:
    bool m_validGalaxy{ true };
    bool m_isFiltered{ false };
    std::vector<SpaceObject_ty> m_objects;
    std::vector<Planet_ty> m_planets;
    std::vector<Fleet_ty> m_fleets;
    std::vector<TargetPoint_ty> m_targetPoints;
    vec2pos_ty m_size;


    [[nodiscard]] unsigned int GetNextID() const;

    // Planet
    void InitializePlanets(size_t planetCount, std::vector<Player_ty> const & players, Player_ty const& neutralPlayer);

    [[nodiscard]] int GenerateHomePlanets(std::vector<Player_ty> const& players);

    void GenerateOtherPlanets(size_t PlanetCount, int currentPlanet, Player_ty const& player);

    [[nodiscard]] bool IsValidNewPlanet(Planet_ty const& newPlanet, AppContext_ty_c appContext) const;

    // Fleet
    [[nodiscard]] bool IsValidFleet(unsigned int ID) const;

    [[nodiscard]] Fleet_ty GetFleetByID(unsigned int ID) const;

    [[nodiscard]] Fleet_ty TryGetExistingFleetByOriginAndDestination(SpaceObject_ty const& origin, SpaceObject_ty const& destination)
            const;

    [[nodiscard]] HFleetResult
    AddFleetFromPlanet(eve::SendFleetInstructionEvent const* event, Player_ty const& currentPlayer);

    [[nodiscard]] HFleetResult
    AddFleetFromFleet(eve::SendFleetInstructionEvent const* event, Player_ty const& currentPlayer);

    [[nodiscard]] HFleetResult
    AddFleetFromTargetPoint(eve::SendFleetInstructionEvent const* event, Player_ty const& currentPlayer);

    [[nodiscard]] std::vector<Fleet_ty> GetFleetsOfTarget(SpaceObject_ty const& object) const;

    void DeleteFleet(std::vector<Fleet_ty> const& fleets);

    void DeleteFleet(Fleet_ty const& fleet);

    // Target Point
    [[nodiscard]] bool IsValidTargetPoint(unsigned int ID) const;

    [[nodiscard]] TargetPoint_ty GetTargetPointByID(unsigned int ID) const;

    [[nodiscard]] SpaceObject_ty GetOrGenerateDestination(unsigned int ID, int X, int Y, Player_ty const& currentPlayer);

    void CheckDeleteTargetPoints();

    // update
    [[nodiscard]] std::vector<Fleet_ty>
    UpdateFleetTargets(std::vector<Fleet_ty> const& fleets, SpaceObject_ty const& currentFleet, SpaceObject_ty const& target);

    [[nodiscard]] std::vector<HMergeResult> CheckArrivingFriendlyFleets();

    [[nodiscard]] std::vector<HMergeResult> CheckMergingFriendlyFleets();

    void CheckDeleteFleetsWithoutShips();

    [[nodiscard]] std::vector<HFightResult> SimulateFight();

    [[nodiscard]] std::vector<HFightResult> SimulateFightFleetPlanet();

    [[nodiscard]] std::vector<HFightResult> SimulateFightFleetTargetPoint();

    [[nodiscard]] std::vector<HFightResult> SimulateFightFleetFleet();

    [[nodiscard]] std::vector<HFightResult> SimulateFightPlanetFleet();

    [[nodiscard]] std::vector<HFightResult> SimulateFightTargetPointFleet();

    [[nodiscard]] std::vector<HFightResult> SimulateFightTargetPointTargetPoint();

    [[nodiscard]] std::vector<HFightResult> SimulateFightPlanetTargetPoint();

    [[nodiscard]] static HFightResult Fight(SpaceObject_ty const& defender, SpaceObject_ty const& attacker);

    [[nodiscard]] static size_t Salve(SpaceObject_ty const& obj);

public:
    Galaxy(vec2pos_ty size, size_t planetCount, std::vector<Player_ty> const&  players, Player_ty const& neutralPlayer);

    Galaxy(Galaxy const&);

    [[nodiscard]] bool IsValid() const;

    [[nodiscard]] bool IsValidSpaceObjectID(unsigned int ID) const;

    [[nodiscard]] bool HasMovesLeft(Player_ty_c player) const;

    void SetFiltered(bool isFiltered);

    [[nodiscard]] bool IsFiltered() const;

    [[nodiscard]] vec2pos_ty GetSize() const;

    [[nodiscard]] std::vector<Planet_ty> GetPlanets() const;

    [[nodiscard]] std::vector<Fleet_ty> GetFleets() const;

    [[nodiscard]] std::vector<TargetPoint_ty> GetTargetPoints() const;

    [[nodiscard]] Planet_ty GetPlanetByID(unsigned int ID) const;

    [[nodiscard]] SpaceObject_ty GetSpaceObjectByID(unsigned int ID) const;

    [[nodiscard]] bool IsValidPosition(vec2pos_ty_ref_c position) const;

    [[nodiscard]] HFleetResult AddFleet(eve::SendFleetInstructionEvent const* event, Player_ty const& currentPlayer);

    void SetDiscoverByPlayer(unsigned int currentPlayerID);

    void FilterByDiscovered();

    void HandleFleetResult(HFleetResult const& fleetResult, Player_ty_c currentPlayer);

    // update
    [[nodiscard]] UpdateResult_ty Update();
};
