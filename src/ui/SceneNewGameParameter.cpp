//
// Purpur Tentakel
// 31.10.2022
//

#include "SceneNewGameParameter.hpp"
#include "HSceneGameEventSettings.hpp"
#include "HSceneSliderAndInputLine.hpp"
#include <app/AppContext.hpp>
#include <event/EventGeneral.hpp>
#include <event/EventsUI.hpp>
#include <ui_lib/ButtonClassic.hpp>
#include <ui_lib/CheckBox.hpp>
#include <ui_lib/Line.hpp>
#include <ui_lib/SceneType.hpp>
#include <ui_lib/Text.hpp>
#include <ui_lib/Title.hpp>


namespace ui {
    enum class SliderType {
        PLANET_COUNT,
        DIMENSION_X,
        DIMENSION_Y,
        FLEET_SPEED,
        TARGET_ROUND,
    };

    void NewGameParameterScene::Initialize() {
        app::AppContext_ty appContext{ app::AppContext::GetInstance() };

        // title
        m_elements.push_back(std::make_shared<uil::Title>(
                GetElementPosition(0.5f, 0.025f),
                GetElementSize(0.8f, 0.25f),
                uil::Alignment::TOP_MID,
                false
        ));


        // parameters
        auto parameterText = std::make_shared<uil::Text>(
                GetElementPosition(0.5f, 0.2f),
                GetElementSize(0.3f, 0.1f),
                uil::Alignment::TOP_MID,
                uil::Alignment::TOP_MID,
                0.07f,
                appContext.languageManager.Text("scene_new_game_parameter_parameter_headline")
        );
        // parameterText->RenderRectangle(true);
        m_elements.push_back(parameterText);

        // line
        m_elements.push_back(std::make_shared<uil::Line>(
                GetElementPosition(0.5f, 0.28f),
                GetElementPosition(0.5f, 0.95f),
                2.0f,
                WHITE
        ));

        // events
        m_eventSettings = std::make_shared<GameEventSettings>(
                1,
                GetElementPosition(0.25f, 0.3f),
                GetElementSize(0.25f, 0.5f),
                uil::Alignment::TOP_MID
        );
        m_eventSettings->SetActive(true, appContext);
        m_elements.push_back(m_eventSettings);

        int ID = 100;
        int constexpr IDOffset = 100;
        float constexpr posX = 0.75f;
        float posY = 0.28f;
        float constexpr offsetY = 0.1f;
        float constexpr sizeX = 0.4f;
        float constexpr sizeY = 0.05f;

        auto next = [&]() {
            ID += IDOffset;
            posY += offsetY;
        };

        // slider
        m_elements.push_back(std::make_shared<uil::Text>(
                GetElementPosition(posX, posY),
                GetElementSize(sizeX, sizeY),
                uil::Alignment::TOP_MID,
                uil::Alignment::TOP_LEFT,
                0.04f,
                appContext.languageManager.Text("scene_new_game_parameter_planet_count_subheadline", ":")
        ));

        auto planetCount = std::make_shared<SliderAndInputLine>(
                ID,
                GetElementPosition(posX, posY + 0.04f),
                GetElementSize(sizeX, sizeY),
                uil::Alignment::TOP_MID,
                static_cast<int>(appContext.constants.world.minPlanetCount),
                static_cast<int>(appContext.constants.world.maxPlanetCount),
                static_cast<int>(appContext.constants.world.currentPlanetCount)
        );
        planetCount->SetActive(true, appContext);
        planetCount->SetOnSave([](int value) { NewGameParameterScene::SetValue(value, SliderType::PLANET_COUNT); });
        m_elements.push_back(planetCount);
        m_slider.push_back(planetCount);

        next();

        m_elements.push_back(std::make_shared<uil::Text>(
                GetElementPosition(posX, posY),
                GetElementSize(sizeX, sizeY),
                uil::Alignment::TOP_MID,
                uil::Alignment::TOP_LEFT,
                0.04f,
                appContext.languageManager.Text("scene_new_game_parameter_galaxy_width_subheadline", ":")
        ));

        auto galaxyWidth = std::make_shared<SliderAndInputLine>(
                ID,
                GetElementPosition(posX, posY + 0.04f),
                GetElementSize(sizeX, sizeY),
                uil::Alignment::TOP_MID,
                static_cast<int>(appContext.constants.world.minDimensionX),
                static_cast<int>(appContext.constants.world.maxDimensionX),
                static_cast<int>(appContext.constants.world.currentDimensionX)
        );
        galaxyWidth->SetActive(true, appContext);
        galaxyWidth->SetOnSave([](int value) { NewGameParameterScene::SetValue(value, SliderType::DIMENSION_X); });
        m_elements.push_back(galaxyWidth);
        m_slider.push_back(galaxyWidth);

        next();

        m_elements.push_back(std::make_shared<uil::Text>(
                GetElementPosition(posX, posY),
                GetElementSize(sizeX, sizeY),
                uil::Alignment::TOP_MID,
                uil::Alignment::TOP_LEFT,
                0.04f,
                appContext.languageManager.Text("scene_new_game_parameter_galaxy_height_subheadline", ":")
        ));

        auto galaxyHeight = std::make_shared<SliderAndInputLine>(
                ID,
                GetElementPosition(posX, posY + 0.04f),
                GetElementSize(sizeX, sizeY),
                uil::Alignment::TOP_MID,
                static_cast<int>(appContext.constants.world.minDimensionY),
                static_cast<int>(appContext.constants.world.maxDimensionY),
                static_cast<int>(appContext.constants.world.currentDimensionY)
        );
        galaxyHeight->SetActive(true, appContext);
        galaxyHeight->SetOnSave([](int value) { NewGameParameterScene::SetValue(value, SliderType::DIMENSION_Y); });
        m_elements.push_back(galaxyHeight);
        m_slider.push_back(galaxyHeight);

        next();

        m_elements.push_back(std::make_shared<uil::Text>(
                GetElementPosition(posX, posY),
                GetElementSize(sizeX, sizeY),
                uil::Alignment::TOP_MID,
                uil::Alignment::TOP_LEFT,
                0.04f,
                appContext.languageManager.Text("scene_new_game_parameter_fleet_speed_subheadline", ":")
        ));

        auto fleetSpeed = std::make_shared<SliderAndInputLine>(
                ID,
                GetElementPosition(posX, posY + 0.04f),
                GetElementSize(sizeX, sizeY),
                uil::Alignment::TOP_MID,
                static_cast<int>(appContext.constants.fleet.minFleetSpeed),
                static_cast<int>(appContext.constants.fleet.maxFleetSpeed),
                static_cast<int>(appContext.constants.fleet.currentFleetSpeed)
        );
        fleetSpeed->SetActive(true, appContext);
        fleetSpeed->SetOnSave([](int value) { NewGameParameterScene::SetValue(value, SliderType::FLEET_SPEED); });
        m_elements.push_back(fleetSpeed);
        m_slider.push_back(fleetSpeed);

        next();

        m_elements.push_back(std::make_shared<uil::Text>(
                GetElementPosition(posX, posY),
                GetElementSize(sizeX, sizeY),
                uil::Alignment::TOP_MID,
                uil::Alignment::TOP_LEFT,
                0.04f,
                appContext.languageManager.Text("scene_new_game_parameter_last_round_subheadline", ":")
        ));

        auto lastRound = std::make_shared<SliderAndInputLine>(
                ID,
                GetElementPosition(posX, posY + 0.04f),
                GetElementSize(sizeX, sizeY),
                uil::Alignment::TOP_MID,
                static_cast<int>(appContext.constants.global.minRounds),
                static_cast<int>(appContext.constants.global.maxRounds),
                static_cast<int>(appContext.constants.global.currentTargetRound)
        );
        lastRound->SetActive(true, appContext);
        lastRound->SetOnSave([](int value) { NewGameParameterScene::SetValue(value, SliderType::TARGET_ROUND); });
        m_elements.push_back(lastRound);
        m_slider.push_back(lastRound);

        // btn
        auto randomBtn = std::make_shared<uil::ClassicButton>(
                1002,
                GetElementPosition(0.625f, 0.95f),
                GetElementSize(0.15f, 0.1f),
                uil::Alignment::BOTTOM_MID,
                appContext.languageManager.Text("scene_new_game_parameter_random_btn"),
                app::SoundType::CLICKED_RELEASE_STD
        );
        randomBtn->SetOnClick([this]() { this->SetRandom(); });
        m_elements.push_back(randomBtn);

        auto backBtn = std::make_shared<uil::ClassicButton>(
                1001,
                GetElementPosition(0.25f, 0.95f),
                GetElementSize(0.15f, 0.1f),
                uil::Alignment::BOTTOM_MID,
                appContext.languageManager.Text("scene_new_game_parameter_back_btn"),
                app::SoundType::CLICKED_RELEASE_STD
        );
        backBtn->SetOnClick([]() {
            app::AppContext::GetInstance().eventManager.InvokeEvent(
                    eve::SwitchSceneEvent(uil::SceneType::NEW_GAME_PLAYER)
            );
        });
        m_elements.push_back(backBtn);

        auto nextBtn = std::make_shared<uil::ClassicButton>(
                1000,
                GetElementPosition(0.85f, 0.95f),
                GetElementSize(0.15f, 0.1f),
                uil::Alignment::BOTTOM_MID,
                appContext.languageManager.Text("scene_new_game_parameter_next_btn"),
                app::SoundType::ACCEPTED
        );
        nextBtn->SetOnClick([]() {
            auto event = eve::GenerateGalaxyEvent();
            app::AppContext::GetInstance().eventManager.InvokeEvent(event);
        });
        m_elements.push_back(nextBtn);
    }

