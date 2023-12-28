//
// Purpur Tentakel
// 12.09.2022
//

#pragma once
#include <app/AppContext.hpp>
#include <array>
#include <functional>
#include <memory>
#include <string>
#include <ui_lib/Scene.hpp>
#include <ui_lib/SceneType.hpp>
#include <vector>

class Intro final : public Scene {
private:
    Title_ty m_title{ nullptr };
    ClassicButton_ty m_btn{ nullptr };

    void Initialize();

public:
    Intro();

    void CheckAndUpdate(Vector2 const& mousePosition, AppContext_ty_c appContext) override;

    void Render(AppContext_ty_c appContext) override;

    void Resize(AppContext_ty_c appContext) override;

    void SetActive(bool active, AppContext_ty_c appContext) override;
};
