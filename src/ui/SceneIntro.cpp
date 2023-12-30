//
// Purpur Tentakel
// 12.09.2022
//

#include "SceneIntro.hpp"
#include <app/AppContext.hpp>
#include <helper/HInput.hpp>
#include <helper/HRandom.hpp>
#include <ui_lib/ButtonClassic.hpp>
#include <ui_lib/SceneType.hpp>
#include <ui_lib/Text.hpp>
#include <ui_lib/Title.hpp>


namespace ui {
    void Intro::Initialize() {
        app::AppContext_ty appContext = app::AppContext::GetInstance();
        m_title = std::make_shared<uil::Title>(
                GetElementPosition(0.5f, 0.1f),
                GetElementSize(0.9f, 0.3f),
                uil::Alignment::TOP_MID,
                true
        );
        m_elements.push_back(m_title);

        m_btn = std::make_shared<uil::ClassicButton>(
                1,
                GetElementPosition(0.5f, 1.2f),
                GetElementSize(0.3f, 0.2f),
                uil::Alignment::MID_MID,
                appContext.languageManager.Text("scene_intro_start_btn"),
                app::SoundType::ACCEPTED
        );
        m_btn->SetEnabled(false);
        m_elements.push_back(m_btn);

        auto skipText = std::make_shared<uil::Text>(
                GetElementPosition(0.99f, 0.97f),
                GetElementSize(0.2f, 0.03f),
                uil::Alignment::BOTTOM_RIGHT,
                uil::Alignment::BOTTOM_RIGHT,
                0.03f,
                appContext.languageManager.Text("scene_intro_skip", "[ESC]")
        );
        // skipText->RenderRectangle(true);
        m_elements.push_back(skipText);


        m_btn->SetOnClick([]() {
            app::AppContext::GetInstance().eventManager.InvokeEvent(eve::SwitchSceneEvent(uil::SceneType::MAIN_MENU));
        });
    }

    Intro::Intro()
        : Scene{
              { 0.0f, 0.0f },
              { 1.0f, 1.0f },
              uil::Alignment::DEFAULT
    } {
        Initialize();
    }

    void Intro::CheckAndUpdate(Vector2 const& mousePosition, app::AppContext_ty_c appContext) {
        m_title->CheckAndUpdate(mousePosition, appContext);

        bool const skipBtn{ hlp::IsBackInputPressed() and m_title->HasFinishedTitle() and m_btn->IsMoving() };
        if (skipBtn) {
            m_btn->StopMoving();
            m_btn->SetPosition({ 0.5f, 0.5f });
            return;
        }

        if (m_title->IsTitleFinished()) {
            m_btn->SetEnabled(true);
            m_btn->MoveToPositionAsymptotic(Vector2(0.5f, 0.5f), 1.0f);
        }

        m_btn->CheckAndUpdate(mousePosition, appContext);
    }

    void Intro::Render(app::AppContext_ty_c appContext) {
        for (auto& e : m_elements) {
            e->Render(appContext);
        }
    }

    void Intro::Resize(app::AppContext_ty_c appContext) {
        for (auto& e : m_elements) {
            e->Resize(appContext);
        }
    }

    void Intro::SetActive(bool const active, app::AppContext_ty_c appContext) {
        Scene::SetActive(active, appContext);
        eve::SelectFocusElementEvent const event{ m_btn.get() };
        appContext.eventManager.InvokeEvent(event);
    }
} // namespace ui
