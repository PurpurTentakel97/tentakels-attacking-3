//
// Purpur Tentakel
// 19.09.2022
//

#pragma once
#include "ui_lib/Scene.hpp"

/**
 * provides the main menu scene.
 */
class MainMenu final : public Scene{
private:
	/**
	 * initializes all ui elements.
	 * connects the actions.
	 */
	void Initialize();

public:
	/**
	 * initialization.
	 */
	MainMenu();
};
