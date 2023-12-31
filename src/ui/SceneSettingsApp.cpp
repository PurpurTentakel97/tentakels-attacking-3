//
// Purpur Tentakel
// 18.07.2023
//

#include "SceneSettingsApp.hpp"
#include "HSceneSliderAndInputLine.hpp"
#include <app/AppContext.hpp>
#include <ui_lib/CheckBox.hpp>
#include <ui_lib/DropDown.hpp>
#include <ui_lib/Text.hpp>


namespace ui {
    void AppSettingsScene::Initialize() {
        app::AppContext_ty_c appContext{ app::AppContext::GetInstance() };

        // headline
        auto settingsText = std::make_shared<uil::Text>(
                GetElementPosition(0.5f, 0.2f),
                GetElementSize(0.3f, 0.1f),
                uil::Alignment::TOP_MID,
                uil::Alignment::TOP_MID,
                0.07f,
                appContext.languageManager.Text("helper_app_settings")
        );
        m_elements.push_back(settingsText);

        // constants
        int id{ 1 };
        float y{ 0.3f };
        float constexpr lx{ 0.05f };
        float constexpr rx{ 0.55f };
        float constexpr width{ 0.4f };
        float constexpr heightS{ 0.025f };
        float constexpr height{ 0.05f };
        float constexpr offset{ height + 0.005f };
        float constexpr offsetS{ heightS + 0.015f };
        float constexpr rxwoS{ rx + heightS };
        // float     constexpr rxwo   { rx + height      };
        // float     constexpr lxwoS  { lx + heightS     };
        float constexpr lxwo{ lx + height };
        auto constexpr a{ uil::Alignment::MID_LEFT };

        // increase
        auto const incFIDS{ [&]() { ++id; } };
        auto const incFIDB{ [&]() { id += 100; } };
        auto const incPosS{ [&]() { y += offsetS; } };
        auto const incPosB{ [&]() { y += offset; } };


        // first
        auto volumeText = std::make_shared<uil::Text>(
                GetElementPosition(rx, y),
                GetElementSize(width, height),
                a,
                a,
                height,
                appContext.languageManager.Text("scene_settings_volume_subheadline", ":")
        );
        m_elements.push_back(volumeText);

        incPosB();

        m_toggleFullScreenCBM =
                std::make_shared<uil::CheckBox>(id, GetElementPosition(lx, y), GetElementSize(0.0f, height).y, a, 1);
        m_toggleFullScreenCBM->SetChecked(appContext.constants.window.isFullScreen);
        m_toggleFullScreenCBM->SetOnCheck([](unsigned int, bool isChecked) {
            eve::ToggleFullscreenEvent const event{ isChecked };
            app::AppContext::GetInstance().eventManager.InvokeEvent(event);
        });
        m_elements.push_back(m_toggleFullScreenCBM);

        incFIDS();

        auto fullScreenText = std::make_shared<uil::Text>(
                GetElementPosition(lxwo, y),
                GetElementSize(width, height),
                a,
                a,
                height,
                appContext.languageManager.Text("scene_app_settings_fullscreen")
        );
        m_elements.push_back(fullScreenText);

        // second
        m_volume = std::make_shared<SliderAndInputLine>(
                id,
                GetElementPosition(rx, y),
                GetElementSize(width, height),
                a,
                0,
                100,
                static_cast<int>(appContext.constants.sound.masterVolume)
        );
        m_volume->SetActive(true, appContext);
        m_volume->SetEnabled(!appContext.constants.sound.muteVolume);
        m_volume->SetOnSave([](int value) {
            eve::SetMasterVolumeEvent const event{ static_cast<float>(value) };
            app::AppContext::GetInstance().eventManager.InvokeEvent(event);
        });
        m_elements.push_back(m_volume);

        incFIDS(); // extra inc because input line uses two ids
        incFIDS();
        incPosS();

        // third
        auto muteCB =
                std::make_shared<uil::CheckBox>(id, GetElementPosition(rx, y), GetElementSize(0.0f, heightS).y, a, 1);
        muteCB->SetChecked(appContext.constants.sound.muteVolume);
        muteCB->SetOnCheck([this](unsigned int, bool isChecked) {
            eve::MuteMasterVolumeEvent const event{ isChecked };
            app::AppContext::GetInstance().eventManager.InvokeEvent(event);
            this->m_volume->SetEnabled(!isChecked);
        });
        m_elements.push_back(muteCB);

        incFIDS();

        auto muteText = std::make_shared<uil::Text>(
                GetElementPosition(rxwoS, y),
                GetElementSize(width, heightS),
                a,
                a,
                heightS,
                appContext.languageManager.Text("scene_settings_mute")
        );
        m_elements.push_back(muteText);

        incPosB();

        // fourth
        auto resolutionText = std::make_shared<uil::Text>(
                GetElementPosition(lx, y),
                GetElementSize(width, height),
                a,
                a,
                height,
                appContext.languageManager.Text("scene_settings_resolution_subheadline", ":")
        );
        m_elements.push_back(resolutionText);

        auto languageText = std::make_shared<uil::Text>(
                GetElementPosition(rx, y),
                GetElementSize(width, height),
                a,
                a,
                height,
                appContext.languageManager.Text("scene_settings_language_subheadline", ":")
        );
        m_elements.push_back(languageText);

        incPosS();

        // fifth
        auto resolutionHintText = std::make_shared<uil::Text>(
                GetElementPosition(lx, y),
                GetElementSize(width, heightS),
                a,
                a,
                heightS,
                appContext.languageManager.Text("scene_settings_resolution_subtext")
        );
        m_elements.push_back(resolutionHintText);

        incPosS();

        // sixth
        m_resolutionDropDown = std::make_shared<uil::DropDown>(
                GetElementPosition(lx, y),
                GetElementSize(width, height),
                a,
                0.25f,
                id,
                id + 1,
                GetStringsFromResolutionEntries()
        );
        m_resolutionDropDown->SetCurrentElementByID(
                static_cast<unsigned int>(GetIndexFromResolution(appContext.constants.window.currentResolutionEnum) + 1)
        );
        m_resolutionDropDown->SetOnSave([this](unsigned int ID) {
            eve::SetNewResolutionEvent const event{ this->m_rawResolutionEntries[ID - 1].first };
            app::AppContext::GetInstance().eventManager.InvokeEvent(event);
        });
        m_elements.push_back(m_resolutionDropDown);

        incFIDB();

        m_languageDropDown = std::make_shared<uil::DropDown>(
                GetElementPosition(rx, y),
                GetElementSize(width, height),
                a,
                0.25f,
                id,
                id + 1,
                app::LanguageManager::GetAvailableLanguages()
        );
        m_languageDropDown->SetCurrentElementByString(appContext.constants.global.currentLanguageName);
        m_languageDropDown->SetOnSave([](unsigned int ID) {
            auto const language{ app::LanguageManager::GetAvailableLanguages().at(ID - 1) };
            auto const event{ eve::ChangeLanguageEvent(language) };
            app::AppContext::GetInstance().eventManager.InvokeEvent(event);
        });
        m_elements.push_back(m_languageDropDown);
    }

