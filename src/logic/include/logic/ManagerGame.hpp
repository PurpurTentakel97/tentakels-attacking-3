//
// PurpurTentakel
// 10.08.22
//

#pragma once

#include "ManagerGalaxy.hpp"
#include "Player.hpp"
#include <utils/GameEventTypes.hpp>
#include <utils/EventsResults.hpp>
#include <utils/UpdateResult.hpp>
#include <alias/AliasUtils.hpp>
#include <event/EventGeneral.hpp>
#include <event/EventListener.hpp>
#include <event/EventsUI.hpp>
#include <memory>
#include <random>
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
        utl::UpdateResult m_lastUpdateResults{};

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
        [[nodiscard]] std::vector<utl::ResultEvent> UpdateEvents();

        [[nodiscard]] static bool IsSingleGameEvent(utl::GameEventType type);

        [[nodiscard]] utl::ResultEvent RaiseEvent(utl::GameEventType type);

        [[nodiscard]] utl::ResultEvent HandlePirates();

        [[nodiscard]] utl::ResultEvent HandleRevolts();

        [[nodiscard]] utl::ResultEvent HandleRenegadeShips();

        [[nodiscard]] utl::ResultEvent HandleBlackHole();

        [[nodiscard]] utl::ResultEvent HandleSupernova();

        [[nodiscard]] utl::ResultEvent HandleEngineProblem();

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
