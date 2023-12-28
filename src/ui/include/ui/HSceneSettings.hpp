//
// Purpur Tentakel
// 01.11.2022
//

#pragma once
#include <ui_lib/Scene.hpp>


class SettingsScene : public Scene {
private:
    void Initialize();

public:
    SettingsScene();

    void CheckAndUpdate(Vector2 const& mousePosition, AppContext_ty_c appContext) override;

    void Render(AppContext_ty_c appContext) override;

    void Resize(AppContext_ty_c appContext) override;
};
