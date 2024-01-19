//
// PurpurTentakel
// 19.01.24
//

#include "RepresentationGenerator.hpp"
#include "Fleet.hpp"
#include "Planet.hpp"
#include "Player.hpp"
#include "TargetPoint.hpp"
#include <vector>


namespace lgk {
    [[nodiscard]] static utl::RepresentationDestination GenSingleDestinationRep(SpaceObject_ty_c spaceObject) {
        auto const type = [spaceObject]() -> utl::TargetType {
            if (spaceObject->IsPlanet()) {
                return utl::TargetType::PLANET;
            } else if (spaceObject->IsTargetPoint()) {
                return utl::TargetType::TARGET_POINT;
            } else if (spaceObject->IsFleet()) {
                return utl::TargetType::FLEET;
            } else {
                std::unreachable();
            }
        }();

        return {
            // clang-format off
            spaceObject->IsDiscovered(),
            spaceObject->GetID(),
            spaceObject->GetPlayer()->GetID(),
            spaceObject->GetShipCount(),
            spaceObject->GetPos(),
            type
            // clang-format on
        };
    }

    [[nodiscard]] static utl::RepresentationPlanet GenSinglePlanetRep(Planet_ty_c planet) {
        return {
            // clang-format off
            planet->IsDiscovered(),
            planet->GetID(),
            planet->GetPlayer()->GetID(),
            planet->GetShipCount(),
            planet->GetPos(),
            planet->IsDestroyed(),
            planet->GetPlayer()->IsHumanPlayer(),
            planet->GetProduction()
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

    [[nodiscard]] static utl::RepresentationTargetPoint GenSingleTargetPointRep(TargetPoint_ty_c targetPoint) {
        return {
            // clang-format off
            targetPoint->IsDiscovered(),
            targetPoint->GetID(),
            targetPoint->GetPlayer()->GetID(),
            targetPoint->GetShipCount(),
            targetPoint->GetPos(),
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

    [[nodiscard]] static utl::RepresentationFleet GenSingleFleetRep(Fleet_ty_c fleet) {
        return {
            // clang-format off
            fleet->IsDiscovered(),
            fleet->GetID(),
            fleet->GetPlayer()->GetID(),
            fleet->GetShipCount(),
            fleet->GetPos(),
            GenSingleDestinationRep(fleet->GetTarget())
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

    utl::RepresentationGalaxy lgk::GenGalaxyRep(Galaxy const* galaxy) {
        return { GenAllPlanetRep(galaxy->GetPlanets()),
                 GenAllTargetPointRep(galaxy->GetTargetPoints()),
                 GenAllFleetRep(galaxy->GetFleets()),
                 galaxy->GetSize() };
    }
} // namespace lgk