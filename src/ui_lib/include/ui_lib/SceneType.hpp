//
// Purpur Tentakel
// 05.09.2022
//

#pragma once
#include <string>


enum class SceneType {
    TEST,
    LOGO,
    INTRO,
    MAIN_MENU,
    NEW_GAME_PLAYER,
    NEW_GAME_PARAMETER,
    VALIDATE_GALAXY,
    MAIN,
    GAME_SETTINGS,
    APP_SETTINGS,
    CREDITS,
    UPDATE_EVALUATION,
    NONE,
};

[[nodiscard]] std::string GetStringBySceneType(SceneType sceneType);
