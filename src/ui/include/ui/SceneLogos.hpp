//
// Purpur Tentakel
// 14.09.2022
//

#pragma once
#include <functional>
#include <ui_lib/Scene.hpp>
#include <ui_lib/SceneType.hpp>

enum class SceneType;

class LogoScene final : public Scene {
private:
    inline static double const m_sceneLength{ 5.0f };
    SceneType m_nextScene{ SceneType::INTRO };
    double m_time;

    void Initialize();

public:
    LogoScene();

    void CheckAndUpdate(Vector2 const& mousePosition, app::AppContext_ty_c appContext) override;

    void Render(app::AppContext_ty_c appContext) override;

    void Resize(app::AppContext_ty_c appContext) override;
};
