//
// Purpur Tentakel
// 24.08.2022
//

#include "ManagerUI.hpp"
#include "HSceneTestScene.hpp"
#include <alias/AliasConstants.hpp>
#include <helper/HInput.hpp>
#include <helper/HPrint.hpp>

namespace ui {
    uil::Focus& UIManager::GetFocus() {
        return m_focus;
    }

    void UIManager::SetFullScreen() {
        m_isNextFullScreen = !m_isNextFullScreen;
    }

    void UIManager::CheckAndSetToggleFullScreen() {
        cst::Window_ty window{ m_appContext.constants.window };

        if (window.isFullScreen == m_isNextFullScreen) {
            return;
        }
        window.isFullScreen = m_isNextFullScreen;

        if (window.isFullScreen) {
            SetNativeWindowSize();
            ::ToggleFullscreen();
            SetWindowSize(true);
        } else {
            SetNativeWindowSize();
            ::ToggleFullscreen();
            SetWindowSize(true);
            SetWindowPosition();
        }
        m_sceneManager.Resize(m_appContext);
    }

    void UIManager::CheckAndSetNewResolution() {
        cst::Window_ty window{ m_appContext.constants.window };
        if (m_nextResolution == window.currentResolutionEnum) {
            return;
        }

        bool const validResolution{ window.IsPossibleResolution(m_nextResolution) };
        if (!validResolution) {
            Print(hlp::PrintType::ERROR,
                  "invalid resolution for this screen -> {}",
                  m_appContext.constants.window.GetStringFromResolution(m_nextResolution));
            return;
        }

        SetWindowSize();
        SetWindowPosition();

        if (m_sceneManager.IsValidCurrentScene()) {
            m_sceneManager.Resize(m_appContext);
        }
    }

    void UIManager::CheckAndUpdate() {
        if (hlp::IsQuitInput()) {
            eve::CloseWindowEvent event;
            m_appContext.eventManager.InvokeEvent(event);
        }

        if (hlp::IsToggleFullscreenInput()) {
            SetFullScreen();
        }

        Vector2 const mousePosition{ GetMousePosition() };
        m_focus.CheckAndUpdate();
        m_sceneManager.CheckAndUpdate(mousePosition, m_appContext);
    }

    void UIManager::Render() {
        BeginDrawing();
        ClearBackground(BLACK);
        m_sceneManager.Render(m_appContext);
        m_focus.Render();
        m_hover.Render();

#ifdef _DEBUG
        utl::usize const fps{ static_cast<utl::usize>(GetFPS()) };
        cst::Window_ty_c window{ app::AppContext::GetInstance().constants.window };
        DrawTextEx(*(m_appContext.assetManager.GetFont()),
                   ("FPS: " + std::to_string(fps)).c_str(),
                   Vector2(window.currentResolutionVec.x * 0.92f, window.currentResolutionVec.y * 0.01f),
                   window.currentResolutionVec.y * 0.03f,
                   0.0f,
                   WHITE);
#endif // _DEBUG

        EndDrawing();
    }

    void UIManager::SetNativeWindowSize() {
        cst::Window_ty_c window{ m_appContext.constants.window };
        utl::vec2pos_ty_c values{ window.nativeResolutionVec };

        ::SetWindowSize(static_cast<int>(values.x), static_cast<int>(values.y));
    }

    void UIManager::SetWindowSize(bool const force) {
        cst::Window_ty window{ m_appContext.constants.window };
        if (window.currentResolutionEnum == m_nextResolution and not force) {
            return;
        }
        window.currentResolutionEnum = m_nextResolution;

        utl::vec2pos_ty_c values = window.GetIntFromResolution(m_nextResolution);

        window.currentResolutionVec = { static_cast<float>(values.x), static_cast<float>(values.y) };
        ::SetWindowSize(static_cast<int>(values.x), static_cast<int>(values.y));
    }

    void UIManager::SetWindowPosition() {
        cst::Window_ty_c window{ m_appContext.constants.window };
        if (window.isFullScreen) {
            return;
        }

        auto const screen{ GetCurrentMonitor() };
        auto const screenHeight{ GetMonitorHeight(screen) };
        auto const screenWidth{ GetMonitorWidth(screen) };

        auto differenceWidth{ static_cast<int>((static_cast<float>(screenWidth) - window.currentResolutionVec.x) / 2) };
        auto differenceHeight{ static_cast<int>((static_cast<float>(screenHeight) - window.currentResolutionVec.y)
                                                / 2) };

        if (differenceWidth < 0) {
            differenceWidth = 0;
        }
        if (differenceHeight < 0) {
            differenceHeight = 0;
        }

        ::SetWindowPosition(differenceWidth, differenceHeight);
    }

