//
// PurpurTentakel
// 25.05.23
//

#include "HGalaxy.hpp"
#include <alias/AliasLogic.hpp>
#include <logic/Fleet.hpp>

namespace hlp {
    std::pair<bool, lgk::SpaceObject_ty> TryGetTarget(lgk::Fleet_ty_raw fleet, lgk::SpaceObject_ty_c target) {

        if (target->IsFleet()) {
            if (target->GetID() == fleet->GetID()) {
                return { false, nullptr };
            }
            if (fleet->GetPlayer() != target->GetPlayer()) {
                return { true, target };
            }
            auto n_target = dynamic_cast<lgk::Fleet_ty_raw>(target.get());
            return TryGetTarget(fleet, n_target->GetTarget());
        }

        return { true, target };
    }
} // namespace hlp
