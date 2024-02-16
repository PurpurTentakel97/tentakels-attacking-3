//
// Purpur Tentakel
// 16.02.2024
//

#include "BlackHole.hpp"

namespace lgk {
    bool BlackHole::IsBlackHole() const {
        return true;
    }

    void BlackHole::Update(Galaxy_ty_raw) { }

    void BlackHole::AddExtraSize(utl::usize extraSize) {
        m_extraSize += extraSize;
    }

    utl::usize BlackHole::ExtraSize() const {
        return m_extraSize / 100;
    }
} // namespace lgk
