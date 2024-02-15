//
// PurpurTentakel
// 08.02.24
//

#pragma once

#include "GameEventTypes.hpp"
#include <alias/AliasUtils.hpp>

namespace utl {
    class ResultEvent {
    private:
        GameEventType m_type{};
        usize m_playerID{};

    public:
        ResultEvent() = default;
        ResultEvent(GameEventType type, usize playerID) : m_type{ type }, m_playerID{ playerID } { }

        virtual ~ResultEvent() = default;

        [[nodiscard]] GameEventType Type() const {
            return m_type;
        }

        [[nodiscard]] usize PlayerID() const {
            return m_playerID;
        }
    };

    class ResultEventSupernova final : public ResultEvent {
    private:
        usize m_planetID{};

    public:
        using ResultEvent::ResultEvent;
        ResultEventSupernova(usize playerID, usize planetID)
            : ResultEvent{ GameEventType::SUPERNOVA, playerID },
              m_planetID{ planetID } { }

        [[nodiscard]] usize PlanetID() const {
            return m_planetID;
        };
    };

    class ResultEventEngineProblem final : public ResultEvent {
    private:
        usize m_years{};
        usize m_fleetID{};

    public:
        using ResultEvent::ResultEvent;
        ResultEventEngineProblem(usize playerID, usize fleetID, usize years)
            : ResultEvent{ GameEventType::ENGINE_PROBLEM, playerID },
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
