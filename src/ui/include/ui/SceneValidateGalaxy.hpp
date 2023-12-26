//
// Purpur Tentakel
// 20.11.2022
//

#pragma once
#include "ui_lib/Scene.h"
#include "event/EventListener.hpp"
#include <memory>

class GalaxyScene;
class SendGalaxyPointerEvent;

/**
 * provides a scenes where the generates galaxy can be validated.
 * a new galaxy can be validated if wanted.
 */
class ValidateGalaxyScene : public Scene{
private:
	std::shared_ptr<GalaxyScene> m_galaxy; ///< contains the galaxy scene

	/**
	 * initializes all ui elements.
	 * connects the actions.
	 */
	void Initialize();
	/**
	 * initializes the player legen.
	 * matches the colors.
	 */
	void InitializePlayerLegend();
	/**
	 * initializes a ui galaxy.
	 */
	void InitializeGalaxy();

	/**
	 * deletes the old galaxy.
	 * generates a new one via event.
	 * calls to initialize it.
	 */
	void NewGalaxy();

public:
	/**
	 * ctor.
	 * only initialization.
	 */
	ValidateGalaxyScene();
};
