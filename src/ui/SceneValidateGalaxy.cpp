//
// Purpur Tentakel
// 20.11.2022
//

#include "SceneValidateGalaxy.hpp"
#include "HSceneGalaxyAndSlider.hpp"
#include <app/AppContext.hpp>
#include <event/EventGeneral.hpp>
#include <ui_lib/ButtonClassic.hpp>
#include <ui_lib/SceneType.hpp>
#include <ui_lib/Text.hpp>


namespace ui {
    void ValidateGalaxyScene::Initialize() {

        app::AppContext_ty_c appContext{ app::AppContext::GetInstance() };

        auto text = std::make_shared<uil::Text>(
                GetElementPosition(0.5f, 0.01f),
                GetElementSize(0.4f, 0.07f),
                uil::Alignment::TOP_MID,
                uil::Alignment::TOP_MID,
                0.07f,
                appContext.languageManager.Text("scene_validate_galaxy_text", ":")
        );
        m_elements.push_back(text);

        auto backBtn = std::make_shared<uil::ClassicButton>(
                3,
                GetElementPosition(0.1f, 0.95f),
                GetElementSize(0.15f, 0.1f),
                uil::Alignment::BOTTOM_LEFT,
                appContext.languageManager.Text("scene_validate_galaxy_back_btn"),
                app::SoundType::CLICKED_RELEASE_STD
        );
        backBtn->SetOnClick([]() {
            app::AppContext::GetInstance().eventManager.InvokeEvent(
                    eve::SwitchSceneEvent(uil::SceneType::NEW_GAME_PARAMETER)
            );
        });
        m_elements.push_back(backBtn);

        auto reGenerateBtn = std::make_shared<uil::ClassicButton>(
                2,
                GetElementPosition(0.5f, 0.95f),
                GetElementSize(0.15f, 0.1f),
                uil::Alignment::BOTTOM_MID,
                appContext.languageManager.Text("scene_validate_galaxy_regenerate_btn"),
                app::SoundType::CLICKED_RELEASE_STD
        );
        reGenerateBtn->SetOnClick([this]() { this->NewGalaxy(); });
        m_elements.push_back(reGenerateBtn);

        auto nextBtn = std::make_shared<uil::ClassicButton>(
                1,
                GetElementPosition(0.9f, 0.95f),
                GetElementSize(0.15f, 0.1f),
                uil::Alignment::BOTTOM_RIGHT,
                appContext.languageManager.Text("scene_validate_galaxy_next_btn"),
                app::SoundType::ACCEPTED
        );
        nextBtn->SetOnClick([]() {
            eve::StartGameEvent const event{};
            app::AppContext::GetInstance().eventManager.InvokeEvent(event);
        });
        m_elements.push_back(nextBtn);
    }
    void ValidateGalaxyScene::InitializePlayerLegend() {
        app::AppContext_ty_c appContext = app::AppContext::GetInstance();

        auto const players = appContext.playerCollection.GetPlayerData();

        float const width{ 0.15f };
        float const height{ 0.03f };
        float const X{ 0.97f };
        float Y{ 0.5f - (height * static_cast<float>(players.size()) / 2.0f) };

        for (auto const& player : players) {
            auto text = std::make_shared<uil::Text>(
                    GetElementPosition(X, Y),
                    GetElementSize(width, height),
                    uil::Alignment::TOP_RIGHT,
                    uil::Alignment::TOP_RIGHT,
                    height,
                    player.GetName()
            );
            text->SetColor(player.color);

            m_elements.push_back(text);

            Y += height;
        }
    }

    void ValidateGalaxyScene::InitializeGalaxy() {
        app::AppContext_ty_c appContext{ app::AppContext::GetInstance() };

        m_galaxy = std::make_shared<GalaxyScene>(
                GetElementPosition(0.05f, 0.465f),
                GetElementSize(0.75f, 0.75f),
                uil::Alignment::MID_LEFT,
                false,
                false
        );
        m_galaxy->SetActive(true, appContext);
        m_elements.push_back(m_galaxy);
    }

    void ValidateGalaxyScene::NewGalaxy() {
        app::AppContext_ty_c appContext{ app::AppContext::GetInstance() };

        m_galaxy->SetActive(false, appContext);
        m_elements.erase(std::remove(m_elements.begin(), m_elements.end(), m_galaxy), m_elements.end());
        m_galaxy = nullptr;

        eve::GenerateGalaxyEvent const event;
        appContext.eventManager.InvokeEvent(event);

        InitializeGalaxy();
    }

    ValidateGalaxyScene::ValidateGalaxyScene()
        : Scene{
              { 0.0f, 0.0f },
              { 1.0f, 1.0f },
              uil::Alignment::DEFAULT
    } {

        Initialize();
        InitializeGalaxy();
        InitializePlayerLegend();
    }
} // namespace ui
