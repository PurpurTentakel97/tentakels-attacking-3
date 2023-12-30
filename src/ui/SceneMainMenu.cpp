//
// Purpur Tentakel
// 19.09.2022
//

#include "SceneMainMenu.hpp"
#include "HSceneGalaxyAndSlider.hpp"
#include "ManagerUI.hpp"
#include <app/AppContext.hpp>
#include <memory>
#include <ui_lib/ButtonClassic.hpp>
#include <ui_lib/ButtonExpanding.hpp>
#include <ui_lib/Text.hpp>
#include <ui_lib/Title.hpp>


namespace ui {
    void MainMenu::Initialize() {
        app::AppContext_ty_c appContext{ app::AppContext::GetInstance() };

        auto galaxy = std::make_shared<GalaxyScene>(
                GetElementPosition(0.95f, 0.95f),
                GetElementSize(0.7f, 0.7f),
                uil::Alignment::BOTTOM_RIGHT,
                true,
                false
        );
        galaxy->SetActive(true, appContext);
        galaxy->SetIsScaling(false);
        galaxy->SetIsEnabled(false);
        m_elements.push_back(galaxy);

        auto title = std::make_shared<uil::Title>(
                GetElementPosition(0.625f, 0.025f),
                GetElementSize(0.7f, 0.2f),
                uil::Alignment::TOP_MID,
                false
        );
        m_elements.push_back(title);

        auto versionAndCopyRight = std::make_shared<uil::Text>(
                GetElementPosition(0.99f, 0.98f),
                GetElementSize(0.1f, 0.1f),
                uil::Alignment::BOTTOM_RIGHT,
                uil::Alignment::BOTTOM_RIGHT,
                0.02f,
                cst::Global::gameVersion + '\n' + cst::Global::copyRight
        );
        m_elements.push_back(versionAndCopyRight);


        float constexpr btnPosX{ 0.23f };
        float btnPosY{ 0.25f };
        float constexpr btnSizX{ 0.2f };
        float constexpr btnSizY{ 0.1f };
        float constexpr btnOffset{ 0.13f };
        int focusID{ 1 };

        auto const incFID{ [&]() { ++focusID; } };
        auto const incAll{ [&]() {
            btnPosY += btnOffset;
            incFID();
        } };

        auto gameBtn = std::make_shared<uil::ExpandingButton>(
                focusID,
                GetElementPosition(btnPosX, btnPosY),
                GetElementSize(btnSizX, btnSizY),
                uil::Alignment::MID_RIGHT,
                uil::ExpandingButton::RIGHT,
                0.005f,
                10.0f,
                appContext.languageManager.Text("helper_game")
        );
        m_elements.push_back(gameBtn);

        incFID();

        auto continueBtn = std::make_shared<uil::ClassicButton>(
                focusID,
                Vector2{ 0.0f, 0.0f },
                Vector2{ 0.0f, 0.0f },
                uil::Alignment::DEFAULT,
                appContext.languageManager.Text("scene_main_menu_continue_btn"),
                app::SoundType::ACCEPTED
        );
        continueBtn->SetEnabled(appContext.constants.global.isGameRunning);
        continueBtn->SetOnClick([]() {
            eve::ResumeGameEvent const event{};
            app::AppContext::GetInstance().eventManager.InvokeEvent(event);
        });
        gameBtn->Add(continueBtn, appContext.constants.global.isGameRunning);

        incFID();

        auto newGameBtn = std::make_shared<uil::ClassicButton>(
                focusID,
                Vector2{ 0.0f, 0.0f },
                Vector2{ 0.0f, 0.0f },
                uil::Alignment::DEFAULT,
                appContext.languageManager.Text("scene_main_menu_new_game_btn"),
                app::SoundType::ACCEPTED
        );
        newGameBtn->SetOnClick([]() {
            app::AppContext::GetInstance().eventManager.InvokeEvent(
                    eve::SwitchSceneEvent(uil::SceneType::NEW_GAME_PLAYER)
            );
        });
        gameBtn->Add(newGameBtn, true);

        incFID();

        auto networkBtn = std::make_shared<uil::ClassicButton>(
                focusID,
                Vector2{ 0.0f, 0.0f },
                Vector2{ 0.0f, 0.0f },
                uil::Alignment::DEFAULT,
                appContext.languageManager.Text("helper_network"),
                app::SoundType::ACCEPTED
        );
        gameBtn->Add(networkBtn, false);
        gameBtn->Update();

        incAll();

        auto savesBtn = std::make_shared<uil::ExpandingButton>(
                focusID,
                GetElementPosition(btnPosX, btnPosY),
                GetElementSize(btnSizX, btnSizY),
                uil::Alignment::MID_RIGHT,
                uil::ExpandingButton::RIGHT,
                0.005f,
                10.0f,
                appContext.languageManager.Text("helper_saves")
        );
        m_elements.push_back(savesBtn);

        incFID();

        auto saveGameBtn = std::make_shared<uil::ClassicButton>(
                focusID,
                Vector2{ 0.0f, 0.0f },
                Vector2{ 0.0f, 0.0f },
                uil::Alignment::DEFAULT,
                appContext.languageManager.Text("scene_main_menu_save_btn"),
                app::SoundType::ACCEPTED
        );
        saveGameBtn->SetOnClick([]() {
            app::AppContext_ty appContext_{ app::AppContext::GetInstance() };
            if (not appContext_.constants.global.isGameSaved) {
                appContext_.constants.global.isGameSaved = true;
                eve::ShowMessagePopUpEvent const event{
                    "debug save",
                    "set save bool to false\nwill be set later when a game was saved.",
                    []() {}
                };
                appContext_.eventManager.InvokeEvent(event);
            }
        });
        savesBtn->Add(saveGameBtn, true);

        incFID();

        auto loadGameBtn = std::make_shared<uil::ClassicButton>(
                focusID,
                Vector2{ 0.0f, 0.0f },
                Vector2{ 0.0f, 0.0f },
                uil::Alignment::DEFAULT,
                appContext.languageManager.Text("scene_main_menu_load_btn"),
                app::SoundType::ACCEPTED
        );
        loadGameBtn->SetOnClick([]() {
            app::AppContext::GetInstance().eventManager.InvokeEvent(eve::SwitchSceneEvent(uil::SceneType::TEST));
        });
        bool constexpr lge{ true };
        savesBtn->Add(loadGameBtn, lge);
        savesBtn->Update();

        incAll();

        auto settingsBtn = std::make_shared<uil::ExpandingButton>(
                focusID,
                GetElementPosition(btnPosX, btnPosY),
                GetElementSize(btnSizX, btnSizY),
                uil::Alignment::MID_RIGHT,
                uil::ExpandingButton::RIGHT,
                0.005f,
                10.0f,
                appContext.languageManager.Text("helper_settings")
        );
        m_elements.push_back(settingsBtn);

        incFID();

        auto gameSettingsBtn = std::make_shared<uil::ClassicButton>(
                focusID,
                Vector2{ 0.0f, 0.0f },
                Vector2{ 0.0f, 0.0f },
                uil::Alignment::DEFAULT,
                appContext.languageManager.Text("helper_game"),
                app::SoundType::CLICKED_RELEASE_STD
        );
        gameSettingsBtn->SetOnClick([]() {
            app::AppContext::GetInstance().eventManager.InvokeEvent(eve::SwitchSceneEvent(uil::SceneType::GAME_SETTINGS)
            );
        });
        settingsBtn->Add(gameSettingsBtn, true);

        incFID();

        auto appSettingsBtn = std::make_shared<uil::ClassicButton>(
                focusID,
                Vector2{ 0.0f, 0.0f },
                Vector2{ 0.0f, 0.0f },
                uil::Alignment::DEFAULT,
                appContext.languageManager.Text("helper_app"),
                app::SoundType::CLICKED_RELEASE_STD
        );
        appSettingsBtn->SetOnClick([]() {
            eve::SwitchSceneEvent const event{ uil::SceneType::APP_SETTINGS };
            app::AppContext::GetInstance().eventManager.InvokeEvent(event);
        });
        settingsBtn->Add(appSettingsBtn, true);
        settingsBtn->Update();

        incAll();

        auto creditsBtn = std::make_shared<uil::ClassicButton>(
                focusID,
                GetElementPosition(btnPosX, btnPosY),
                GetElementSize(btnSizX, btnSizY),
                uil::Alignment::MID_RIGHT,
                appContext.languageManager.Text("scene_main_menu_credits_btn"),
                app::SoundType::CLICKED_RELEASE_STD
        );
        creditsBtn->SetOnClick([]() {
            app::AppContext::GetInstance().eventManager.InvokeEvent(eve::SwitchSceneEvent(uil::SceneType::CREDITS));
        });
        m_elements.push_back(creditsBtn);

        incAll();

        auto quitBtn = std::make_shared<uil::ClassicButton>(
                focusID,
                GetElementPosition(btnPosX, btnPosY),
                GetElementSize(btnSizX, btnSizY),
                uil::Alignment::MID_RIGHT,
                appContext.languageManager.Text("scene_main_menu_quit_btn"),
                app::SoundType::ACCEPTED
        );
        quitBtn->SetOnClick([]() { app::AppContext::GetInstance().eventManager.InvokeEvent(eve::QuitGameEvent{}); });
        m_elements.push_back(quitBtn);
    }

    MainMenu::MainMenu()
        : Scene{
              { 0.0f, 0.0f },
              { 1.0f, 1.0f },
              uil::Alignment::DEFAULT
    } {

        Initialize();
    }
} // namespace ui
