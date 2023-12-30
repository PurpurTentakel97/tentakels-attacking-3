//
// Purpur Tentakel
// 14.09.2022
//

#include "SceneLogos.hpp"
#include "ManagerUI.hpp"
#include <app/AppContext.hpp>
#include <helper/HInput.hpp>
#include <memory>
#include <ui_lib/Picture.hpp>
#include <ui_lib/Text.hpp>


namespace ui {
    void LogoScene::Initialize() {
        app::AppContext_ty_c appContext{ app::AppContext::GetInstance() };

        auto logo = std::make_shared<uil::Picture>(
                GetElementPosition(0.5f, 0.1f),
                GetElementSize(0.0f, 0.5f),
                uil::Alignment::TOP_MID,
                app::AssetType::LOGO
        );
        m_elements.push_back(logo);

        auto mainText = std::make_shared<uil::Text>(
                GetElementPosition(0.5f, 0.65f),
                GetElementSize(1.0f, 0.1f),
                uil::Alignment::TOP_MID,
                uil::Alignment::TOP_MID,
                0.07f,
                appContext.languageManager.Text("scene_logo_subtitle", "Purpur Tentakel")
        );
        //mainText->RenderRectangle(true);
        m_elements.push_back(mainText);

        auto skipText = std::make_shared<uil::Text>(
                GetElementPosition(0.99f, 0.97f),
                GetElementSize(0.2f, 0.03f),
                uil::Alignment::BOTTOM_RIGHT,
                uil::Alignment::BOTTOM_RIGHT,
                0.03f,
                appContext.languageManager.Text("scene_logo_skip", "[ESC]")
        );
        // skipText->RenderRectangle(true);
        m_elements.push_back(skipText);
    }

    LogoScene::LogoScene()
	:Scene{ {0.0f, 0.0f}, {1.0f, 1.0f}, uil::Alignment::DEFAULT },
	m_time{ GetTime() } {
        Initialize();
    }

    void LogoScene::CheckAndUpdate(Vector2 const& mousePosition, app::AppContext_ty_c appContext) {
        bool const nextScene{ hlp::IsBackInputPressed() or (m_time + m_sceneLength) < GetTime() };
        if (nextScene) {
            eve::SwitchSceneEvent event{ m_nextScene };
            appContext.eventManager.InvokeEvent(event);
        }

        for (auto const& e : m_elements) {
            e->CheckAndUpdate(mousePosition, appContext);
        }
    }

    void LogoScene::Render(app::AppContext_ty_c appContext) {
        for (auto const& e : m_elements) {
            e->Render(appContext);
        }
    }

    void LogoScene::Resize(app::AppContext_ty_c appContext) {
        for (auto const& e : m_elements) {
            e->Resize(appContext);
        }
    }
} // namespace ui
