//
// PurpurTentakel
// 08.11.22
//

#pragma once
#include "Planet.h"
#include "TargetPoint.h"
#include "Fleet.h"
#include "event/GenerelEvents.hpp"
#include "helper/Vec2.hpp"
#include <vector>
#include <memory>

struct HFleetResult;
struct HFightResult;

/**
 * contains objects witch include planet, fleets, target points
 * generates itself.
 */
class Galaxy final {
private:
	bool m_validGalaxy{ true }; ///< specifies if the generation in valid and the galaxy is able to use
	bool m_isFiltered{ false }; ///< returnsa if the galaxy was getting filtered
	std::vector<SpaceObject_ty> m_objects; ///< contains all space object for updating 
	std::vector<Planet_ty> m_planets; ///< contains all planets 
	std::vector<Fleet_ty> m_fleets; ///< contains all fleets
	std::vector<TargetPoint_ty> m_targetPoints; ///< contains all target points

	vec2pos_ty m_size; ///< contains the size of the galaxy

	/**
	 * returns the next free ID for an Space object that is the nearest to 0.
	 */
	[[nodiscard]] unsigned int GetNextID() const;

	// Planet
	/**
	 * coordinates the generation of all planets.
	 */
	void InitializePlanets(size_t planetCount, std::vector<Player_ty> players, Player_ty neutralPlayer);
	/**
	 * generation one home planet for every player.
	 * returns the planet count for generating the other planets.
	 */
	[[nodiscard]] int GenerateHomePlanets(std::vector<Player_ty> players);
	/**
	 * generation all other planet until the planet count is reached.
	 */
	void GenerateOtherPlanets(size_t PlanetCount, int currentPlanet, Player_ty player);
	/**
	 * validates if the new planet has a valid position.
	 * mainly if the distance to every other planet is big enough.
	 * returns a bool.
	 */
	[[nodiscard]] bool IsValidNewPlanet(Planet_ty newPlanet, AppContext_ty_c appContext) const;

	// Fleet
	/**
	 * checks if the provided ID is a valid Feet.
	 */
	[[nodiscard]] bool IsValidFleet(unsigned int const ID) const;
	/**
	 * returns a fleet by ID.
	 * throws an runtime error if no Fleet exists for that ID.
	 */
	[[nodiscard]] Fleet_ty GetFleetByID(unsigned int const ID) const;
	/**
	 * returns a fleet if existing.
	 * returns a nullptr if not.
	 */
	[[nodiscard]] Fleet_ty TryGetExistingFleetByOriginAndDestination(
		SpaceObject_ty origin, SpaceObject_ty destination) const;

	/**
	 * validates the data from the UI if the instruction is for a planet.
	 * generates Popups if needed.
	 * add new fleet if valid.
	 */
	[[nodiscard]] HFleetResult AddFleetFromPlanet(SendFleetInstructionEvent const* event, Player_ty currentPlayer);
	/**
	 * validates the data from the UI if the instruction is for a fleet.
	 * generates Popups if needed.
	 * add new fleet if valid.
	 */
	[[nodiscard]] HFleetResult AddFleetFromFleet(SendFleetInstructionEvent const* event, Player_ty currentPlayer);
	/**
	 * validates the data from the UI if the instruction is for a target point.
	 * generates Popups if needed.
	 * add new fleet if valid.
	 */
	[[nodiscard]] HFleetResult AddFleetFromTargetPoint(SendFleetInstructionEvent const* event, Player_ty currentPlayer);

	/**
	 * returns a vector of fleets that has the provided SpaceObject as target.
	 */
	[[nodiscard]] std::vector<Fleet_ty> GetFleetsOfTarget(SpaceObject_ty object) const;

	/**
	 * deletes a vector of fleets.
	 */
	void DeleteFleet(std::vector<Fleet_ty> const& fleets);
	/**
	 * delete a single fleet.
	 */
	void DeleteFleet(Fleet_ty fleet);

	// Target Point
	/**
	 * checks if the provided ID is a target point.
	 */
	[[nodiscard]] bool IsValidTargetPoint(unsigned int const ID) const;
	/**
	 * returns the target point of the provided ID.
	 * throws an runtime error if no target point exists.
	 */
	[[nodiscard]] TargetPoint_ty GetTargetPointByID(unsigned int const ID) const;

	/**
	 * returns a existing destination er generate a TargetPoint as destination.
	 */
	[[nodiscard]] SpaceObject_ty GetOrGenerateDestination(unsigned int ID,
		int X, int Y, Player_ty currentPlayer);
	/**
	 * checks every target point if there are origins.
	 * if not it gets deleted.
	 */
	void CheckDeleteTargetPoints();

	// update
	/**
	 * updates the targets of the provided fleets.
	 */
	[[nodiscard]] std::vector<Fleet_ty> UpdateFleetTargets(std::vector<Fleet_ty> fleets, SpaceObject_ty currentFleet, SpaceObject_ty target);

