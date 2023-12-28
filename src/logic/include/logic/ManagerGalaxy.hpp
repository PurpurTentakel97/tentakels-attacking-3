//
// PurpurTentakel
// 23.05.23
//

#pragma once
#include <helper/HLogicAlias.hpp>
#include <memory>
#include <vector>

class GameManager;
enum class CopyGalaxyType;
struct HFightResult;

namespace eve {
    class SendFleetInstructionEvent;
}

class GalaxyManager final {
    friend class Galaxy;

private:
    GameManager* m_gameManager;
    Galaxy_ty m_mainGalaxy{ nullptr };
    Galaxy_ty m_startGalaxy{ nullptr };
    Galaxy_ty m_currentGalaxy{ nullptr };
    Galaxy_ty m_showGalaxy{ nullptr };

    void FilterCurrentGalaxy();

public:
    explicit GalaxyManager(GameManager* gameManager);

    void GenerateGalaxy();

    void GenerateShowGalaxy();

    void CopyGalaxies(CopyGalaxyType copyType);

    [[nodiscard]] Galaxy* GetGalaxy();

    [[nodiscard]] bool AddFleet(eve::SendFleetInstructionEvent const* event, Player_ty const& currentPlayer);

    [[nodiscard]] bool HasMovesLeft(Player_ty_c player) const;

    void KillPlayer(Player_ty_c player, Player_ty_c neutral_player);

    [[nodiscard]] UpdateResult_ty Update();
};
