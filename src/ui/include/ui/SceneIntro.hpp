//
// Purpur Tentakel
// 12.09.2022
//

#pragma once

#include <alias/AliasApp.hpp>
#include <array>
#include <functional>
#include <memory>
#include <string>
#include <ui_lib/Scene.hpp>
#include <ui_lib/SceneType.hpp>
#include <vector>

class Intro final : public uil::Scene {
private:
    uil::Title_ty m_title{ nullptr };
    uil::ClassicButton_ty m_btn{ nullptr };

    void Initialize();

public:
    Intro();

    void CheckAndUpdate(Vector2 const& mousePosition, app::AppContext_ty_c appContext) override;

    void Render(app::AppContext_ty_c appContext) override;

    void Resize(app::AppContext_ty_c appContext) override;

    void SetActive(bool active, app::AppContext_ty_c appContext) override;
};
