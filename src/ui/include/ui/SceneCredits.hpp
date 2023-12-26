//
// Purpur Tentakel
// 04.11.2022
//

#pragma once
#include "ui_lib/Scene.hpp"

/**
 * provides the credits scene.
 */
class CreditsScene final : public Scene {
private:
	Title_ty m_title; ///< contains the title
	Line_ty m_titleLine; ///< contains the line below title
	ClassicButton_ty m_endBTN;  ///< contains the button that gets displayed at the end of the credits
	ClassicButton_ty m_speedBTN; ///< contains the button that can toggle the credit speed
	float m_speed{ 0.07f }; ///< contains the base credit speed -> speed level 1
	int m_maxSpeedLevel{ 3 }; ///< contains the maximum speed level.
	int m_speedLevel{ 1 }; ///< contains the current speed level.
	std::vector<std::shared_ptr<UIElement>> m_movingElements; ///< contains the elements that are moving during the credits


	using creditEntries = std::vector<std::vector<std::string>>;
	static inline creditEntries const libVec = {
		{"raylib", "", "www.raylib.com", "https://www.raylib.com"},
		{"random lib", "", "www.github.com/mgerhold", "https://www.github.com/mgerhold"},
	};
	static inline creditEntries const inspirationVec = {
		{"my Dad"},
		{"coder2k"},
	};
	static inline creditEntries const testerVec = {
		{"Kiki3578"},
		{"TODO"},
	};
	static inline creditEntries const specialThanksVec = {
		{"coder2k"},
		{"r00tifant"},
		{"Clemens"},
		{"CrazyNightowl01"},
		{"NECROMENZER"},
		{"german coding commuinty on twitch"},
		{"the discord of coder2k"},
		{"TODO: more to come"},
	};
	static inline creditEntries const contactVec = {
		{"discord", "", "www.discord.gg/JG5fsFZqEE", "https://www.discord.gg/JG5fsFZqEE"},
		{"twitch", "", "www.twitch.tv/codingPurpurTentakel", "https://www.twitch.tv/codingpurpurtentakel"},
		{"gitHub", "", "www.github.com/PurpurTentakel97", "https://www.github.com/PurpurTentakel97"},
	};


	/**
	 * initializes all ui elements.
	 * contains all the text.
	 * connects the actions.
	 */
	void Initialize();
	/**
	 * adds an element ass moving element an into the normal elements.
	 */
	void AddMovingElement(std::shared_ptr<UIElement> element);

	/**
	 * increases the speed level by one.
	 * resets to 1 once the max speed level gets crossed.
	 */
	void ToggleSpeedLevel();
	/**
	 * moves the credits.
	 * returns if the credits currently are not moving.
	 * moves all elements in moving elements.
	 */
	void Move();
	/**
	 * checks if the credits are finished.
	 * sets moving to false if so.
	 */
	void CheckCreditsFinished();

public:
	/**
	 * ctor
	 * only initialization.
	 */
	CreditsScene();

	/**
	 * sets moving to true when the title is fully animated.
	 * calls the moving elements to move as long as moving is true.
	 */
	void CheckAndUpdate(Vector2 const& mousePosition, AppContext_ty_c appContext) override;
	/**
	 * sets the new resolution.
	 * calls all elements zu resize.
	 */
	void Resize(AppContext_ty_c appContext) override;
};
