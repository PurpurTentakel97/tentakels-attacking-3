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
    void InitializePlanets(size_t planetCount, std::vector<Player_ty> players, Player_ty neutralPlayer);

    [[nodiscard]] int GenerateHomePlanets(std::vector<Player_ty> players);

    void GenerateOtherPlanets(size_t PlanetCount, int currentPlanet, Player_ty player);

    [[nodiscard]] bool IsValidNewPlanet(Planet_ty newPlanet, AppContext_ty_c appContext) const;

    // Fleet
    [[nodiscard]] bool IsValidFleet(unsigned int ID) const;

    [[nodiscard]] Fleet_ty GetFleetByID(unsigned int ID) const;

    [[nodiscard]] Fleet_ty TryGetExistingFleetByOriginAndDestination(SpaceObject_ty origin, SpaceObject_ty destination)
            const;

    [[nodiscard]] HFleetResult AddFleetFromPlanet(SendFleetInstructionEvent const* event, Player_ty currentPlayer);

    [[nodiscard]] HFleetResult AddFleetFromFleet(SendFleetInstructionEvent const* event, Player_ty currentPlayer);

    [[nodiscard]] HFleetResult AddFleetFromTargetPoint(SendFleetInstructionEvent const* event, Player_ty currentPlayer);

    [[nodiscard]] std::vector<Fleet_ty> GetFleetsOfTarget(SpaceObject_ty object) const;

    void DeleteFleet(std::vector<Fleet_ty> const& fleets);

    void DeleteFleet(Fleet_ty fleet);

    // Target Point
    [[nodiscard]] bool IsValidTargetPoint(unsigned int ID) const;

    [[nodiscard]] TargetPoint_ty GetTargetPointByID(unsigned int ID) const;

    [[nodiscard]] SpaceObject_ty GetOrGenerateDestination(unsigned int ID, int X, int Y, Player_ty currentPlayer);

    void CheckDeleteTargetPoints();

    // update
    [[nodiscard]] std::vector<Fleet_ty>
    UpdateFleetTargets(std::vector<Fleet_ty> fleets, SpaceObject_ty currentFleet, SpaceObject_ty target);

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

    [[nodiscard]] HFightResult Fight(SpaceObject_ty defender, SpaceObject_ty attacker);

    [[nodiscard]] size_t Salve(SpaceObject_ty obj) const;

public:
    Galaxy(vec2pos_ty size, size_t planetCount, std::vector<Player_ty> players, Player_ty neutralPlayer);

    Galaxy(Galaxy const&);

    [[nodiscard]] bool IsValid() const;

    [[nodiscard]] bool IsValidSpaceObjectID(unsigned int ID) const;

    [[nodiscard]] bool HasMovesLeft(Player_ty_c player) const;

    void SetFiltered(bool isFiltered);

    [[nodiscard]] bool IsFiltered() const;

    [[nodiscard]] vec2pos_ty GetSize() const;

    [[nodiscard]] std::vector<Planet_ty> const GetPlanets() const;

    [[nodiscard]] std::vector<Fleet_ty> const GetFleets() const;

    [[nodiscard]] std::vector<TargetPoint_ty> const GetTargetPoints() const;

    [[nodiscard]] Planet_ty const GetPlanetByID(unsigned int ID) const;

    [[nodiscard]] SpaceObject_ty const GetSpaceObjectByID(unsigned int ID) const;

    [[nodiscard]] bool IsValidPosition(vec2pos_ty_ref_c position) const;

    [[nodiscard]] HFleetResult AddFleet(SendFleetInstructionEvent const* event, Player_ty currentPlayer);

    void SetDiscoverByPlayer(unsigned int currentPlayerID);

    void FilterByPlayer(unsigned int currentPlayerID);

    void HandleFleetResult(HFleetResult const& fleetResult, Player_ty_c currentPlayer);

    // update
    [[nodiscard]] UpdateResult_ty Update();
};
