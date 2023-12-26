//
// Purpur Tentakel
// 05.09.2022
//

#include "ManagerScene.hpp"
#include "AppContext.hpp"
#include "CustomRaylib.hpp"
#include "ManagerUI.hpp"
#include "PopUpMessage.hpp"
#include "SceneAll.hpp"
#include "helper/HPrint.hpp"
#include "ui_lib/Scene.hpp"
#include "ui_lib/SceneType.hpp"


void SceneManager::InitializeNewScene(SceneType sceneType) {
    switch (sceneType) {
        case SceneType::TEST:
            m_currentScene = std::make_shared<TestScene>();
            return;

        case SceneType::LOGO:
            m_currentScene = std::make_shared<LogoScene>();
            return;

        case SceneType::INTRO:
            m_currentScene = std::make_shared<Intro>();
            return;

        case SceneType::MAIN_MENU:
            m_currentScene = std::make_shared<MainMenu>();
            return;

        case SceneType::NEW_GAME_PLAYER:
            m_currentScene = std::make_shared<NewGamePlayerScene>();
            return;

        case SceneType::NEW_GAME_PARAMETER:
            m_currentScene = std::make_shared<NewGameParameterScene>();
            return;

        case SceneType::VALIDATE_GALAXY:
            m_currentScene = std::make_shared<ValidateGalaxyScene>();
            return;

        case SceneType::MAIN:
            m_currentScene = std::make_shared<MainScene>();
            return;

        case SceneType::GAME_SETTINGS:
            m_currentScene = std::make_shared<GameSettingsScene>();
            return;

        case SceneType::APP_SETTINGS:
            m_currentScene = std::make_shared<AppSettingsScene>();
            return;

        case SceneType::CREDITS:
            m_currentScene = std::make_shared<CreditsScene>();
            return;

        case SceneType::UPDATE_EVALUATION:
            m_currentScene = std::make_shared<UpdateEvaluationScene>();
            return;

        case SceneType::NONE:
            throw std::runtime_error("unexpected scene type NONE in initialize new scene");
    }
    throw std::runtime_error("unexpected scene type in initialize new scene");
}

void SceneManager::SwitchScene(AppContext_ty_c appContext) {

    if (m_currentSceneType == m_nextSceneType) {
        return;
    }

    ClearFocusEvent const closeEvent;
    appContext.eventManager.InvokeEvent(closeEvent);

    NewFocusLayerEvent const newLayerEvent;
    appContext.eventManager.InvokeEvent(newLayerEvent);

    InitializeNewScene(m_nextSceneType);

    m_currentScene->SetActive(true, appContext);
    m_currentSceneType = m_nextSceneType;

    Print(PrintType::INFO, "scene switched to -> {}", GetStringBySceneType(m_currentSceneType));
}

SceneManager::SceneManager() {
    AppContext::GetInstance().eventManager.AddListener(this);
    Print(PrintType::INITIALIZE, "SceneManager");
}

void SceneManager::SwitchSceneManual() {
    SwitchScene(AppContext::GetInstance());
}

void SceneManager::CheckAndUpdate(Vector2 const& mousePosition, AppContext_ty_c appContext) {

    SwitchScene(appContext);

    if (!m_popUpManager.IsActivePopUp()) {
        m_currentScene->CheckAndUpdate(mousePosition, appContext);
    }
    m_popUpManager.CheckAndUpdate(mousePosition, appContext);
}
void SceneManager::Render(AppContext_ty_c appContext) {
    m_currentScene->Render(appContext);
    m_popUpManager.Render(appContext);
}
void SceneManager::Resize(AppContext_ty_c appContext) {
    m_currentScene->Resize(appContext);
    m_popUpManager.Resize(appContext);
}

void SceneManager::OnEvent(Event const& event) {

    if (auto const SceneEvent = dynamic_cast<SwitchSceneEvent const*>(&event)) {
        m_nextSceneType = SceneEvent->GetSceneType();
        return;
    }
}

bool SceneManager::IsValidCurrentScene() const {
    return m_currentScene != nullptr;
}
