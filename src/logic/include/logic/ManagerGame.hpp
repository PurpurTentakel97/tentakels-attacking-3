//
// PurpurTentakel
// 10.08.22
//

#pragma once
#include "ManagerGalaxy.hpp"
#include "Player.hpp"
#include <event/EventGenerel.hpp>
#include <event/EventListener.hpp>
#include <event/EventsUI.hpp>
#include <memory>
#include <random>
#include <vector>


class GameManager final : public EventListener {
    friend class GalaxyManager;

private:
    std::default_random_engine m_random{ std::default_random_engine() };
    std::unordered_map<PlayerType, Player_ty> m_npcs{};
    std::vector<Player_ty> m_players{};
    std::vector<Player_ty> m_currentRoundPlayers{};
    GalaxyManager m_galaxyManager;
    UpdateResult_ty m_lastUpdateResults{};

    // player
    [[nodiscard]] bool ValidAddPlayer() const;

    [[nodiscard]] unsigned int GetNextPlayerID() const;

    [[nodiscard]] bool IsExistingPlayerID(unsigned int ID) const;

    [[nodiscard]] bool GetCurrentPlayer(Player_ty& currentPlayer) const;

    [[nodiscard]] bool GetNextPlayer(Player_ty& nextPlayer) const;

    void AddPlayer(AddPlayerEvent const* event);

    void EditPlayer(EditPlayerEvent const* event) const;

    void DeletePlayer(DeletePlayerEvent const* event);

    void ResetPlayer();

    void KillPlayer(Player_ty player);

    void CheckPlayerCount() const;

    void ShuffleCurrentRoundPlayer();

    [[nodiscard]] bool CheckValidAddRemovePlayer(std::function<void(bool valid)> forPopup) const;

    void SendCurrentPlayerID();

    void SendNextPlayerID();

    // rounds
    void NextRound(bool valid);

    void NextTurn(bool valid);

    void ValidateNextTurn();

    // fleet
    void AddFleet(SendFleetInstructionEvent const* event);

    [[nodiscard]] bool ValidateAddFleetInput(SendFleetInstructionEvent const* event);

    // game
    void StartGame();

    void StopGame();

    void PauseGame();

    void ResumeGame();

    void QuitGame();

public:
    GameManager();

    void Update();

    void OnEvent(Event const& event) override;
};
