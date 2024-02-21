//
// PurpurTentakel
// 19.01.24
//

#include "RepresentationGenerator.hpp"
#include "Fleet.hpp"
#include "Player.hpp"
#include <vector>


namespace lgk {
    static auto constexpr type = [](SpaceObject_ty_c spaceObject) -> utl::SpaceObjectType {
        if (spaceObject->IsPlanet()) {
            return utl::SpaceObjectType::PLANET;
        } else if (spaceObject->IsTargetPoint()) {
            return utl::SpaceObjectType::TARGET_POINT;
        } else if (spaceObject->IsFleet()) {
            return utl::SpaceObjectType::FLEET;
        } else if (spaceObject->IsBlackHole()) {
            return utl::SpaceObjectType::BLACK_HOLE;
        } else {
            std::unreachable();
        }
    };
    [[nodiscard]] utl::RepresentationSpaceObject GenSingleSpaceObjectRep(SpaceObject_ty_c spaceObject) {
        return {
            // clang-format off
            spaceObject->IsDiscovered(),
            spaceObject->GetID(),
            spaceObject->GetPlayer()->GetID(),
            spaceObject->GetShipCount(),
            spaceObject->GetPos(),
            type(spaceObject)
            // clang-format on
        };
    }

    // black Hole
    [[nodiscard]] utl::RepresentationBlackHole GenSingleBlackHoleRep(BlackHole_ty_c blackHole, int const galaxyWidth) {
        return {
  // clang-format off
            {
                blackHole->IsDiscovered(),
                blackHole->GetID(),
                blackHole->GetPlayer()->GetID(),
                blackHole->GetShipCount(),
                blackHole->GetPos(),
                type(blackHole)
            },
            blackHole->Size(galaxyWidth)
  // clang-format on
        };
    }

    [[nodiscard]] static std::vector<utl::RepresentationBlackHole> GenAllBlackHoleRep(
            std::vector<BlackHole_ty> const& blackHoles, int const galaxyWidth) {
        std::vector<utl::RepresentationBlackHole> result{};
        for (auto const& b : blackHoles) {
            result.push_back(GenSingleBlackHoleRep(b, galaxyWidth));
        }
        return result;
    }

    // Planet
    [[nodiscard]] static utl::RepresentationPlanet GenSinglePlanetRep(Planet_ty_c planet) {
        return {
  // clang-format off
            {
                planet->IsDiscovered(),
                planet->GetID(),
                planet->GetPlayer()->GetID(),
                planet->GetShipCount(),
                planet->GetPos(),
                type(planet)
            },
            planet->GetPlayer()->IsHumanPlayer(),
            planet->GetProduction(),
            planet->GetProductionProblemYears()
  // clang-format on
        };
    }
    [[nodiscard]] static std::vector<utl::RepresentationPlanet> GenAllPlanetRep(std::vector<Planet_ty> const& planets) {
        std::vector<utl::RepresentationPlanet> r{};
        for (auto const& p : planets) {
            r.push_back(GenSinglePlanetRep(p));
        }
        return r;
    }

    // Target Point
    [[nodiscard]] static utl::RepresentationTargetPoint GenSingleTargetPointRep(TargetPoint_ty_c targetPoint) {
        return {
            // clang-format off
            targetPoint->IsDiscovered(),
            targetPoint->GetID(),
            targetPoint->GetPlayer()->GetID(),
            targetPoint->GetShipCount(),
            targetPoint->GetPos(),
            type(targetPoint)
            // clang-format on
        };
    }
    [[nodiscard]] static std::vector<utl::RepresentationTargetPoint> GenAllTargetPointRep(
            std::vector<TargetPoint_ty> const& targetPoints) {
        std::vector<utl::RepresentationTargetPoint> r{};
        for (auto const& t : targetPoints) {
            r.push_back(GenSingleTargetPointRep(t));
        }
        return r;
    }

    // Fleet
    [[nodiscard]] static utl::RepresentationFleet GenSingleFleetRep(Fleet_ty_c fleet) {
        return {
  // clang-format off
            {
                fleet->IsDiscovered(),
                fleet->GetID(),
                fleet->GetPlayer()->GetID(),
                fleet->GetShipCount(),
                fleet->GetPos(),
                type(fleet)
            },
            fleet->GetEngineProblemYears(),
            GenSingleSpaceObjectRep(fleet->GetTarget())
  // clang-format on
        };
    }
    [[nodiscard]] static std::vector<utl::RepresentationFleet> GenAllFleetRep(std::vector<Fleet_ty> const& fleets) {
        std::vector<utl::RepresentationFleet> r{};
        for (auto const& f : fleets) {
            r.push_back(GenSingleFleetRep(f));
        }
        return r;
    }

    utl::RepresentationGalaxy GenGalaxyRep(Galaxy const* galaxy) {
        return { GenAllPlanetRep(galaxy->GetPlanets()),
                 GenAllTargetPointRep(galaxy->GetTargetPoints()),
                 GenAllFleetRep(galaxy->GetFleets()),
                 GenAllBlackHoleRep(galaxy->GetBlackHoles(), galaxy->GetSize().x),
                 galaxy->GetSize() };
    }

    utl::RepresentationPlayer GenPlayerRep(Player const* player) {
        return { player->GetID() };
    }
} // namespace lgk
