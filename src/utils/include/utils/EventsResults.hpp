//
// PurpurTentakel
// 08.02.24
//

#pragma once

#include "GameEventTypes.hpp"
#include <alias/AliasUtils.hpp>

namespace utl {
    class EventResult {
    private:
        GameEventType m_type;
        usize m_playerID;

    public:
        EventResult(GameEventType type, usize playerID) : m_type{ type }, m_playerID{ playerID } { }

        [[nodiscard]] GameEventType Type() const {
            return m_type;
        }

        [[nodiscard]] usize PlayerID() const {
            return m_playerID;
        }
    };

    class EngineProblemEventResult final : public EventResult {
    private:
        usize m_years;
        usize m_fleetID;

    public:
        EngineProblemEventResult(GameEventType type, usize years, usize playerID, usize fleetID)
            : EventResult{ type, playerID },
              m_years{ years },
              m_fleetID{ fleetID } { }

        [[nodiscard]] usize Years() const {
            return m_years;
        }


        [[nodiscard]] usize FleetID() const {
            return m_fleetID;
        }
    };
} // namespace utl
