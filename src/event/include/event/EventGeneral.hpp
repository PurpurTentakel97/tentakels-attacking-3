//
// Purpur Tentakel
// 10.11.2022
//

#pragma once

#include "EventMain.hpp"
#include <CustomRaylib.hpp>
#include <alias/AliasUtils.hpp>
#include <string>
#include <unordered_map>
#include <utils/RepresentationGalaxy.hpp>
#include <utils/ResultFight.hpp>
#include <utils/ResultMerge.hpp>


namespace eve {
    class PlayerEvent : public Event {
    private:
        std::string m_name;
        Color m_color;

    public:
        PlayerEvent(std::string name, Color const color) : m_name{ std::move(name) }, m_color{ color } { }

        [[nodiscard]] std::string GetName() const {
            return m_name;
        }
        [[nodiscard]] Color GetColor() const {
            return m_color;
        }
    };

    class PlayerWithIDEvent : public PlayerEvent {
    private:
        utl::usize m_ID;

    public:
        PlayerWithIDEvent(utl::usize ID, std::string const& name, Color const color)
            : PlayerEvent{ name, color },
              m_ID{ ID } { }

        [[nodiscard]] utl::usize GetID() const {
            return m_ID;
        }
    };


    class AddPlayerEvent final : public PlayerEvent {
    public:
        using PlayerEvent::PlayerEvent;
    };

    class EditPlayerEvent final : public PlayerWithIDEvent {
    public:
        using PlayerWithIDEvent::PlayerWithIDEvent;
    };

    class DeletePlayerEvent final : public Event {
    private:
        utl::usize m_ID;

    public:
        explicit DeletePlayerEvent(utl::usize const ID) : m_ID{ ID } { }

        [[nodiscard]] utl::usize GetID() const {
            return m_ID;
        }
    };

    class ResetPlayerEvent final : public Event { };

    class LoadCurrentPlayerEvent final : public Event { };

    class KillCurrentPlayerEvent final : public Event { };

    class AddPlayerUIEvent final : public PlayerWithIDEvent {
    public:
        using PlayerWithIDEvent::PlayerWithIDEvent;
    };

    class EditPlayerUIEvent final : public PlayerWithIDEvent {
    public:
        using PlayerWithIDEvent::PlayerWithIDEvent;
    };

    class DeletePlayerUIEvent final : public Event {
    private:
        utl::usize m_ID;

    public:
        explicit DeletePlayerUIEvent(utl::usize const ID) : m_ID{ ID } { }

        [[nodiscard]] utl::usize GetID() const {
            return m_ID;
        }
    };

    class ResetPlayerUIEvent final : public Event { };

    class PlayerIDEvent : public Event {
    private:
        utl::usize m_ID;

    public:
        explicit PlayerIDEvent(utl::usize const ID) : m_ID{ ID } { }
        [[nodiscard]] utl::usize GetID() const {
            return m_ID;
        }
    };

    class UpdateCurrentPlayerIDEvent final : public PlayerIDEvent {
    public:
        using PlayerIDEvent::PlayerIDEvent;
    };

    class UpdateNextPlayerIDEvent final : public PlayerIDEvent {
    public:
        using PlayerIDEvent::PlayerIDEvent;
    };

    class TriggerNextTurnEvent final : public Event { };

    class ShowNextTurnEvent final : public Event { };

    class ShowSkipTurnEvent final : public Event { };

    class ShowEvaluationEvent final : public Event { };

    class GetUpdateEvaluation final : public Event { };

    class SendUpdateEvaluation final : public Event {
    private:
        std::vector<utl::ResultMerge> m_mergeResults;
        std::vector<utl::ResultFight> m_fightResults;

    public:
        SendUpdateEvaluation(std::vector<utl::ResultMerge> mergeResult, std::vector<utl::ResultFight> fightResult)
            : m_mergeResults{ std::move(mergeResult) },
              m_fightResults{ std::move(fightResult) } { }

        [[nodiscard]] std::vector<utl::ResultMerge> GetMergeResults() const {
            return m_mergeResults;
        }
        [[nodiscard]] std::vector<utl::ResultFight> GetFightResults() const {
            return m_fightResults;
        }
    };

    class ValidatePlayerCountEvent final : public Event { };

    class ValidatePlayerCountResultEvent final : public Event {
    private:
        bool m_validPlayerCount;

    public:
        explicit ValidatePlayerCountResultEvent(bool const validPlayerCount)
            : m_validPlayerCount{ validPlayerCount } { }

        [[nodiscard]] bool GetValid() const {
            return m_validPlayerCount;
        }
    };

    class StartGameEvent final : public Event { };

    class StopGameEvent final : public Event { };

    class PauseGameEvent final : public Event { };

    class ResumeGameEvent final : public Event { };

    class QuitGameEvent final : public Event { };

    class SetCurrentLastRoundEvent final : public Event {
    private:
        utl::usize m_lastRound;

    public:
        explicit SetCurrentLastRoundEvent(utl::usize const lastRound) : m_lastRound{ lastRound } { }

        [[nodiscard]] utl::usize GetLastRound() const {
            return m_lastRound;
        }
    };

    class GenerateGalaxyEvent final : public Event { };

    class GalaxyGeneratedUIEvent final : public Event { };

    class GetGalaxyPointerEvent final : public Event { };

    class GetShowGalaxyPointerEvent final : public Event { };

    class SendGalaxyRepresentationEvent final : public Event {
    private:
        utl::RepresentationGalaxy m_galaxy;
        bool m_isShowGalaxy;

    public:
        SendGalaxyRepresentationEvent(utl::RepresentationGalaxy galaxy, bool const isShowGalaxy)
            : m_galaxy{ std::move(galaxy) },
              m_isShowGalaxy{ isShowGalaxy } { }

        [[nodiscard]] utl::RepresentationGalaxy GetGalaxy() const {
            return m_galaxy;
        }
        [[nodiscard]] bool IsShowGalaxy() const {
            return m_isShowGalaxy;
        }
    };

    class SendFleetInstructionEvent final : public Event {
    private:
        utl::usize m_origin;
        utl::usize m_destination;
        utl::usize m_destinationX;
        utl::usize m_destinationY;
        utl::usize m_shipCount;
        utl::FleetInstructionType m_type;

    public:
        SendFleetInstructionEvent(utl::usize const origin,
                                  utl::usize const destination,
                                  utl::usize const destinationX,
                                  utl::usize const destinationY,
                                  utl::usize const shipCount,
                                  utl::FleetInstructionType const type)
            : m_origin{ origin },
              m_destination{ destination },
              m_destinationX{ destinationX },
              m_destinationY{ destinationY },
              m_shipCount{ shipCount },
              m_type{ type } { }

        [[nodiscard]] utl::usize GetOrigin() const {
            return m_origin;
        }
        [[nodiscard]] utl::usize GetDestination() const {
            return m_destination;
        }
        [[nodiscard]] utl::usize GetDestinationX() const {
            return m_destinationX;
        }
        [[nodiscard]] utl::usize GetDestinationY() const {
            return m_destinationY;
        }
        [[nodiscard]] utl::usize GetShipCount() const {
            return m_shipCount;
        }
        [[nodiscard]] utl::FleetInstructionType GetType() const {
            return m_type;
        }
    };

    class ReturnFleetInstructionEvent final : public Event {
    private:
        bool m_isValidFleet;

    public:
        explicit ReturnFleetInstructionEvent(bool const validFeet) : m_isValidFleet{ validFeet } { }

        [[nodiscard]] bool IsValidFleet() const {
            return m_isValidFleet;
        }
    };
} // namespace eve
