//
// Purpur Tentakel
// 12.07.2023
//

#include "CGameEvents.hpp"

namespace cst {
    void GameEvents::SetFlag(GameEventType const type, bool const active) {
        if (active) {
            events |= type;
        } else {
            if ((type & GameEventType::GLOBAL) == GameEventType::GLOBAL) {
                events = static_cast<GameEventType>(0b11000000);
                return;
            }
            events &= ~type;
        }
    }

    bool GameEvents::IsFlag(GameEventType const type) const {
        return (events & type) == type;
    }

    utl::Probability GameEvents::ChanceByType(GameEventType type) const {
        switch (type) {
                // clang-format off
            case GameEventType::PIRATES:        return m_pirateChance       ;
            case GameEventType::REVOLTS:        return m_revoltChance       ;
            case GameEventType::RENEGADE_SHIPS: return m_renegadeShipsChance;
            case GameEventType::BLACK_HOLE:     return m_blackHoleChance    ;
            case GameEventType::SUPERNOVA:      return m_supernovaChance    ;
            case GameEventType::ENGINE_PROBLEM: return m_engineProblemChance;
            case GameEventType::GLOBAL:         return m_globalChance       ;
                // clang-format on
        }
        std::unreachable();
    }
} // namespace cst
