//
// Purpur Tentakel
// 15.05.2023
//

#include "helper/HLogicAlias.hpp"
#include "helper/HPlayerData.hpp"
#include "ui_lib/Scene.hpp"
#pragma once


class FleetAndTargetPointTable final : public Scene {
private:
	Galaxy_ty_raw m_galaxy; ///< contains the current galaxy  of the logic
	Table_ty m_table; ///< contains the table within the planet info's

	/**
	 * initializes the table from the current galaxy.
	 */
	void Initialization(PlayerData currentPlayer);

	/**
	 * returns the current position as a string.
	 */
	[[nodiscard]] std::string GetStringFromPosition(vec2pos_ty position, bool const getCoordinates) const;

public:
	/**
	 * ctor and calls to initialize
	 */
	FleetAndTargetPointTable(Vector2 pos, Vector2 size, Alignment alignment, Galaxy_ty_raw galaxy, PlayerData currentPlayer);
	/**
	 * sets if the scene is currently active.
	 * calls set focus active.
	 */
	void SetActive(bool active, AppContext_ty_c appContext) override;
};
