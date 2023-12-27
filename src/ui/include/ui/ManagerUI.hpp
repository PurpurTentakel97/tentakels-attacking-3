//
// Purpur Tentakel
// 24.08.2022
//

#pragma once
#include "ManagerScene.hpp"
#include <AppContext.hpp>
#include <event/EventListener.hpp>
#include <logic/ManagerGame.hpp>
#include <memory>
#include <ui_lib/Focus.hpp>
#include <ui_lib/HoverRender.hpp>
#include <ui_lib/UIElement.hpp>
#include <vector>

class Scene;

class UIManager final : public EventListener {
private:
    AppContext_ty m_appContext;
    Focus m_focus;
    SceneManager m_sceneManager;
    GameManager m_gameManager;
    HoverRender m_hover;
    bool m_closeWindow{ false };
    bool m_isNextFullScreen{ false };
    Resolution m_nextResolution;

    void SetFullScreen();

    void CheckAndSetToggleFullScreen();

    void CheckAndSetNewResolution();

    void CheckAndUpdate();

    void Render();

    void SetNativeWindowSize();

    void SetWindowSize(bool force = false);

    void SetWindowPosition();

    void SetTargetFPS(SetTargetFPSEvent const* event);

    void UILoop();

public:
    UIManager();

    ~UIManager() override;

    void StartUI();

    void StartUILoop();

    void OnEvent(Event const& event) override;

    [[nodiscard]] Focus& GetFocus();
};
