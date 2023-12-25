//
// Purpur Tentakel
// 10.11.2022
//

#pragma once
#include "MainEvent.hpp"
#include "CustomRaylib.h"
#include "helper/HLogicAlias.hpp"
#include "helper/HFightResult.h"
#include "helper/HMergeResult.h"
#include <string>
#include <unordered_map>

/**
 * general event to provide player name and color.
 */
class PlayerEvent : public Event {
private:
	std::string m_name;
	Color m_color;

public:
	PlayerEvent(std::string const& name, Color color)
		: m_name{ name }, m_color{ color } { }

	[[nodiscard]] std::string GetName() const {
		return m_name;
	}
	[[nodiscard]] Color GetColor() const {
		return m_color;
	}
};
/**
 * general event to provide player ID, name and color.
 */
class PlayerWithIDEvent : public PlayerEvent {
private:
	unsigned int m_ID;

public:
	PlayerWithIDEvent(unsigned int ID, std::string const& name, Color color)
		: PlayerEvent{ name, color }, m_ID{ ID } { }

	[[nodiscard]] unsigned int GetID() const {
		return m_ID;
	}
};

/**
 * use this to add a player in the logic.
 */
class AddPlayerEvent final : public PlayerEvent {
public:
	using PlayerEvent::PlayerEvent;
};
/**
 * use this to edit a player in the lockige.
 */
class EditPlayerEvent final : public PlayerWithIDEvent {
public:
	using PlayerWithIDEvent::PlayerWithIDEvent;
};
/**
 * use this to delete a player by id in the logic.
 */
class DeletePlayerEvent final : public Event {
private:
	unsigned int m_ID;
public:
	DeletePlayerEvent(unsigned int ID)
		:m_ID{ ID } { }

	[[nodiscard]] unsigned int GetID() const {
		return m_ID;
	}
};
/**
 * use this to remove all player in logic.
 */
class ResetPlayerEvent final : public Event { };
/**
 * use this to load the current player data.
 */
class LoadCurrentPlayerEvent final : public Event { };
/**
 * use this to kill the current player manually
 */
class KillCurrentPlayerEvent final : public Event { };

/**
 * "callback event" from AddPlayerEvent.
 * use this so add a player in PlayerCollection
 */
class AddPlayerUIEvent final : public PlayerWithIDEvent {
public:
	using PlayerWithIDEvent::PlayerWithIDEvent;
};
/**
 * "callback event" from EditPlayerEvent.
 * use this to edit a player in PlayerCollection
 */
class EditPlayerUIEvent final : public PlayerWithIDEvent {
public:
	using PlayerWithIDEvent::PlayerWithIDEvent;
};
/**
 * "callback event" from DeletePlayerEvent.
 * use this to delete a player in PlayerCollection
 */
class DeletePlayerUIEvent final : public Event {
private:
	unsigned int m_ID;
public:
	DeletePlayerUIEvent(unsigned int ID)
		:m_ID{ ID } { }

	[[nodiscard]] unsigned int GetID() const {
		return m_ID;
	}
};
/**
 * "callback event" from ResetPlayerEvent.
 * use this remove all player from PlayerCollection
 */
class ResetPlayerUIEvent final : public Event { };

/**
 * general event to provide a player id.
 */
class PlayerIDEvent : public Event {
private:
	unsigned int m_ID;

public:
	PlayerIDEvent(unsigned int ID)
		:m_ID{ ID } { }
	[[nodiscard]] unsigned int GetID() const {
		return m_ID;
	}
};
/**
 * use this to update the current player id in the UI.
 */
class UpdateCurrentPlayerIDEvent final : public PlayerIDEvent {
public:
	using PlayerIDEvent::PlayerIDEvent;
};
/**
 * use this to update the next player id in the UI.
 */
class UpdateNextPlayerIDEvent final : public PlayerIDEvent {
public:
	using PlayerIDEvent::PlayerIDEvent;
};

/**
 * use this to trigger the logic to evaluate the next turn or round if no player remaining.
 */
class TriggerNextTurnEvent final : public Event { };
/**
 * use this to trigger the ui to show the next turn.
 */
class ShowNextTurnEvent final : public Event { };
/**
 * use this to skip the next turn.
 */
class ShowSkipTurnEvent final : public Event { };
/**
 * use this to trigger the ui to show the next round.
 */
class ShowEvaluationEvent final : public Event { };

/**
 * use this to get the update evaluation.
 */
