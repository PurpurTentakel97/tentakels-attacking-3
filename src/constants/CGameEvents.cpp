//
// Purpur Tentakel
// 12.07.2023
//

#include "CGameEvents.hpp"

namespace cst {
    void GameEvents::SetFlag(utl::GameEventType const type, bool const active) {
        if (active) {
            events |= type;
        } else {
            if ((type & utl::GameEventType::GLOBAL) == utl::GameEventType::GLOBAL) {
                events = static_cast<utl::GameEventType>(0b11000000);
                return;
            }
            events &= ~type;
        }
    }

    bool GameEvents::IsFlag(utl::GameEventType const type) const {
        return (events & type) == type;
    }

    utl::Probability GameEvents::ChanceByType(utl::GameEventType type) const {
        switch (type) {
                // clang-format off
            case utl::GameEventType::PIRATES:        return m_pirateChance       ;
            case utl::GameEventType::REVOLTS:        return m_revoltChance       ;
            case utl::GameEventType::RENEGADE_SHIPS: return m_renegadeShipsChance;
            case utl::GameEventType::BLACK_HOLE:     return m_blackHoleChance    ;
            case utl::GameEventType::SUPERNOVA:      return m_supernovaChance    ;
            case utl::GameEventType::ENGINE_PROBLEM: return m_engineProblemChance;
            case utl::GameEventType::GLOBAL:         return m_globalChance       ;
                // clang-format on
        }
        std::unreachable();
    }
} // namespace cst
