//
// Purpur Tentakel
// 10.11.2022
//

#pragma once
#include "EventMain.hpp"
#include <CustomRaylib.hpp>
#include <helper/HFightResult.hpp>
#include <helper/HLogicAlias.hpp>
#include <helper/HMergeResult.hpp>
#include <string>
#include <unordered_map>


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
        unsigned int m_ID;

    public:
        PlayerWithIDEvent(unsigned int ID, std::string const& name, Color const color)
            : PlayerEvent{ name, color },
              m_ID{ ID } { }

        [[nodiscard]] unsigned int GetID() const {
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
        unsigned int m_ID;

    public:
        explicit DeletePlayerEvent(unsigned int const ID) : m_ID{ ID } { }

        [[nodiscard]] unsigned int GetID() const {
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
        unsigned int m_ID;

    public:
        explicit DeletePlayerUIEvent(unsigned int const ID) : m_ID{ ID } { }

        [[nodiscard]] unsigned int GetID() const {
            return m_ID;
        }
    };

    class ResetPlayerUIEvent final : public Event { };

    class PlayerIDEvent : public Event {
    private:
        unsigned int m_ID;

    public:
        explicit PlayerIDEvent(unsigned int const ID) : m_ID{ ID } { }
        [[nodiscard]] unsigned int GetID() const {
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
        std::vector<HMergeResult> m_mergeResults;
        std::vector<HFightResult> m_fightResults;

    public:
        SendUpdateEvaluation(std::vector<HMergeResult> mergeResult, std::vector<HFightResult> fightResult)
            : m_mergeResults{ std::move(mergeResult) },
              m_fightResults{ std::move(fightResult) } { }

        [[nodiscard]] std::vector<HMergeResult> GetMergeResults() const {
            return m_mergeResults;
        }
        [[nodiscard]] std::vector<HFightResult> GetFightResults() const {
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
        size_t m_lastRound;

    public:
        explicit SetCurrentLastRoundEvent(size_t const lastRound) : m_lastRound{ lastRound } { }

        [[nodiscard]] size_t GetLastRound() const {
            return m_lastRound;
        }
    };

    class GenerateGalaxyEvent final : public Event { };

    class GalaxyGeneratedUIEvent final : public Event { };

    class GetGalaxyPointerEvent final : public Event { };

    class GetShowGalaxyPointerEvent final : public Event { };

    class SendGalaxyPointerEvent final : public Event {
    private:
        Galaxy_ty_c_raw m_galaxy;
        bool m_isShowGalaxy;

    public:
        SendGalaxyPointerEvent(Galaxy_ty_c_raw const galaxy, bool const isShowGalaxy)
            : m_galaxy{ galaxy },
              m_isShowGalaxy{ isShowGalaxy } { }

        [[nodiscard]] Galaxy_ty_raw GetGalaxy() const {
            return m_galaxy;
        }
        [[nodiscard]] bool IsShowGalaxy() const {
            return m_isShowGalaxy;
        }
    };

    class SendFleetInstructionEvent final : public Event {
    private:
        unsigned int m_origin;
        unsigned int m_destination;
        int m_destinationX;
        int m_destinationY;
        size_t m_shipCount;

    public:
        SendFleetInstructionEvent(
                unsigned int const origin,
                unsigned int const destination,
                int const destinationX,
                int const destinationY,
                size_t const shipCount
        )
            : m_origin{ origin },
              m_destination{ destination },
              m_destinationX{ destinationX },
              m_destinationY{ destinationY },
              m_shipCount{ shipCount } { }

        [[nodiscard]] unsigned int GetOrigin() const {
            return m_origin;
        }
        [[nodiscard]] unsigned int GetDestination() const {
            return m_destination;
        }
        [[nodiscard]] int GetDestinationX() const {
            return m_destinationX;
        }
        [[nodiscard]] int GetDestinationY() const {
            return m_destinationY;
        }
        [[nodiscard]] size_t GetShipCount() const {
            return m_shipCount;
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
