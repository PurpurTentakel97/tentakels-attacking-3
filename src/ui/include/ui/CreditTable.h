//
// Purpur Tentakel
// 05.11.2022
//

#pragma once
#include "ui_lib/Scene.h"

/**
 * provides a scene that displays a credits table.
 * contains link defines if every second string should be interpreted as a link that gets called.
 * if it contains link one row can contain 2 or 4 strings.
 * if nor one row can contain 1 or 2 strings. 
 * it will be generated one column or two columns.
 * all rows need to have the same amount of strings.
 */
class CreditTableScene : public Scene {
private:
	using creditEntries = std::vector<std::vector<std::string>>; ///< contains the datatype of the credit entries
	
	/**
	 * initializes all ui elements.
	 * connects the actions.
	 */
	void Initialize(std::string const& headline, creditEntries const& entries, bool containsLink);

public:
	/**
	 * ctor.
	 * only initialization.
 	 */
	CreditTableScene(Vector2 pos, Vector2 size, Alignment alignment, std::string const& headline,
		creditEntries const& entries, bool containsLink = false);
};
