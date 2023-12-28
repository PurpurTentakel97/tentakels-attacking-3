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


class SceneManager final : public eve::EventListener {
private:
    ManagerPopUp m_popUpManager;
    SceneType m_currentSceneType{ SceneType::NONE };
    SceneType m_nextSceneType{ SceneType::NONE };
    std::shared_ptr<Scene> m_currentScene;

    void InitializeNewScene(SceneType sceneType);

    void SwitchScene(AppContext_ty_c appContext);

public:
    SceneManager();

    void SwitchSceneManual();

    void CheckAndUpdate(Vector2 const& mousePosition, AppContext_ty_c appContext);

    void Render(AppContext_ty_c appContext);

    void Resize(AppContext_ty_c appContext);

    void OnEvent(eve::Event const& event) override;

    [[nodiscard]] bool IsValidCurrentScene() const;
};
