//
// Purpur Tentakel
// 05.09.2022
//

#include "ManagerScene.hpp"
#include "ManagerUI.hpp"
#include "SceneAll.hpp"
#include <app/AppContext.hpp>
#include <helper/HPrint.hpp>
#include <ui_lib/SceneType.hpp>


namespace ui {
    void SceneManager::InitializeNewScene(uil::SceneType const sceneType) {
        switch (sceneType) {
            case uil::SceneType::TEST:
                m_currentScene = std::make_shared<TestScene>();
                return;

            case uil::SceneType::LOGO:
                m_currentScene = std::make_shared<LogoScene>();
                return;

            case uil::SceneType::INTRO:
                m_currentScene = std::make_shared<Intro>();
                return;

            case uil::SceneType::MAIN_MENU:
                m_currentScene = std::make_shared<MainMenu>();
                return;

            case uil::SceneType::NEW_GAME_PLAYER:
                m_currentScene = std::make_shared<NewGamePlayerScene>();
                return;

            case uil::SceneType::NEW_GAME_PARAMETER:
                m_currentScene = std::make_shared<NewGameParameterScene>();
                return;

            case uil::SceneType::VALIDATE_GALAXY:
                m_currentScene = std::make_shared<ValidateGalaxyScene>();
                return;

            case uil::SceneType::MAIN:
                m_currentScene = std::make_shared<MainScene>();
                return;

            case uil::SceneType::GAME_SETTINGS:
                m_currentScene = std::make_shared<GameSettingsScene>();
                return;

            case uil::SceneType::APP_SETTINGS:
                m_currentScene = std::make_shared<AppSettingsScene>();
                return;

            case uil::SceneType::CREDITS:
                m_currentScene = std::make_shared<CreditsScene>();
                return;

            case uil::SceneType::UPDATE_EVALUATION:
                m_currentScene = std::make_shared<UpdateEvaluationScene>();
                return;

            case uil::SceneType::NONE:
                throw std::runtime_error("unexpected scene type NONE in initialize new scene");
        }
        throw std::runtime_error("unexpected scene type in initialize new scene");
    }

    void SceneManager::SwitchScene(app::AppContext_ty_c appContext) {

        if (m_currentSceneType == m_nextSceneType) {
            return;
        }

        eve::ClearFocusEvent const closeEvent;
        appContext.eventManager.InvokeEvent(closeEvent);

        eve::NewFocusLayerEvent const newLayerEvent;
        appContext.eventManager.InvokeEvent(newLayerEvent);

        InitializeNewScene(m_nextSceneType);

        m_currentScene->SetActive(true, appContext);
        m_currentSceneType = m_nextSceneType;

        hlp::Print(hlp::PrintType::INFO, "scene switched to -> {}", GetStringBySceneType(m_currentSceneType));
    }

    SceneManager::SceneManager() {
        app::AppContext::GetInstance().eventManager.AddListener(this);
        hlp::Print(hlp::PrintType::INITIALIZE, "SceneManager");
    }

    void SceneManager::SwitchSceneManual() {
        SwitchScene(app::AppContext::GetInstance());
    }

    void SceneManager::CheckAndUpdate(Vector2 const& mousePosition, app::AppContext_ty_c appContext) {

        SwitchScene(appContext);

        if (!m_popUpManager.IsActivePopUp()) {
            m_currentScene->CheckAndUpdate(mousePosition, appContext);
        }
        m_popUpManager.CheckAndUpdate(mousePosition, appContext);
    }

    void SceneManager::Render(app::AppContext_ty_c appContext) {
        m_currentScene->Render(appContext);
        m_popUpManager.Render(appContext);
    }

    void SceneManager::Resize(app::AppContext_ty_c appContext) {
        m_currentScene->Resize(appContext);
        m_popUpManager.Resize(appContext);
    }

    void SceneManager::OnEvent(eve::Event const& event) {

        if (auto const SceneEvent = dynamic_cast<eve::SwitchSceneEvent const*>(&event)) {
            m_nextSceneType = SceneEvent->GetSceneType();
            return;
        }
    }

    bool SceneManager::IsValidCurrentScene() const {
        return m_currentScene != nullptr;
    }
} // namespace ui
