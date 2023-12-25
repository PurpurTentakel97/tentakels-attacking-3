//
// Purpur Tentakel
// 24.08.2022
//

#pragma once
#include "ui_lib/UIElement.hpp"
#include "event/EventListener.hpp"
#include "AppContext.h"
#include "SceneManager.h"
#include "ui_lib/HoverRender.h"
#include "logic/GameManager.h"
#include "ui_lib/Focus.h"
#include <vector>
#include <memory>

class Scene;

/**
 * manages the complete UI.
 * contains the logic and calls it to update.
 */
class UIManager final : public EventListener {
private:
	AppContext_ty m_appContext; ///< contains a AppContext ref.
	Focus m_focus; ///< contains the focus system.
	SceneManager m_sceneManager; ///< contains the scene manager.
	GameManager m_gameManager; ///< contains the game logic
	HoverRender m_hover;
	bool m_closeWindow{ false }; ///< contains if the game will quit at the end of the tick
	bool m_isNextFullScreen{ false }; ///< contains if the next frame fill toggle fullscreen
	Resolution m_nextResolution; ///< contains the resolution of the next frame

	/**
	 * sets a bool so that the next frame will toggle full screen.
	 */
	void SetFullScreen();
	/**
	 * Toggles between full screen and window mode.
	 */
	void CheckAndSetToggleFullScreen();

	/**
	 * converts and updates the resolution in Window mode.
	 */
	void CheckAndSetNewResolution();

	/**
	 * checks the quit input.
	 * checks the full screen toggle.
	 * calls the focus and UImanager to update.
	 */
	void CheckAndUpdate();
	/**
	 * start drawing.
	 * draws the background black.
	 * calls the UImanager to render.
	 * calls the focus to render.
	 * draws the FPS in debug build.
	 * ends drawing.
	 */
	void Render();

	/**
	 * sets the window size to the native screen size.
	 * does not update anything because the current size need to be set after toggle.
	 */
	void SetNativeWindowSize();
	/**
	 * sets the current window size from the config to raylib.
	 */
	void SetWindowSize(bool force = false);
	/**
	 * sets the pint ow position if in window mode.
	 */
	void SetWindowPosition();
	/**
	 * sets the target FPS in the raylib.
	 */
	void SetTargetFPS(SetTargetFPSEvent const* event);
	/**
	 * main loop of the program.
	 * loops while not should close.
	 * calls check resolution.
	 * calls generell update.
	 * calls render.
	 */
	void UILoop();

public:
	/**
	 * ctor.
	 * sets edit key in raylib to none.
	 * resize window.
	 * add event listener.
	 */
	UIManager();
	/**
	 * dtor.
	 * removes listener.
	 */
	~UIManager();

	/**
	 * main loop entry.
	 * sets initial scene.
	 * sets initial window mode.
	 * calls the ui loop (main loop).
	 */
	void StartUI();


	void StartUILoop();

	/**
	 * receives all events and calls the member functions.
	 */
	void OnEvent(Event const& event);
	/**
	 * returns an reference if the current focus instance.
	 */
	[[nodiscard]] Focus& GetFocus();
};
