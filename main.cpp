//
// Purpur Tentakel
// 08.08.2022
// C++ 23
//

// original Random by coder2k (https://gist.github.com/mgerhold/353e39da27ae9b22c614bc264c8a3d18)

#include "AppContext.hpp"
#include "helper/HErrorLog.hpp"
#include "helper/HLogicAlias.hpp"
#include "helper/HPrint.hpp"
#include "ui/UIManager.h"

int main() {
    SetConfigFlags(FLAG_VSYNC_HINT);
    InitWindow(100, 100, "");
    AppContext_ty appContext{ AppContext::GetInstance() };
#ifdef _DEBUG
    Print(PrintType::BUILD, "Debug");
#else
    Print(PrintType::BUILD, "Release");
#endif // _DEBUG

    Print(PrintType::BUILD, appContext.constants.global.gameVersion);

    UIManager uiManager;

    appContext.LoadConfig();
    appContext.LoadLanguages();

    uiManager.StartUI();

    appContext.ValidateConfig();

    uiManager.StartUILoop();

    appContext.SaveConfig();

    CloseErrorStream();

    return 0;
}