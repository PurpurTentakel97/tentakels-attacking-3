//
// PurpurTentakel
// 08.11.22
//

#pragma once
#include "Fleet.hpp"
#include "Planet.hpp"
#include "TargetPoint.hpp"
#include <alias/AliasApp.hpp>
#include <alias/AliasUtils.hpp>
#include <event/EventGeneral.hpp>
#include <memory>
#include <utils/Vec2.hpp>
#include <vector>

namespace lgk {
    class Galaxy final {
    private:
        bool m_validGalaxy{ true };
        bool m_isFiltered{ false };
        std::vector<SpaceObject_ty> m_objects;
        std::vector<Planet_ty> m_planets;
        std::vector<Fleet_ty> m_fleets;
        std::vector<TargetPoint_ty> m_targetPoints;
        utl::vec2pos_ty m_size;


        [[nodiscard]] utl::usize GetNextID() const;

        // Planet
        void InitializePlanets(
                utl::usize planetCount,
                std::vector<Player_ty> const& players,
                Player_ty const& neutralPlayer
        );

        [[nodiscard]] utl::usize GenerateHomePlanets(std::vector<Player_ty> const& players);

        void GenerateOtherPlanets(utl::usize PlanetCount, utl::usize currentPlanet, Player_ty const& player);

        [[nodiscard]] bool IsValidNewPlanet(Planet_ty const& newPlanet, app::AppContext_ty_c appContext) const;

        // Fleet
        [[nodiscard]] bool IsValidFleet(utl::usize ID) const;

        [[nodiscard]] Fleet_ty GetFleetByID(utl::usize ID) const;

        [[nodiscard]] Fleet_ty TryGetExistingFleetByOriginAndDestination(
                SpaceObject_ty const& origin,
                SpaceObject_ty const& destination
        ) const;

        [[nodiscard]] utl::ResultFleet AddFleetFromPlanet(eve::SendFleetInstructionEvent const* event,
                                                          Player_ty const& currentPlayer);

        [[nodiscard]] utl::ResultFleet AddFleetFromFleet(eve::SendFleetInstructionEvent const* event,
                                                         Player_ty const& currentPlayer);

        [[nodiscard]] utl::ResultFleet AddFleetFromTargetPoint(eve::SendFleetInstructionEvent const* event,
                                                               Player_ty const& currentPlayer);

        [[nodiscard]] std::vector<Fleet_ty> GetFleetsOfTarget(SpaceObject_ty const& object) const;

        void DeleteFleet(std::vector<Fleet_ty> const& fleets);

        void DeleteFleet(Fleet_ty const& fleet);

        // Target Point
        [[nodiscard]] bool IsValidTargetPoint(utl::usize ID) const;

        [[nodiscard]] TargetPoint_ty GetTargetPointByID(utl::usize ID) const;

        [[nodiscard]] SpaceObject_ty
        GetOrGenerateDestination(utl::usize ID, int X, int Y, Player_ty const& currentPlayer);

        void CheckDeleteTargetPoints();

        // update
        [[nodiscard]] std::vector<Fleet_ty> UpdateFleetTargets(
                std::vector<Fleet_ty> const& fleets,
                SpaceObject_ty const& currentFleet,
                SpaceObject_ty const& target
        );

        [[nodiscard]] std::vector<utl::ResultMerge> CheckArrivingFriendlyFleets();

        [[nodiscard]] std::vector<utl::ResultMerge> CheckMergingFriendlyFleets();

        void CheckDeleteFleetsWithoutShips();

        [[nodiscard]] std::vector<utl::ResultFight> SimulateFight();

        [[nodiscard]] std::vector<utl::ResultFight> SimulateFightFleetPlanet();

        [[nodiscard]] std::vector<utl::ResultFight> SimulateFightFleetTargetPoint();

        [[nodiscard]] std::vector<utl::ResultFight> SimulateFightFleetFleet();

        [[nodiscard]] std::vector<utl::ResultFight> SimulateFightPlanetFleet();

        [[nodiscard]] std::vector<utl::ResultFight> SimulateFightTargetPointFleet();

        [[nodiscard]] std::vector<utl::ResultFight> SimulateFightTargetPointTargetPoint();

        [[nodiscard]] std::vector<utl::ResultFight> SimulateFightPlanetTargetPoint();

        [[nodiscard]] static utl::ResultFight Fight(SpaceObject_ty const& defender, SpaceObject_ty const& attacker);

        [[nodiscard]] static utl::usize Salve(SpaceObject_ty const& obj);

    public:
        Galaxy(utl::vec2pos_ty size,
               utl::usize planetCount,
               std::vector<Player_ty> const& players,
               Player_ty const& neutralPlayer);

        Galaxy(Galaxy const&);

        [[nodiscard]] bool IsValid() const;

        [[nodiscard]] bool IsValidSpaceObjectID(utl::usize ID) const;

        [[nodiscard]] bool HasMovesLeft(Player_ty_c player) const;

        void SetFiltered(bool isFiltered);

        [[nodiscard]] bool IsFiltered() const;

        [[nodiscard]] utl::vec2pos_ty GetSize() const;

        [[nodiscard]] std::vector<Planet_ty> GetPlanets() const;

        [[nodiscard]] std::vector<Fleet_ty> GetFleets() const;

        [[nodiscard]] std::vector<TargetPoint_ty> GetTargetPoints() const;

        [[nodiscard]] Planet_ty GetPlanetByID(utl::usize ID) const;

        [[nodiscard]] SpaceObject_ty GetSpaceObjectByID(utl::usize ID) const;

        [[nodiscard]] bool IsValidPosition(utl::vec2pos_ty_ref_c position) const;

        [[nodiscard]] utl::ResultFleet AddFleet(eve::SendFleetInstructionEvent const* event,
                                                Player_ty const& currentPlayer);

        void SetDiscoverByPlayer(utl::usize currentPlayerID);

        void FilterByDiscovered();

        void HandleFleetResult(utl::ResultFleet const& fleetResult, Player_ty_c currentPlayer);

        // update
        [[nodiscard]] utl::UpdateResult_ty Update();
    };
} // namespace lgk