	/**
	 * checks if any fleet is arrived.
	 * calls the other fleets to gets a new target.
	 */
	[[nodiscard]] std::vector<HMergeResult> CheckArrivingFriendlyFleets();
	/**
	 * checks if any fleets from one player are at the same spot.
	 * class the other fleets zo gets a new target.
	 */
	[[nodiscard]] std::vector<HMergeResult> CheckMergingFriendlyFleets();
	/**
	 * Checks if there is a Fleet without ships.
	 * if it is so the fleets gets deleted and the other fleets gets redirected. 
	 */
	void CheckDeleteFleetsWithoutShips();

	/**
	 * manages all fights while update.
	 */
	[[nodiscard]] std::vector<HFightResult> SimulateFight();
	/**
	 * simulates the fight between a fleet and a planet.
	 */
	[[nodiscard]] std::vector<HFightResult> SimulateFightFleetPlanet();
	/**
	 * simulates the fight between a fleet and a SpacePoint.
	 */
	[[nodiscard]] std::vector<HFightResult> SimulateFightFleetTargetPoint();
	/**
	 * simulates the fight between 2 fleets.
	 */
	[[nodiscard]] std::vector<HFightResult> SimulateFightFleetFleet();
	/**
	 * simulates the fight between a planet and a fleet.
	 */
	[[nodiscard]] std::vector<HFightResult> SimulateFightPlanetFleet();
	/**
	 * simulates the fight between a target point and a fleet.
	 */
	[[nodiscard]] std::vector<HFightResult> SimulateFightTargetPointFleet();
	/**
	 * simulates the fight between a target point and a target point.
	 */
	[[nodiscard]] std::vector<HFightResult> SimulateFightTargetPointTargetPoint();
	/**
	 * simulates the fight between a target point and a target point.
	 */
	[[nodiscard]] std::vector<HFightResult> SimulateFightPlanetTargetPoint();
	/**
	 * simulates a single fight.
	 */
	[[nodiscard]] HFightResult Fight(SpaceObject_ty defender, SpaceObject_ty attacker);
	/**
	 * simulate a salve.
	 * return a hit count.
	 */
    [[nodiscard]] int Salve(SpaceObject_ty obj) const;

public:
	/**
	 * generates all planets.
	 * IsValid should be called after construction because there is no guaranty,
	 * that the	generation is valid.
	 */
	Galaxy(vec2pos_ty size, size_t planetCount, std::vector<Player_ty> players,
		Player_ty neutralPlayer);
	/**
	 * makes a exact copy of a galaxy
	 */
	Galaxy(Galaxy const&);

    Galaxy(Galaxy&&) = default;
    Galaxy& operator=(Galaxy const&) = default;
    Galaxy& operator=(Galaxy&&) = default;

    /**
	 * return if the galaxy is valid.
	 * if its not valid I really to not use this galaxy.
	 * this galaxy will not be complete then.
	 * you should generate a new one.
	 */
	[[nodiscard]] bool IsValid() const;

	/**
	 * returns true if the provided ID is existing in this galaxy.
	 */
	[[nodiscard]] bool IsValidSpaceObjectID(unsigned int ID) const;

	/**
	 * returns if the provided player has any move left.
	 */
	[[nodiscard]] bool HasMovesLeft(Player_ty_c player) const;

	/**
	 * sets if the galaxy was filtered.
	 */
	void SetFiltered(bool isFiltered);
	/**
	 * returns if the galaxy is filtered
	 */
	[[nodiscard]] bool IsFiltered() const;
	/**
	 * returns the size of the galaxy.
	 */
	[[nodiscard]] vec2pos_ty GetSize() const;
	/**
	 * returns the planets of the galaxy.
	 */
	[[nodiscard]] std::vector<Planet_ty> const GetPlanets() const;
	/**
	 * returns the fleets of the galaxy.
	 */
	[[nodiscard]] std::vector<Fleet_ty> const GetFleets() const;
	/**
	 * returns the target points of the galaxy.
	 */
	[[nodiscard]] std::vector<TargetPoint_ty> const GetTargetPoints() const;
	/**
	 * returns a specific planet by ID.
	 */
	[[nodiscard]] Planet_ty const GetPlanetByID(unsigned int ID) const;
	/**
	 * returns a SpaceObject with the provided ID.
	 * returns nullptr if there is no SpaceObject.
	 */
	[[nodiscard]] SpaceObject_ty const GetSpaceObjectByID(unsigned int ID) const;
	/**
	 * returns if the new position is a valid position.
	 */
	[[nodiscard]] bool IsValidPosition(vec2pos_ty_ref_c position) const;
	/**
	 * adds a new fleet to the galaxy for the provided player.
	 */
	[[nodiscard]] HFleetResult AddFleet(SendFleetInstructionEvent const* event, Player_ty currentPlayer);
	/**
	 * updates the discover by player
	 */
	void SetDiscoverByPlayer(unsigned int currentPlayerID);
	/**
	 * filters the galaxy for relevant data for the provided player.
	 */
	void FilterByPlayer(unsigned int currentPlayerID);
	/**
	 * handles the changes of the FleetResult.
	 */
	void HandleFleetResult(HFleetResult const& fleetResult, Player_ty_c currentPlayer);

	// update

	/**
	 * updates the Galaxy.
	 */
	[[nodiscard]] UpdateResult_ty Update();
};
