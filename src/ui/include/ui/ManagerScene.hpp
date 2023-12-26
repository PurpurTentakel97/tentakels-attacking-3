//
// Purpur Tentakel
// 05.09.2022
//

#pragma once
#include "ManagerPopUp.hpp"
#include <memory>
#include <ui_lib/PopUp.hpp>
#include <ui_lib/SceneType.hpp>
#include <unordered_map>
#include <vector>

class Scene;
class UIManager;

/**
 * manages all non support scenes.
 */
class SceneManager final : public EventListener {
private:
    ManagerPopUp m_popUpManager; ///< contains the ManagerPopUp

    SceneType m_currentSceneType{ SceneType::NONE }; ///< contains the current / loaded SceneType
    SceneType m_nextSceneType{ SceneType::NONE };    ///< contains the SceneType of the next tick
    std::shared_ptr<Scene> m_currentScene;           ///< contains the current Scene

    /**
	 * initializes a nuw scene that is represented by the provided SceneType.
	 */
    void InitializeNewScene(SceneType sceneType);
    /**
	 * retunes if the current scene type is the next scene type.
	 * clears current focus.
	 * calls initialize scene.
	 * override current scene type.
	 */
    void SwitchScene(AppContext_ty_c appContext);

public:
    /**
	 * ctor.
	 * only initialization.
	 */
    SceneManager();

    /**
	 * switches the scenes manually if a new scene should be loaded.
	 */
    void SwitchSceneManual();

    /**
	 * calls switch scene.
	 * calls update popups if active popup.
	 * else calls current scene to update.
	 */
    void CheckAndUpdate(Vector2 const& mousePosition, AppContext_ty_c appContext);
    /**
	 * calls current scene to render.
	 * calls the popup manager to render the popups.
	 */
    void Render(AppContext_ty_c appContext);
    /**
	 * calls current scene to resize.
	 * calls the popup manager to resize the popups.
	 */
    void Resize(AppContext_ty_c appContext);

    /**
	 * receives all events and calls the member functions.
	 */
    void OnEvent(Event const& event);

    /**
	 * returns if there is a valid current scene.
	 */
    [[nodiscard]] bool IsValidCurrentScene() const;
};