    void UIManager::SetTargetFPS(eve::SetTargetFPSEvent const* const event) {
        ::SetTargetFPS(static_cast<int>(event->GetFPS()));
        hlp::Print(hlp::PrintType::INFO, "fps set -> {}", event->GetFPS());
    }

    void UIManager::UILoop() {
        while (!WindowShouldClose()) {
            m_appContext.constants.global.acceptInputTriggered = false;
            CheckAndSetToggleFullScreen();
            CheckAndSetNewResolution();
            CheckAndUpdate();
            Render();
            if (m_closeWindow) {
                break;
            }
        }
    }

    UIManager::UIManager()
        : m_appContext(app::AppContext::GetInstance()),
          m_sceneManager(),
          m_nextResolution(cst::Resolution::LAST) {

        SetExitKey(KeyboardKey::KEY_NULL);

        m_appContext.eventManager.AddListener(this);

        hlp::Print(hlp::PrintType::INITIALIZE, "UIManager");
    }

    UIManager::~UIManager() {
        m_appContext.eventManager.RemoveListener(this);
    }

    void UIManager::StartUI() {

        SetWindowTitle(("Tentakels Attacking " + cst::Global::gameVersion).c_str());
        cst::Window_ty window{ m_appContext.constants.window };
        window.nativeResolutionVec = window.GetIntFromResolution(cst::Resolution::SCREEN);

        if (m_appContext.constants.window.currentResolutionEnum == cst::Resolution::LAST) {

            m_nextResolution                           = cst::Resolution::SCREEN;
            /*
             * problem here is, that the game actually starts with window mode.
             * to trick this I set the local variable to true and the constants variable to false.
             * this cause the CheckAndSetToggleFullScreen() to toggle fullscreen.
             * kinda hacky. I know.
             * */
            m_isNextFullScreen                         = true;
            m_appContext.constants.window.isFullScreen = false;

            eve::ShowInitialSoundLevelPopUpEvent event{
                m_appContext.languageManager.Text("ui_manager_initial_sound_popup_title"),
                m_appContext.languageManager.Text("ui_manager_initial_sound_popup_text")
            };
            app::AppContext::GetInstance().eventManager.InvokeEvent(event);
        } else {
            m_nextResolution             = window.currentResolutionEnum;
            window.currentResolutionEnum = cst::Resolution::LAST;
            /*
             * problem here is, that the game actually starts with window mode.
             * to trick this I set the local variable to the constants value and the constants variable to false.
             * this cause the CheckAndSetToggleFullScreen() to toggle fullscreen if fullscreen was provided in config.
             * kinda hacky. I know.
             * */
            m_isNextFullScreen           = window.isFullScreen;
            window.isFullScreen          = false;

            if (!window.IsPossibleResolution(m_nextResolution)) {
                hlp::Print(hlp::PrintType::ERROR,
                           "invalid resolution: {} -> resolution set to: {}",
                           m_appContext.constants.window.GetStringFromResolution(m_nextResolution),
                           m_appContext.constants.window.GetStringFromResolution(cst::Resolution::SCREEN));
                m_nextResolution = cst::Resolution::SCREEN;
            }
        }

        hlp::Print(hlp::PrintType::INFO, "\"UI\" started");
    }

    void UIManager::StartUILoop() {

        eve::SwitchSceneEvent event{ uil::SceneType::LOGO };
        m_appContext.eventManager.InvokeEvent(event);

        m_sceneManager.SwitchSceneManual();

        CheckAndSetToggleFullScreen();
        CheckAndSetNewResolution();

        hlp::Print(hlp::PrintType::INFO, "\"UI Loop\" started");

        UILoop();
    }

    void UIManager::OnEvent(eve::Event const& event) {
        if ([[maybe_unused]] auto const* CloseEvent = dynamic_cast<eve::CloseWindowEvent const*>(&event)) {
            m_closeWindow = true;
            return;
        }

        if (auto const* ResolutionEvent = dynamic_cast<eve::SetNewResolutionEvent const*>(&event)) {
            m_nextResolution = ResolutionEvent->GetResolution();
        }

        if (auto const* ToggleEvent = dynamic_cast<eve::ToggleFullscreenEvent const*>(&event)) {
            m_isNextFullScreen = ToggleEvent->IsNextFullscreen();
            return;
        }

        if (auto const* FPSEvent = dynamic_cast<eve::SetTargetFPSEvent const*>(&event)) {
            SetTargetFPS(FPSEvent);
            return;
        }
    }
} // namespace ui
