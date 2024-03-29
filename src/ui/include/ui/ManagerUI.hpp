//
// Purpur Tentakel
// 24.08.2022
//

#pragma once

#include "ManagerScene.hpp"
#include <alias/AliasUiLib.hpp>
#include <app/AppContext.hpp>
#include <event/EventListener.hpp>
#include <memory>
#include <ui_lib/Focus.hpp>
#include <ui_lib/HoverRender.hpp>
#include <ui_lib/UIElement.hpp>
#include <vector>


namespace ui {
    class UIManager final : public eve::EventListener {
    private:
        app::AppContext_ty m_appContext;
        uil::Focus m_focus;
        SceneManager m_sceneManager;
        uil::HoverRender m_hover;
        bool m_closeWindow{ false };
        bool m_isNextFullScreen{ false };
        cst::Resolution m_nextResolution;

        void SetFullScreen();

        void CheckAndSetToggleFullScreen();

        void CheckAndSetNewResolution();

        void CheckAndUpdate();

        void Render();

        void SetNativeWindowSize();

        void SetWindowSize(bool force = false);

        void SetWindowPosition();

        static void SetTargetFPS(eve::SetTargetFPSEvent const* event);

        void UILoop();

    public:
        UIManager();

        ~UIManager() override;

        void StartUI();

        void StartUILoop();

        void OnEvent(eve::Event const& event) override;

        [[nodiscard]] uil::Focus& GetFocus();
    };
} // namespace ui
