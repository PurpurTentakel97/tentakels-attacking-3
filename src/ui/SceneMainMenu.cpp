//
// Purpur Tentakel
// 19.09.2022
//

#include "SceneMainMenu.hpp"
#include "HSceneGalaxyAndSlider.hpp"
#include "ManagerUI.hpp"
#include <AppContext.hpp>
#include <memory>
#include <ui_lib/ButtonClassic.hpp>
#include <ui_lib/ButtonExpanding.hpp>
#include <ui_lib/Text.hpp>
#include <ui_lib/Title.hpp>

void MainMenu::Initialize() {
    AppContext_ty_c appContext{ AppContext::GetInstance() };

    auto galaxy = std::make_shared<GalaxyScene>(
            GetElementPosition(0.95f, 0.95f),
            GetElementSize(0.7f, 0.7f),
            Alignment::BOTTOM_RIGHT,
            true,
            false
    );
    galaxy->SetActive(true, appContext);
    galaxy->SetIsScaling(false);
    galaxy->SetIsEnabled(false);
    m_elements.push_back(galaxy);

    auto title = std::make_shared<Title>(
            GetElementPosition(0.625f, 0.025f),
            GetElementSize(0.7f, 0.2f),
            Alignment::TOP_MID,
            false
    );
    m_elements.push_back(title);

    auto versionAndCopyRight = std::make_shared<Text>(
            GetElementPosition(0.99f, 0.98f),
            GetElementSize(0.1f, 0.1f),
            Alignment::BOTTOM_RIGHT,
            Alignment::BOTTOM_RIGHT,
            0.02f,
            CGlobal::gameVersion + '\n' + CGlobal::copyRight
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

    auto gameBtn = std::make_shared<ExpandingButton>(
            focusID,
            GetElementPosition(btnPosX, btnPosY),
            GetElementSize(btnSizX, btnSizY),
            Alignment::MID_RIGHT,
            ExpandingButton::RIGHT,
            0.005f,
            10.0f,
            appContext.languageManager.Text("helper_game")
    );
    m_elements.push_back(gameBtn);

    incFID();

    auto continueBtn = std::make_shared<ClassicButton>(
            focusID,
            Vector2{ 0.0f, 0.0f },
            Vector2{ 0.0f, 0.0f },
            Alignment::DEFAULT,
            appContext.languageManager.Text("scene_main_menu_continue_btn"),
            SoundType::ACCEPTED
    );
    continueBtn->SetEnabled(appContext.constants.global.isGameRunning);
    continueBtn->SetOnClick([]() {
        ResumeGameEvent const event{};
        AppContext::GetInstance().eventManager.InvokeEvent(event);
    });
    gameBtn->Add(continueBtn, appContext.constants.global.isGameRunning);

    incFID();

    auto newGameBtn = std::make_shared<ClassicButton>(
            focusID,
            Vector2{ 0.0f, 0.0f },
            Vector2{ 0.0f, 0.0f },
            Alignment::DEFAULT,
            appContext.languageManager.Text("scene_main_menu_new_game_btn"),
            SoundType::ACCEPTED
    );
    newGameBtn->SetOnClick([]() {
        AppContext::GetInstance().eventManager.InvokeEvent(SwitchSceneEvent(SceneType::NEW_GAME_PLAYER));
    });
    gameBtn->Add(newGameBtn, true);

    incFID();

    auto networkBtn = std::make_shared<ClassicButton>(
            focusID,
            Vector2{ 0.0f, 0.0f },
            Vector2{ 0.0f, 0.0f },
            Alignment::DEFAULT,
            appContext.languageManager.Text("helper_network"),
            SoundType::ACCEPTED
    );
    gameBtn->Add(networkBtn, false);
    gameBtn->Update();

    incAll();

    auto savesBtn = std::make_shared<ExpandingButton>(
            focusID,
            GetElementPosition(btnPosX, btnPosY),
            GetElementSize(btnSizX, btnSizY),
            Alignment::MID_RIGHT,
            ExpandingButton::RIGHT,
            0.005f,
            10.0f,
            appContext.languageManager.Text("helper_saves")
    );
    m_elements.push_back(savesBtn);

    incFID();

    auto saveGameBtn = std::make_shared<ClassicButton>(
            focusID,
            Vector2{ 0.0f, 0.0f },
            Vector2{ 0.0f, 0.0f },
            Alignment::DEFAULT,
            appContext.languageManager.Text("scene_main_menu_save_btn"),
            SoundType::ACCEPTED
    );
    saveGameBtn->SetOnClick([]() {
        AppContext_ty appContext_{ AppContext::GetInstance() };
        if (not appContext_.constants.global.isGameSaved) {
            appContext_.constants.global.isGameSaved = true;
            ShowMessagePopUpEvent const event{ "debug save",
                                               "set save bool to false\nwill be set later when a game was saved.",
                                               []() {} };
            appContext_.eventManager.InvokeEvent(event);
        }
    });
    savesBtn->Add(saveGameBtn, true);

    incFID();

    auto loadGameBtn = std::make_shared<ClassicButton>(
            focusID,
            Vector2{ 0.0f, 0.0f },
            Vector2{ 0.0f, 0.0f },
            Alignment::DEFAULT,
            appContext.languageManager.Text("scene_main_menu_load_btn"),
            SoundType::ACCEPTED
    );
    loadGameBtn->SetOnClick([]() {
        AppContext::GetInstance().eventManager.InvokeEvent(SwitchSceneEvent(SceneType::TEST));
    });
    bool constexpr lge{ true };
    savesBtn->Add(loadGameBtn, lge);
    savesBtn->Update();

    incAll();

    auto settingsBtn = std::make_shared<ExpandingButton>(
            focusID,
            GetElementPosition(btnPosX, btnPosY),
            GetElementSize(btnSizX, btnSizY),
            Alignment::MID_RIGHT,
            ExpandingButton::RIGHT,
            0.005f,
            10.0f,
            appContext.languageManager.Text("helper_settings")
    );
    m_elements.push_back(settingsBtn);

    incFID();

    auto gameSettingsBtn = std::make_shared<ClassicButton>(
            focusID,
            Vector2{ 0.0f, 0.0f },
            Vector2{ 0.0f, 0.0f },
            Alignment::DEFAULT,
            appContext.languageManager.Text("helper_game"),
            SoundType::CLICKED_RELEASE_STD
    );
    gameSettingsBtn->SetOnClick([]() {
        AppContext::GetInstance().eventManager.InvokeEvent(SwitchSceneEvent(SceneType::GAME_SETTINGS));
    });
    settingsBtn->Add(gameSettingsBtn, true);

    incFID();

    auto appSettingsBtn = std::make_shared<ClassicButton>(
            focusID,
            Vector2{ 0.0f, 0.0f },
            Vector2{ 0.0f, 0.0f },
            Alignment::DEFAULT,
            appContext.languageManager.Text("helper_app"),
            SoundType::CLICKED_RELEASE_STD
    );
    appSettingsBtn->SetOnClick([]() {
        SwitchSceneEvent const event{ SceneType::APP_SETTINGS };
        AppContext::GetInstance().eventManager.InvokeEvent(event);
    });
    settingsBtn->Add(appSettingsBtn, true);
    settingsBtn->Update();

    incAll();

    auto creditsBtn = std::make_shared<ClassicButton>(
            focusID,
            GetElementPosition(btnPosX, btnPosY),
            GetElementSize(btnSizX, btnSizY),
            Alignment::MID_RIGHT,
            appContext.languageManager.Text("scene_main_menu_credits_btn"),
            SoundType::CLICKED_RELEASE_STD
    );
    creditsBtn->SetOnClick([]() {
        AppContext::GetInstance().eventManager.InvokeEvent(SwitchSceneEvent(SceneType::CREDITS));
    });
    m_elements.push_back(creditsBtn);

    incAll();

    auto quitBtn = std::make_shared<ClassicButton>(
            focusID,
            GetElementPosition(btnPosX, btnPosY),
            GetElementSize(btnSizX, btnSizY),
            Alignment::MID_RIGHT,
            appContext.languageManager.Text("scene_main_menu_quit_btn"),
            SoundType::ACCEPTED
    );
    quitBtn->SetOnClick([]() { AppContext::GetInstance().eventManager.InvokeEvent(QuitGameEvent{}); });
    m_elements.push_back(quitBtn);
}

MainMenu::MainMenu()
    : Scene{
          { 0.0f, 0.0f },
          { 1.0f, 1.0f },
          Alignment::DEFAULT
} {

    Initialize();
}
