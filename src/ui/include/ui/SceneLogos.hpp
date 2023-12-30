//
// Purpur Tentakel
// 14.09.2022
//

#pragma once

#include <alias/AliasUiLib.hpp>
#include <functional>
#include <ui_lib/Scene.hpp>
#include <ui_lib/SceneType.hpp>


namespace ui {
    class LogoScene final : public uil::Scene {
    private:
        inline static double const m_sceneLength{ 5.0f };
        uil::SceneType m_nextScene{ uil::SceneType::INTRO };
        double m_time;

        void Initialize();

    public:
        LogoScene();

        void CheckAndUpdate(Vector2 const& mousePosition, app::AppContext_ty_c appContext) override;

        void Render(app::AppContext_ty_c appContext) override;

        void Resize(app::AppContext_ty_c appContext) override;
    };
} // namespace ui
