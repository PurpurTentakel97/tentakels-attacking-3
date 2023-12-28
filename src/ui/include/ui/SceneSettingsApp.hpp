//
// Purpur Tentakel
// 18.07.2023
//

#pragma once
#include "HSceneSettings.hpp"
#include <event/EventListener.hpp>

class SliderAndInputLine;

class AppSettingsScene final : public SettingsScene, public EventListener {
private:
    std::vector<std::pair<Resolution, std::string>> m_rawResolutionEntries;
    std::shared_ptr<SliderAndInputLine> m_volume;
    DropDown_ty m_languageDropDown;
    DropDown_ty m_resolutionDropDown;
    CheckBox_ty m_toggleFullScreenCBM;


    void Initialize();


    [[nodiscard]] std::vector<std::string> GetStringsFromResolutionEntries() const;

    [[nodiscard]] size_t GetIndexFromResolution(Resolution resolution) const;

public:
    AppSettingsScene();

    ~AppSettingsScene() override;

    void CheckAndUpdate(Vector2 const& mousePosition, AppContext_ty_c appContext) override;

    void Render(AppContext_ty_c appContext) override;

    void Resize(AppContext_ty_c appContext) override;

    void OnEvent(Event const& event) override;
};
