//
// Purpur Tentakel
// 04.11.2022
//

#include "SceneCredits.hpp"
#include "HSceneCreditTable.hpp"
#include <AppContext.hpp>
#include <ui_lib/ButtonClassic.hpp>
#include <ui_lib/Line.hpp>
#include <ui_lib/Picture.hpp>
#include <ui_lib/SceneType.hpp>
#include <ui_lib/Text.hpp>
#include <ui_lib/Title.hpp>

void CreditsScene::Initialize() {
    AppContext_ty appContext{ AppContext::GetInstance() };

    // not moving btn
    m_speedBTN = std::make_shared<ClassicButton>(
            1,
            GetElementPosition(0.95f, 0.95f),
            GetElementSize(0.15f, 0.1f),
            Alignment::BOTTOM_RIGHT,
            appContext.languageManager.Text("scene_credits_speed_toggle_btn", m_speedLevel, m_maxSpeedLevel),
            SoundType::CLICKED_RELEASE_STD
    );
    m_speedBTN->SetOnClick([this]() { this->ToggleSpeedLevel(); });
    m_speedBTN->SetEnabled(false);
    m_elements.push_back(m_speedBTN);

    auto backBTN = std::make_shared<ClassicButton>(
            2,
            GetElementPosition(0.05f, 0.95f),
            GetElementSize(0.15f, 0.1f),
            Alignment::BOTTOM_LEFT,
            appContext.languageManager.Text("scene_credits_back_btn"),
            SoundType::CLICKED_RELEASE_STD
    );
    backBTN->SetOnClick([]() {
        auto event = SwitchSceneEvent(SceneType::MAIN_MENU);
        AppContext::GetInstance().eventManager.InvokeEvent(event);
    });
    m_elements.push_back(backBTN);

    // credits
    auto creditsText = std::make_shared<Text>(
            GetElementPosition(0.5f, 0.15f),
            GetElementSize(0.5f, 0.15f),
            Alignment::MID_MID,
            Alignment::MID_MID,
            0.15f,
            appContext.languageManager.Text("scene_credits_credits_title")
    );
    // creditsText->RenderRectangle(true);
    AddMovingElement(creditsText);

    auto creditsLine =
            std::make_shared<Line>(GetElementPosition(0.35f, 0.21f), GetElementPosition(0.65f, 0.21f), 3.0f, WHITE);
    AddMovingElement(creditsLine);


    // title
    m_title = std::make_shared<Title>(
            GetElementPosition(0.5f, 0.5f),
            GetElementSize(0.9f, 0.4f),
            Alignment::MID_MID,
            true
    );
    AddMovingElement(m_title);

    m_titleLine = std::make_shared<Line>(GetElementPosition(0.05f, 0.5f), GetElementPosition(0.95f, 0.5f), 5.0f, WHITE);
    // Added to Element when moving is true

    float Y{ 1.1f };
    float height{ 0.5f };

    auto setHeight = [&Y, &height](float newHeight, float spacing) {
        Y += height + spacing;
        height = newHeight;
    };

    // logo
    auto logo = std::make_shared<Picture>(
            GetElementPosition(0.5f, Y),
            GetElementSize(0.5f, height),
            Alignment::TOP_MID,
            AssetType::LOGO
    );
    AddMovingElement(logo);

    setHeight(0.1f, 0.02f);
    auto logoText = std::make_shared<Text>(
            GetElementPosition(0.5f, Y),
            GetElementSize(1.0f, height),
            Alignment::TOP_MID,
            Alignment::TOP_MID,
            0.08f,
            appContext.languageManager.Text("scene_credits_subtitle", "Purpur Tentakel")
    );
    // logoText->RenderRectangle(true);
    AddMovingElement(logoText);

    // credits table
    setHeight(0.5f, 0.5f);
    auto libTable = std::make_shared<CreditTableScene>(
            GetElementPosition(0.5f, Y),
            GetElementSize(0.5f, height),
            Alignment::TOP_MID,
            appContext.languageManager.Text("scene_credits_libraries_headline"),
            libVec,
            true
    );
    libTable->SetActive(true, appContext);
    AddMovingElement(libTable);

    setHeight(0.5f, 0.3f);
    auto inspirationTable = std::make_shared<CreditTableScene>(
            GetElementPosition(0.5f, Y),
            GetElementSize(0.5f, height),
            Alignment::TOP_MID,
            appContext.languageManager.Text("scene_credits_inspiration_headline"),
            inspirationVec
    );
    inspirationTable->SetActive(true, appContext);
    AddMovingElement(inspirationTable);

    setHeight(0.5f, 0.3f);
    auto testersTable = std::make_shared<CreditTableScene>(
            GetElementPosition(0.5f, Y),
            GetElementSize(0.5f, height),
            Alignment::TOP_MID,
            appContext.languageManager.Text("scene_credits_testers_headline"),
            testerVec
    );
    testersTable->SetActive(true, appContext);
    AddMovingElement(testersTable);

    setHeight(0.5f, 0.3f);
    auto spatialThanksTable = std::make_shared<CreditTableScene>(
            GetElementPosition(0.5f, Y),
            GetElementSize(0.5f, height),
            Alignment::TOP_MID,
            appContext.languageManager.Text("scene_credits_special_thanks_headline"),
            specialThanksVec
    );
    spatialThanksTable->SetActive(true, appContext);
    AddMovingElement(spatialThanksTable);

    setHeight(0.5f, 0.3f);
    auto contactTable = std::make_shared<CreditTableScene>(
            GetElementPosition(0.5f, Y),
            GetElementSize(0.5f, height),
            Alignment::TOP_MID,
            appContext.languageManager.Text("scene_credits_contact_headline"),
            contactVec,
            true
    );
    contactTable->SetActive(true, appContext);
    AddMovingElement(contactTable);


    // finish btn
    setHeight(0.1f, 0.0f);
    m_endBTN = std::make_shared<ClassicButton>(
            3,
            GetElementPosition(0.5f, Y),
            GetElementSize(0.15f, height),
            Alignment::TOP_MID,
            appContext.languageManager.Text("scene_credits_end_btn"),
            SoundType::ACCEPTED
    );
    m_endBTN->SetOnClick([]() {
        auto event = SwitchSceneEvent(SceneType::MAIN_MENU);
        AppContext::GetInstance().eventManager.InvokeEvent(event);
    });
    AddMovingElement(m_endBTN);
}

