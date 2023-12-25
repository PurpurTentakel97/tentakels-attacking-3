//
// Purpur Tentakel
// 16.02.2022
//

#pragma once
#include "ui_lib/Scene.h"
#include "logic/Galaxy.h"
#include "ui_lib/Table.h"

class PlanetTable final : public Scene {
private:
	Galaxy_ty_raw m_galaxy; ///< contains the current galaxy  of the logic
	Table_ty m_table; ///< contains the table within the planet info's

	/**
	 * initializes the table from the current galaxy.
	 */
	void Initialization();

public:
	/**
	 * ctor and calls to initialize
	 */
	PlanetTable(Vector2 pos, Vector2 size, Alignment alignment,	Galaxy_ty_raw galaxy);

	/**
	 * sets if the scene is currently active.
	 * calls set focus active.
	 */
	void SetActive(bool active, AppContext_ty_c appContext) override;
};
