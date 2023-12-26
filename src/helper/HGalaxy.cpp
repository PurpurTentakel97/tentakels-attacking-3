//
// PurpurTentakel
// 25.05.23
//

#include "HGalaxy.hpp"
#include <logic/Fleet.hpp>

std::pair<bool, SpaceObject_ty> TryGetTarget(Fleet_ty_raw fleet, SpaceObject_ty_c target) {

    if (target->IsFleet()) {
        if (target->GetID() == fleet->GetID()) {
            return { false, nullptr };
        }
        if (fleet->GetPlayer() != target->GetPlayer()) {
            return { true, target };
        }
        Fleet_ty_raw n_target = dynamic_cast<Fleet_ty_raw>(target.get());
        return TryGetTarget(fleet, n_target->GetTarget());
    }

    return { true, target };
}
