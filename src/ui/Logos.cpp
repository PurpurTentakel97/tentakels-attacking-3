//
// Purpur Tentakel
// 14.09.2022
//

#include "Logos.h"
#include "AppContext.hpp"
#include "UIManager.h"
#include "helper/HInput.h"
#include "ui_lib/Picture.h"
#include "ui_lib/SceneType.h"
#include "ui_lib/Text.h"
#include <memory>


void LogoScene::Initialize() {
    AppContext_ty_c appContext{ AppContext::GetInstance() };

    auto logo = std::make_shared<Picture>(
            GetElementPosition(0.5f, 0.1f),
            GetElementSize(0.0f, 0.5f),
            Alignment::TOP_MID,
            AssetType::LOGO
    );
    m_elements.push_back(logo);

    auto mainText = std::make_shared<Text>(
            GetElementPosition(0.5f, 0.65f),
            GetElementSize(1.0f, 0.1f),
            Alignment::TOP_MID,
            Alignment::TOP_MID,
            0.07f,
            appContext.languageManager.Text("scene_logo_subtitle", "Purpur Tentakel")
    );
    //mainText->RenderRectangle(true);
    m_elements.push_back(mainText);

    auto skipText = std::make_shared<Text>(
            GetElementPosition(0.99f, 0.97f),
            GetElementSize(0.2f, 0.03f),
            Alignment::BOTTOM_RIGHT,
            Alignment::BOTTOM_RIGHT,
            0.03f,
            appContext.languageManager.Text("scene_logo_skip", "[ESC]")
    );
    // skipText->RenderRectangle(true);
    m_elements.push_back(skipText);
}

LogoScene::LogoScene()
	:Scene{ {0.0f, 0.0f}, {1.0f, 1.0f}, Alignment::DEFAULT },
	m_time{ GetTime() } {
    Initialize();
}
void LogoScene::CheckAndUpdate(Vector2 const& mousePosition, AppContext_ty_c appContext) {
    bool const nextScene{ IsBackInputPressed() or (m_time + m_sceneLength) < GetTime() };
    if (nextScene) {
        SwitchSceneEvent event{ m_nextScene };
        appContext.eventManager.InvokeEvent(event);
    }

    for (auto e : m_elements) {
        e->CheckAndUpdate(mousePosition, appContext);
    }
}
void LogoScene::Render(AppContext_ty_c appContext) {
    for (auto e : m_elements) {
        e->Render(appContext);
    }
}
void LogoScene::Resize(AppContext_ty_c appContext) {
    for (auto e : m_elements) {
        e->Resize(appContext);
    }
}
