//
// Purpur Tentakel
// 18.07.2023
//

#pragma once

#include "HSceneSettings.hpp"
#include <alias/AliasUi.hpp>
#include <event/EventListener.hpp>

class AppSettingsScene final : public SettingsScene, public eve::EventListener {
private:
    std::vector<std::pair<cst::Resolution, std::string>> m_rawResolutionEntries;
    std::shared_ptr<SliderAndInputLine> m_volume;
    uil::DropDown_ty m_languageDropDown;
    uil::DropDown_ty m_resolutionDropDown;
    uil::CheckBox_ty m_toggleFullScreenCBM;

    void Initialize();

    [[nodiscard]] std::vector<std::string> GetStringsFromResolutionEntries() const;

    [[nodiscard]] size_t GetIndexFromResolution(cst::Resolution resolution) const;

public:
    AppSettingsScene();

    ~AppSettingsScene() override;

    void CheckAndUpdate(Vector2 const& mousePosition, app::AppContext_ty_c appContext) override;

    void Render(app::AppContext_ty_c appContext) override;

    void Resize(app::AppContext_ty_c appContext) override;

    void OnEvent(eve::Event const& event) override;
};