    std::vector<std::string> AppSettingsScene::GetStringsFromResolutionEntries() const {
        std::vector<std::string> toReturn;

        for (auto const& e : m_rawResolutionEntries) {
            toReturn.push_back(e.second);
        }

        return toReturn;
    }

    utl::usize AppSettingsScene::GetIndexFromResolution(cst::Resolution const resolution) const {
        for (utl::usize i = 0; i < m_rawResolutionEntries.size(); ++i) {
            if (m_rawResolutionEntries[i].first == resolution) {
                return i;
            }
        }
        throw std::runtime_error("resolution not existing");
    }

    AppSettingsScene::AppSettingsScene() : SettingsScene{} {

        app::AppContext_ty appContext{ app::AppContext::GetInstance() };
        m_rawResolutionEntries = appContext.constants.window.GetAllResolutionsAsString();
        appContext.eventManager.AddListener(this);

        Initialize();
    }
    AppSettingsScene::~AppSettingsScene() {
        app::AppContext::GetInstance().eventManager.RemoveListener(this);
    }

    void AppSettingsScene::CheckAndUpdate(Vector2 const& mousePosition, app::AppContext_ty_c appContext) {
        SettingsScene::CheckAndUpdate(mousePosition, appContext);
        m_toggleFullScreenCBM->SetChecked(appContext.constants.window.isFullScreen);
    }

    void AppSettingsScene::Render(app::AppContext_ty_c appContext) {
        SettingsScene::Render(appContext);
    }

    void AppSettingsScene::Resize(app::AppContext_ty_c appContext) {
        SettingsScene::Resize(appContext);
    }

    void AppSettingsScene::OnEvent(eve::Event const& event) {
        if (auto const* LanguageEvent = dynamic_cast<eve::UpdateLanguageInUIEvent const*>(&event)) {
            m_languageDropDown->SetCurrentElementByString(LanguageEvent->GetLanguage());
            app::AppContext_ty_c appContext{ app::AppContext::GetInstance() };
            eve::ShowMessagePopUpEvent const mEvent{
                appContext.languageManager.Text("helper_new_language"),
                appContext.languageManager.Text("ui_popup_new_language_text", LanguageEvent->GetLanguage()),
                []() {}
            };
            appContext.eventManager.InvokeEvent(mEvent);
            return;
        }
    }
} // namespace ui
