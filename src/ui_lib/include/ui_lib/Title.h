//
// Purpur Tentakel
// 19.09.2022
//

#pragma once
#include "UIElement.hpp"
#include <array>
#include <vector>

/**
 * provides the title of the game.
 * can be animated.
 */
class Title final : public UIElement {
private:
	static inline std::array<std::string, 10> const m_postFixes{ ///< contains the moving part if the animation
	"  /-\\-",
	"  \\--/",
	"  -/--/",
	"  -\\_-\\",
	"  _/_\\",
	"  -_/\\-",
	"  --__-",
	"  __\\\\/",
	"  \\__-/",
	"  \\/-__",
	};
	std::vector<std::string>* m_title; ///< contains the title of the game split in lines
	float m_fontSize; ///< contains the absolute font size in px
	size_t m_charCount{ 0 }; ///< contains the current count of chars of the title that is drown so far
	size_t m_maxCharCount; ///< contains the total amount of chars in the title
	bool m_titleFinish; ///< contains if the animation is finished
	bool m_lastFinishedTitle{ false }; ///< contains if the animation was finished last tick

	/**
	 * enders the static title line by line.
	 */
	void RenderTitle(AppContext_ty_c appContext);
	/**
	 * renders the title sequent.
	 * every tick gets renders one character more.
	 * adds a random postFix to the string.
	 */
	void RenderTitleSequens(AppContext_ty_c appContext);

	/**
	 * measures the amount of characters in the title.
	 */
	void MeasureTitleLength();
	/**
	 * calculates the collider out of the title length and position.
	 */
	void SetCollider(AppContext_ty_c appContext);

	/**
	 * sets the title finished.
	 */
	void TitleFinish(AppContext_ty_c appContext);

public:
	/**
	 * ctor.
	 * loads the title.
	 * measures the title length.
	 * sets collider.
	 */
	Title(Vector2 pos, Vector2 size, Alignment alignment, bool drawTitle);

	/**
	 * title logic.
	 */
	void CheckAndUpdate(Vector2 const& mousePosition, AppContext_ty_c appContext) override;
	/**
	 * renders the title animation or the static title.
	 */
	void Render(AppContext_ty_c appContext) override;
	/**
	 * resizes the title.
	 */
	void Resize(AppContext_ty_c appContext) override;

	/**
	 * returns if the title animation has finished.
	 */
	[[nodiscard]] bool HasFinishedTitle() const;
	/**
	 * returns if the title finished this tick.
	 */
	[[nodiscard]] bool IsTitleFinished() const;
};
