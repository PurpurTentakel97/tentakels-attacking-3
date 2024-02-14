//
// PurpurTentakel
// 10.08.22
//

#pragma once

#include "ManagerGalaxy.hpp"
#include "Player.hpp"
#include <alias/AliasUtils.hpp>
#include <event/EventGeneral.hpp>
#include <event/EventListener.hpp>
#include <event/EventsUI.hpp>
#include <memory>
#include <random>
#include <utils/GameEventTypes.hpp>
#include <utils/ResultUpdate.hpp>
#include <utils/ResultsEvents.hpp>
#include <vector>


namespace lgk {
    class GameManager final : public eve::EventListener {
        friend class GalaxyManager;

    private:
        std::default_random_engine m_random{ std::default_random_engine() };
        std::unordered_map<PlayerType, Player_ty> m_npcs{};
        std::vector<Player_ty> m_players{};
        std::vector<Player_ty> m_currentRoundPlayers{};
        GalaxyManager m_galaxyManager;
        utl::ResultUpdate m_lastUpdateResults{};

        // player
        [[nodiscard]] bool ValidAddPlayer() const;

        [[nodiscard]] utl::usize GetNextPlayerID() const;

        [[nodiscard]] bool IsExistingPlayerID(utl::usize ID) const;

        [[nodiscard]] bool GetCurrentPlayer(Player_ty& currentPlayer) const;

        [[nodiscard]] bool GetNextPlayer(Player_ty& nextPlayer) const;

        void AddPlayer(eve::AddPlayerEvent const* event);

        void EditPlayer(eve::EditPlayerEvent const* event) const;

        void DeletePlayer(eve::DeletePlayerEvent const* event);

        void ResetPlayer();

        void KillPlayer(Player_ty const& player);

        void CheckPlayerCount() const;

        void ShuffleCurrentRoundPlayer();

        [[nodiscard]] static bool CheckValidAddRemovePlayer(std::function<void(bool valid)> forPopup);

        void SendCurrentPlayerID();

        void SendNextPlayerID();

        // rounds
        void NextRound(bool valid);

        void NextTurn(bool valid);

        void ValidateNextTurn();

        // fleet
        void AddFleet(eve::SendFleetInstructionEvent const* event);

        // events
        [[nodiscard]] std::vector<utl::ResultUpdate::event_ty> UpdateEvents();

        [[nodiscard]] static bool IsSingleGameEvent(utl::GameEventType type);

        [[nodiscard]] utl::ResultUpdate::event_ty RaiseEvent(utl::GameEventType type);

        [[nodiscard]] std::shared_ptr<utl::ResultEvent> HandlePirates();

        [[nodiscard]] std::shared_ptr<utl::ResultEvent> HandleRevolts();

        [[nodiscard]] std::shared_ptr<utl::ResultEvent> HandleRenegadeShips();

        [[nodiscard]] std::shared_ptr<utl::ResultEvent> HandleBlackHole();

        [[nodiscard]] std::shared_ptr<utl::ResultEvent> HandleSupernova();

        [[nodiscard]] std::shared_ptr<utl::ResultEventEngineProblem> HandleEngineProblem();

        // game
        void StartGame();

        void StopGame();

        static void PauseGame();

        static void ResumeGame();

        void QuitGame();

    public:
        GameManager();

        ~GameManager() override;

        void Update();

        void OnEvent(eve::Event const& event) override;
    };
} // namespace lgk