void CreditsScene::AddMovingElement(std::shared_ptr<UIElement> const& element) {
    m_elements.push_back(element);
    m_movingElements.push_back(element);
}

void CreditsScene::ToggleSpeedLevel() {

    if (!m_title->HasFinishedTitle()) {
        return;
    }

    ++m_speedLevel;

    if (m_speedLevel > m_maxSpeedLevel) {
        m_speedLevel = 1;
    }

    m_speedBTN->SetText(AppContext::GetInstance()
                                .languageManager.Text("scene_credits_speed_toggle_btn", m_speedLevel, m_maxSpeedLevel));

    for (auto const& e : m_movingElements) {
        e->MoveBySpeed(m_speed * static_cast<float>(m_speedLevel), 0.0f);
    }
}

void CreditsScene::CheckCreditsFinished() {
    Resolution_ty_c resolution{ AppContext::GetInstance().GetResolution() };
    float const shouldY{ (resolution.y * 0.75f) - (m_endBTN->GetCollider().height / 2) };
    float const btnY{ m_endBTN->GetCollider().y };
    if (btnY <= shouldY) {
        for (auto& e : m_movingElements) {
            e->StopMoving();
        }
    }
}

CreditsScene::CreditsScene()
    : Scene{
          { 0.0f, 0.0f },
          { 1.0f, 1.0f },
          Alignment::DEFAULT
} {
    Initialize();
}

void CreditsScene::CheckAndUpdate(Vector2 const& mousePosition, AppContext_ty_c appContext) {
    Scene::CheckAndUpdate(mousePosition, appContext);

    if (m_title->IsTitleFinished()) {
        m_speedBTN->SetEnabled(true);
        AddMovingElement(m_titleLine);
        for (auto& e : m_movingElements) {
            e->MoveBySpeed(m_speed * static_cast<float>(m_speedLevel), 0.0f);
        }
    }

    CheckCreditsFinished();


    // for debugging
    /*if (IsKeyPressed(KEY_ESCAPE)) {
		m_moving = !m_moving;
	}*/
}

void CreditsScene::Resize(AppContext_ty_c appContext) {
    Scene::Resize(appContext);
}
