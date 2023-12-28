//
// Purpur Tentakel
// 24.08.2022
//

#include "ManagerUI.hpp"
#include "HSceneTestScene.hpp"
#include <helper/HInput.hpp>
#include <helper/HPrint.hpp>

Focus& UIManager::GetFocus() {
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
        Print(PrintType::ERROR,
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
    if (IsQuitInput()) {
        eve::CloseWindowEvent event;
        m_appContext.eventManager.InvokeEvent(event);
    }

    if (IsToggleFullscreenInput()) {
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
    int const fps{ GetFPS() };
    cst::Window_ty_c window{ AppContext::GetInstance().constants.window };
    DrawTextEx(
            *(m_appContext.assetManager.GetFont()),
            ("FPS: " + std::to_string(fps)).c_str(),
            Vector2(window.currentResolutionVec.x * 0.92f, window.currentResolutionVec.y * 0.01f),
            window.currentResolutionVec.y * 0.03f,
            0.0f,
            WHITE
    );
#endif // _DEBUG

    EndDrawing();
}

void UIManager::SetNativeWindowSize() {
    cst::Window_ty_c window{ m_appContext.constants.window };
    HVec2<int> values{ window.nativeResolutionVec };

    ::SetWindowSize(values.x, values.y);
}

void UIManager::SetWindowSize(bool const force) {
    cst::Window_ty window{ m_appContext.constants.window };
    if (window.currentResolutionEnum == m_nextResolution and not force) {
        return;
    }
    window.currentResolutionEnum = m_nextResolution;

    HVec2<int> values = window.GetIntFromResolution(m_nextResolution) ;

    window.currentResolutionVec = { static_cast<float>(values.x), static_cast<float>(values.y) };
    ::SetWindowSize(values.x, values.y);
}

void UIManager::SetWindowPosition() {
    cst::Window_ty_c window{ m_appContext.constants.window };
    if (window.isFullScreen) {
        return;
    }

    int const screen{ GetCurrentMonitor() };
    int const screenHeight{ GetMonitorHeight(screen) };
    int const screenWidth{ GetMonitorWidth(screen) };

    int differenceWidth{ (screenWidth - static_cast<int>(window.currentResolutionVec.x)) / 2 };
    int differenceHeight{ (screenHeight - static_cast<int>(window.currentResolutionVec.y)) / 2 };

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
    Print(PrintType::INFO, "fps set -> {}", event->GetFPS());
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
    CloseWindow();
}

UIManager::UIManager() : m_appContext(AppContext::GetInstance()), m_sceneManager(), m_nextResolution(Resolution::LAST) {

    SetExitKey(KeyboardKey::KEY_NULL);

    m_appContext.eventManager.AddListener(this);

    Print(PrintType::INITIALIZE, "UIManager");
}

UIManager::~UIManager() {
    m_appContext.eventManager.RemoveListener(this);
}

void UIManager::StartUI() {

    SetWindowTitle(("Tentakels Attacking " + cst::Global::gameVersion).c_str());
    cst::Window_ty window{ m_appContext.constants.window };
    window.nativeResolutionVec = window.GetIntFromResolution(Resolution::SCREEN);

    if (m_appContext.constants.window.currentResolutionEnum == Resolution::LAST) {

        m_nextResolution = Resolution::SCREEN;
        m_isNextFullScreen = true;

        eve::ShowInitialSoundLevelPopUpEvent event{
            m_appContext.languageManager.Text("ui_manager_initial_sound_popup_title"),
            m_appContext.languageManager.Text("ui_manager_initial_sound_popup_text")
        };
        AppContext::GetInstance().eventManager.InvokeEvent(event);
    } else {
        m_nextResolution = window.currentResolutionEnum;
        window.currentResolutionEnum = Resolution::LAST;
        m_isNextFullScreen = window.isFullScreen;
        window.isFullScreen = false;

        if (!window.IsPossibleResolution(m_nextResolution)) {
            Print(PrintType::ERROR,
                  "invalid resolution: {} -> resolution set to: {}",
                  m_appContext.constants.window.GetStringFromResolution(m_nextResolution),
                  m_appContext.constants.window.GetStringFromResolution(Resolution::SCREEN));
            m_nextResolution = Resolution::SCREEN;
        }
    }

    Print(PrintType::INFO, "\"UI\" started");
}

void UIManager::StartUILoop() {

    eve::SwitchSceneEvent event{ SceneType::LOGO };
    m_appContext.eventManager.InvokeEvent(event);

    m_sceneManager.SwitchSceneManual();

    CheckAndSetToggleFullScreen();
    CheckAndSetNewResolution();

    Print(PrintType::INFO, "\"UI Loop\" started");

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
