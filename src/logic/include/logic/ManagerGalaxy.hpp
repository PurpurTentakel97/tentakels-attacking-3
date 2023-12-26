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
class SendFleetInstructionEvent;
struct HFightResult;

/**
 * all instructions are executed on the main Galaxy
 */
class GalaxyManager final {
private:
    GameManager* m_gameManager; ///< contains the current game manager
    friend Galaxy;
    Galaxy_ty m_mainGalaxy{ nullptr }; ///< contains the global galaxy with all changes.
    Galaxy_ty m_startGalaxy{
        nullptr
    }; ///< contains the data at round begin. every round it gets overwritten by the main galaxy
    Galaxy_ty m_currentGalaxy{
        nullptr
    }; ///< is used to store the player data of one player. every turn it gets overwritten by the start Galaxy
    Galaxy_ty m_showGalaxy{ nullptr }; ///< is a hardcoded galaxy that is used to guaranty, that it generation is valid.

    /**
	 * filters the current galaxy for relevant only data for current player.
	 */
    void FilterCurrentGalaxy();

public:
    GalaxyManager(GameManager* gameManager);

    /**
	 * generates a new galaxy.
	 * if the new galaxy is valid the old galaxy gets override and informs the ui via event.
	 * if not the old galaxy will be keep and generates an failure popup.
	 */
    void GenerateGalaxy();
    /**
	 * generates a new show galaxy.
	 * if the new galaxy is valid the old galaxy gets override and sends a galaxy* via event to the ui.
	 * if not and an old galaxy exists, the old galaxy will be keep and will be provided via event to the ui.
	 * also prints a log entry to the console.
	 * if not and no galaxy exists it only prints a log entry to the console.
	 */
    void GenerateShowGalaxy();
    /**
	 * copies all galaxies.
	 */
    void CopyGalaxies(CopyGalaxyType copyType);
    /**
	 * return the current galaxy raw pointer.
	 */
    [[nodiscard]] Galaxy* GetGalaxy();
    /**
	 * add a new fleet to the Galaxies.
	 */
    [[nodiscard]] bool AddFleet(SendFleetInstructionEvent const* event, Player_ty currentPlayer);

    /**
	 * returns if the provided player has any moves left.  
	 */
    [[nodiscard]] bool HasMovesLeft(Player_ty_c player) const;

    /**
	 * sets the provided player to neutral player.
	 */
    void KillPlayer(Player_ty_c player, Player_ty_c neutral_player);

    /**
	 * updates the main galaxy
	 */
    [[nodiscard]] UpdateResult_ty Update();
};
