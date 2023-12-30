//
// Purpur Tentakel
// 05.09.2022
//

#pragma once

#include "ManagerPopUp.hpp"
#include <alias/AliasUi.hpp>
#include <alias/AliasUiLib.hpp>
#include <memory>
#include <ui_lib/PopUp.hpp>
#include <ui_lib/SceneType.hpp>
#include <unordered_map>
#include <vector>


namespace ui {
    class SceneManager final : public eve::EventListener {
    private:
        ManagerPopUp m_popUpManager;
        uil::SceneType m_currentSceneType{ uil::SceneType::NONE };
        uil::SceneType m_nextSceneType{ uil::SceneType::NONE };
        std::shared_ptr<uil::Scene> m_currentScene;

        void InitializeNewScene(uil::SceneType sceneType);

        void SwitchScene(app::AppContext_ty_c appContext);

    public:
        SceneManager();

        void SwitchSceneManual();

        void CheckAndUpdate(Vector2 const& mousePosition, app::AppContext_ty_c appContext);

        void Render(app::AppContext_ty_c appContext);

        void Resize(app::AppContext_ty_c appContext);

        void OnEvent(eve::Event const& event) override;

        [[nodiscard]] bool IsValidCurrentScene() const;
    };
} // namespace ui
