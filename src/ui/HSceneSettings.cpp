//
// Purpur Tentakel
// 01.11.2022
//

#include "HSceneSettings.hpp"
#include <AppContext.hpp>
#include <event/EventGenerel.hpp>
#include <ui_lib/ButtonClassic.hpp>
#include <ui_lib/Line.hpp>
#include <ui_lib/SceneType.hpp>
#include <ui_lib/Title.hpp>

void SettingsScene::Initialize() {
    AppContext_ty appContext{ AppContext::GetInstance() };

    // title
    m_elements.push_back(std::make_shared<Title>(
            GetElementPosition(0.5f, 0.025f),
            GetElementSize(0.8f, 0.25f),
            Alignment::TOP_MID,
            false
    ));

    // line
    m_elements.push_back(
            std::make_shared<Line>(GetElementPosition(0.5f, 0.3f), GetElementPosition(0.5f, 0.95f), 2.0f, WHITE)
    );

    // btn
    auto continueBtn = std::make_shared<ClassicButton>(
            1000,
            GetElementPosition(0.75f, 0.95f),
            GetElementSize(0.15f, 0.1f),
            Alignment::BOTTOM_MID,
            appContext.languageManager.Text("scene_settings_continue_btn"),
            SoundType::ACCEPTED
    );
    continueBtn->SetEnabled(appContext.constants.global.isGameRunning);
    continueBtn->SetOnClick([]() {
        eve::ResumeGameEvent const event{};
        AppContext::GetInstance().eventManager.InvokeEvent(event);
    });
    m_elements.push_back(continueBtn);

    auto backBtn = std::make_shared<ClassicButton>(
            1001,
            GetElementPosition(0.25f, 0.95f),
            GetElementSize(0.15f, 0.1f),
            Alignment::BOTTOM_MID,
            appContext.languageManager.Text("scene_settings_main_menu_btn"),
            SoundType::CLICKED_RELEASE_STD
    );
    backBtn->SetOnClick([]() {
        AppContext::GetInstance().eventManager.InvokeEvent(eve::SwitchSceneEvent{ SceneType::MAIN_MENU });
    });
    m_elements.push_back(backBtn);
}

SettingsScene::SettingsScene()
    : Scene{
          { 0.0f, 0.0f },
          { 1.0f, 1.0f },
          Alignment::DEFAULT
} {
    Initialize();
}

void SettingsScene::CheckAndUpdate(Vector2 const& mousePosition, AppContext_ty_c appContext) {
    Scene::CheckAndUpdate(mousePosition, appContext);
}

void SettingsScene::Render(AppContext_ty_c appContext) {
    Scene::Render(appContext);
}

void SettingsScene::Resize(AppContext_ty_c appContext) {
    Scene::Resize(appContext);
}
