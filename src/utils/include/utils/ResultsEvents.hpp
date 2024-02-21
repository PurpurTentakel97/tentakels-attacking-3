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
        GameEventType m_type;
        usize m_playerID;

    public:
        ResultEvent(GameEventType type, usize playerID) : m_type{ type }, m_playerID{ playerID } { }

        virtual ~ResultEvent() = default;

        [[nodiscard]] GameEventType Type() const {
            return m_type;
        }

        [[nodiscard]] usize PlayerID() const {
            return m_playerID;
        }
    };

    class ResultEventPirates final : public ResultEvent {
    private:
        usize m_ships;
        vec2pos_ty m_position;

    public:
        ResultEventPirates(usize playerID, usize ships, vec2pos_ty position)
            : ResultEvent{ GameEventType::PIRATES, playerID },
              m_ships{ ships },
              m_position{ position } { }

        [[nodiscard]] usize Ships() const {
            return m_ships;
        }

        [[nodiscard]] vec2pos_ty Position() const {
            return m_position;
        }
    };

    class ResultEventRevolts final : public ResultEvent {
    private:
        usize m_planetID;
        usize m_shipCount;

    public:
        ResultEventRevolts(usize playerID, usize planetID, usize shipCount)
            : ResultEvent{ GameEventType::REVOLTS, playerID },
              m_planetID{ planetID },
              m_shipCount{ shipCount } { }

        [[nodiscard]] usize PlanetID() const {
            return m_planetID;
        }

        [[nodiscard]] usize ShipCount() const {
            return m_shipCount;
        }
    };

    class ResultEventRenagateShips final : public ResultEvent {
    private:
        usize m_fleetID;
        usize m_shipCount;

    public:
        ResultEventRenagateShips(usize playerID, usize fleetID, usize shipCount)
            : ResultEvent{ GameEventType::RENEGADE_SHIPS, playerID },
              m_fleetID{ fleetID },
              m_shipCount{ shipCount } { }

        [[nodiscard]] usize FleetID() const {
            return m_fleetID;
        }

        [[nodiscard]] usize ShipCount() const {
            return m_shipCount;
        }
    };

    class ResultEventSupernova final : public ResultEvent {
    private:
        usize m_planetID;
        usize m_shipsDestroyed;

    public:
        ResultEventSupernova(usize playerID, usize planetID, usize shipsDestroyed)
            : ResultEvent{ GameEventType::SUPERNOVA, playerID },
              m_planetID{ planetID },
              m_shipsDestroyed{ shipsDestroyed } { }

        [[nodiscard]] usize PlanetID() const {
            return m_planetID;
        };

        [[nodiscard]] usize ShipsDestroyed() const {
            return m_shipsDestroyed;
        }
    };

    class ResultEventEngineProblem final : public ResultEvent {
    private:
        usize m_years;
        usize m_fleetID;

    public:
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
