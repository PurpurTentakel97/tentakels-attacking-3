//
// Purpur Tentakel
// 16.02.2022
//

#include "TargetPoint.hpp"
#include <helper/HPrint.hpp>


namespace lgk {
    bool TargetPoint::IsTargetPoint() const {
        return true;
    }

    void TargetPoint::Update(Galaxy_ty_raw) {
        hlp::Print(
                hlp::PrintType::ONLY_DEBUG,
                "update target point -> id: {} -> ships: {} -> nothing happens",
                m_ID,
                m_ships
        );
    }
} // namespace lgk
