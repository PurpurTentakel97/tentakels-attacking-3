//
// Purpur Tentakel
// 08.08.2022
// C++ 23
//

// original Random by coder2k (https://gist.github.com/mgerhold/353e39da27ae9b22c614bc264c8a3d18)

#include <app/AppContext.hpp>
#include <helper/HErrorLog.hpp>
#include <helper/HPrint.hpp>
#include <logic/ManagerGame.hpp>
#include <ui/ManagerUI.hpp>
#include <constants/CFiles.hpp>

int main() {
    SetConfigFlags(FLAG_VSYNC_HINT);
    InitWindow(100, 100, "");
    app::AppContext_ty appContext{ app::AppContext::GetInstance() };
#ifdef _DEBUG
    hlp::Print(hlp::PrintType::BUILD, "Debug");
#else
    hlp::Print(hlp::PrintType::BUILD, "Release");
#endif // _DEBUG

    hlp::Print(hlp::PrintType::BUILD, appContext.constants.g_version.get_game_version());

    ui::UIManager uiManager;

    appContext.LoadConfig();
    appContext.LoadLanguages();

    uiManager.StartUI();

    appContext.ValidateConfig();

    appContext.LoadGame(cst::Files::gameSafeDir(), "test.tas");

    uiManager.StartUILoop();

    appContext.SaveGame(cst::Files::gameSafeDir(), "test.tas");

    app::AppContext::SaveConfig();

    hlp::CloseErrorStream();

    appContext.Unload();

    CloseWindow();

    return 0;
}
