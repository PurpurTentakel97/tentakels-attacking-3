//
// Purpur Tentakel
// 20.11.2022
//

#include "SceneValidateGalaxy.hpp"
#include "HSceneGalaxyAndSlider.hpp"
#include <AppContext.hpp>
#include <event/EventGenerel.hpp>
#include <ui_lib/ButtonClassic.hpp>
#include <ui_lib/SceneType.hpp>
#include <ui_lib/Text.hpp>

void ValidateGalaxyScene::Initialize() {

    AppContext_ty_c appContext{ AppContext::GetInstance() };

    auto text = std::make_shared<Text>(
            GetElementPosition(0.5f, 0.01f),
            GetElementSize(0.4f, 0.07f),
            Alignment::TOP_MID,
            Alignment::TOP_MID,
            0.07f,
            appContext.languageManager.Text("scene_validate_galaxy_text", ":")
    );
    m_elements.push_back(text);

    auto backBtn = std::make_shared<ClassicButton>(
            3,
            GetElementPosition(0.1f, 0.95f),
            GetElementSize(0.15f, 0.1f),
            Alignment::BOTTOM_LEFT,
            appContext.languageManager.Text("scene_validate_galaxy_back_btn"),
            SoundType::CLICKED_RELEASE_STD
    );
    backBtn->SetOnClick([]() {
        AppContext::GetInstance().eventManager.InvokeEvent(SwitchSceneEvent(SceneType::NEW_GAME_PARAMETER));
    });
    m_elements.push_back(backBtn);

    auto reGenerateBtn = std::make_shared<ClassicButton>(
            2,
            GetElementPosition(0.5f, 0.95f),
            GetElementSize(0.15f, 0.1f),
            Alignment::BOTTOM_MID,
            appContext.languageManager.Text("scene_validate_galaxy_regenerate_btn"),
            SoundType::CLICKED_RELEASE_STD
    );
    reGenerateBtn->SetOnClick([this]() { this->NewGalaxy(); });
    m_elements.push_back(reGenerateBtn);

    auto nextBtn = std::make_shared<ClassicButton>(
            1,
            GetElementPosition(0.9f, 0.95f),
            GetElementSize(0.15f, 0.1f),
            Alignment::BOTTOM_RIGHT,
            appContext.languageManager.Text("scene_validate_galaxy_next_btn"),
            SoundType::ACCEPTED
    );
    nextBtn->SetOnClick([this]() {
        StartGameEvent const event{};
        AppContext::GetInstance().eventManager.InvokeEvent(event);
    });
    m_elements.push_back(nextBtn);
}
void ValidateGalaxyScene::InitializePlayerLegend() {
    AppContext_ty_c appContext = AppContext::GetInstance();

    auto const players = appContext.playerCollection.GetPlayerData();

    float const width{ 0.15f };
    float const height{ 0.03f };
    float const X{ 0.97f };
    float Y{ 0.5f - (height * static_cast<float>(players.size()) / 2.0f) };

    for (auto const& player : players) {
        auto text = std::make_shared<Text>(
                GetElementPosition(X, Y),
                GetElementSize(width, height),
                Alignment::TOP_RIGHT,
                Alignment::TOP_RIGHT,
                height,
                player.GetName()
        );
        text->SetColor(player.color);

        m_elements.push_back(text);

        Y += height;
    }
}
void ValidateGalaxyScene::InitializeGalaxy() {
    AppContext_ty_c appContext{ AppContext::GetInstance() };

    m_galaxy = std::make_shared<GalaxyScene>(
            GetElementPosition(0.05f, 0.465f),
            GetElementSize(0.75f, 0.75f),
            Alignment::MID_LEFT,
            false,
            false
    );
    m_galaxy->SetActive(true, appContext);
    m_elements.push_back(m_galaxy);
}

void ValidateGalaxyScene::NewGalaxy() {
    AppContext_ty_c appContext{ AppContext::GetInstance() };

    m_galaxy->SetActive(false, appContext);
    m_elements.erase(std::remove(m_elements.begin(), m_elements.end(), m_galaxy), m_elements.end());
    m_galaxy = nullptr;

    GenerateGalaxyEvent const event;
    appContext.eventManager.InvokeEvent(event);

    InitializeGalaxy();
}

ValidateGalaxyScene::ValidateGalaxyScene()
    : Scene{
          { 0.0f, 0.0f },
          { 1.0f, 1.0f },
          Alignment::DEFAULT
} {

    Initialize();
    InitializeGalaxy();
    InitializePlayerLegend();
}
