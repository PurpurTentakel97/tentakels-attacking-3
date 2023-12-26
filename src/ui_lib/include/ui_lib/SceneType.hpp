//
// Purpur Tentakel
// 05.09.2022
//

#pragma once
#include <string>

/**
 * provides all main scene types.
 */
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

/**
 * returns a string representation of an main scene type.
 */
[[nodiscard]] std::string GetStringBySceneType(SceneType sceneType);
