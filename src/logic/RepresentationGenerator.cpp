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
    [[nodiscard]] static utl::DestinationRepresentation GenSingleDestinationRep(SpaceObject_ty_c spaceObject) {
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

    [[nodiscard]] static utl::PlanetRepresentation GenSinglePlanetRep(Planet_ty_c planet) {
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
    [[nodiscard]] static std::vector<utl::PlanetRepresentation> GenAllPlanetRep(std::vector<Planet_ty> const& planets) {
        std::vector<utl::PlanetRepresentation> r{};
        for (auto const& p : planets) {
            r.push_back(GenSinglePlanetRep(p));
        }
        return r;
    }

    [[nodiscard]] static utl::TargetPointRepresentation GenSingleTargetPointRep(TargetPoint_ty_c targetPoint) {
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
    [[nodiscard]] static std::vector<utl::TargetPointRepresentation> GenAllTargetPointRep(
            std::vector<TargetPoint_ty> const& targetPoints) {
        std::vector<utl::TargetPointRepresentation> r{};
        for (auto const& t : targetPoints) {
            r.push_back(GenSingleTargetPointRep(t));
        }
        return r;
    }

    [[nodiscard]] static utl::FleetRepresentation GenSingleFleetRep(Fleet_ty_c fleet) {
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
    [[nodiscard]] static std::vector<utl::FleetRepresentation> GenAllFleetRep(std::vector<Fleet_ty> const& fleets) {
        std::vector<utl::FleetRepresentation> r{};
        for (auto const& f : fleets) {
            r.push_back(GenSingleFleetRep(f));
        }
        return r;
    }

    utl::GalaxyRepresentation lgk::GenGalaxyRep(Galaxy const* galaxy) {
        return { GenAllPlanetRep(galaxy->GetPlanets()),
                 GenAllTargetPointRep(galaxy->GetTargetPoints()),
                 GenAllFleetRep(galaxy->GetFleets()),
                 galaxy->GetSize() };
    }
} // namespace lgk