    void NewGameParameterScene::SetValue(int const value, SliderType const type) {
        switch (type) {
            case SliderType::PLANET_COUNT:
                app::AppContext::GetInstance().constants.world.currentPlanetCount = static_cast<size_t>(value);
                return;
            case SliderType::DIMENSION_X:
                app::AppContext::GetInstance().constants.world.currentDimensionX = value;
                return;
            case SliderType::DIMENSION_Y:
                app::AppContext::GetInstance().constants.world.currentDimensionY = value;
                return;
            case SliderType::FLEET_SPEED:
                app::AppContext::GetInstance().constants.fleet.currentFleetSpeed = value;
                return;
            case SliderType::TARGET_ROUND:
                app::AppContext::GetInstance().constants.global.currentTargetRound = static_cast<size_t>(value);
                return;
        }
    }

    void NewGameParameterScene::SetRandom() const {
        m_eventSettings->SetRandom();
        for (auto& s : m_slider) {
            s->RandomValue();
        }
    }

    void NewGameParameterScene::NextScene() {
        eve::SwitchSceneEvent event{ uil::SceneType::VALIDATE_GALAXY };
        app::AppContext::GetInstance().eventManager.InvokeEvent(event);
    }

    NewGameParameterScene::NewGameParameterScene()
        : Scene{
              { 0.0f, 0.0f },
              { 1.0f, 1.0f },
              uil::Alignment::DEFAULT
    } {
        Initialize();
        app::AppContext::GetInstance().eventManager.AddListener(this);
    }

    NewGameParameterScene::~NewGameParameterScene() {
        app::AppContext::GetInstance().eventManager.RemoveListener(this);
    }

    void NewGameParameterScene::OnEvent(eve::Event const& event) {

        if ([[maybe_unused]] auto const* GalaxyEvent = dynamic_cast<eve::GalaxyGeneratedUIEvent const*>(&event)) {
            NextScene();
            return;
        }
    }
} // namespace ui