class GetUpdateEvaluation final : public Event { };
/**
 * sends the update evaluation.
 */
class SendUpdateEvaluation final : public Event {
private:
	std::vector<HMergeResult> m_mergeResults;
	std::vector<HFightResult> m_fightResults;

public:
	SendUpdateEvaluation(std::vector<HMergeResult> mergeResult, std::vector<HFightResult> fightResult)
		: m_mergeResults{ mergeResult }, m_fightResults { fightResult } { }

	[[nodiscard]] std::vector<HMergeResult> GetMergeResults() const {
		return m_mergeResults;
	}
	[[nodiscard]] std::vector<HFightResult> GetFightResults() const {
		return m_fightResults;
	}
};

/**
 * use this to trigger the logic to validate the Player count.
 * return an ValidatePlayerCountResultEvent.
 */
class ValidatePlayerCountEvent final : public Event { };
/**
 * use this to return the value of ValidatePlayerCountEvent.
 * ui should listen to that.
 */
class ValidatePlayerCountResultEvent final : public Event {
private:
	bool m_validPlayerCount;

public:
	ValidatePlayerCountResultEvent(bool validPlayerCount)
		: m_validPlayerCount{ validPlayerCount } { }

	[[nodiscard]] bool GetValid() const {
		return m_validPlayerCount;
	}
};

/**
 * use this to trigger the logic to start the game.
 */
class StartGameEvent  final : public Event { };
/**
 * use this to trigger the logic to end the game.
 */
class StopGameEvent   final : public Event { };
/**
 * use this to trigger the logic to pause the game.
 */
class PauseGameEvent  final : public Event { };
/**
 * use this to trigger the logic to resume the game.
 */
class ResumeGameEvent final : public Event { };
/**
 * use this to trigger the logic to quit the game.
 */
class QuitGameEvent   final : public Event { };

/**
 * use this to trigger the constants to update the target last round.
 */
class SetCurrentLastRoundEvent final : public Event {
private:
    size_t m_lastRound;

public:
    SetCurrentLastRoundEvent(size_t lastRound) :m_lastRound{ lastRound } { }

    [[nodiscard]] size_t GetLastRound() const {
        return m_lastRound;
	}
};

/**
 * use this to trigger the logic to generate a new galaxy.
 */
class GenerateGalaxyEvent final : public Event { };
/**
 * use this to trigger the logic to generate a new show galaxy.
 */
class GalaxyGeneratedUIEvent final : public Event { };

/**
 * use this to trigger the logic to return a galaxy pointer.
 * returns a SendGalaxyPointerEvent.
 */
class GetGalaxyPointerEvent final : public Event { };
/**
 * use this to trigger the logic to return a show galaxy pointer.
 * returns a SendGalaxyPointerEvent.
 */
class GetShowGalaxyPointerEvent final : public Event { };
/**
 * sends a galaxy pointer to the ui.
 */
class SendGalaxyPointerEvent final : public Event {
private:
	Galaxy_ty_c_raw m_galaxy;
	bool m_isShowGalaxy;

public:
	SendGalaxyPointerEvent(Galaxy_ty_c_raw galaxy, bool isShowGalaxy)
		: m_galaxy{ galaxy }, m_isShowGalaxy{ isShowGalaxy } { }

	[[nodiscard]] Galaxy_ty_raw GetGalaxy() const {
		return m_galaxy;
	}
	[[nodiscard]] bool IsShowGalaxy() const {
		return m_isShowGalaxy;
	}
};


/**
 * send a ship instruction into the logic.
 */
class SendFleetInstructionEvent final : public Event {
private:
	unsigned int m_origin;
	unsigned int m_destination;
	int m_destinationX;
	int m_destinationY;
	size_t m_shipCount;

public:
	SendFleetInstructionEvent(unsigned int origin, unsigned int destination, int destinationX,
		int destinationY, size_t shipCount)
		: m_origin{ origin }, m_destination{ destination }, m_destinationX{ destinationX },
		m_destinationY{ destinationY }, m_shipCount{ shipCount } { }

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
/**
 * functions as the return of SendFleetInstructionEvent.
 */
class ReturnFleetInstructionEvent final : public Event {
private:
	bool m_isValidFleet;

public:
	ReturnFleetInstructionEvent(bool validFeet)
		: m_isValidFleet{ validFeet } { }

	[[nodiscard]] bool IsValidFleet() const {
		return m_isValidFleet;
	}
};
