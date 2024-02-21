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
            case utl::GameEventType::PIRATES:            return pirateChance           ;
            case utl::GameEventType::REVOLTS:            return revoltChance           ;
            case utl::GameEventType::RENEGADE_SHIPS:     return renegadeShipsChance    ;
            case utl::GameEventType::SUPERNOVA:          return supernovaChance        ;
            case utl::GameEventType::ENGINE_PROBLEM:     return engineProblemChance    ;
            case utl::GameEventType::PRODUCTION_PROBLEM: return productionProblemChance;
            case utl::GameEventType::GLOBAL:             return globalChance           ;
                // clang-format on
        }
        std::unreachable();
    }
} // namespace cst
