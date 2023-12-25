//
// Purpur Tentakel
// 07.10.2022
//

#pragma once
#include <string>

/**
 * contains all text processing constants
 */
struct CTextProcessing final {
	static constexpr char cursor{ '_' }; ///< indicates where the next key input will be displayed.
	static inline const std::string prefix{ "..." }; ///< is mapped into a string to indicate its not the full string
	static constexpr int cursorOffset{ 5 }; ///< defines the general offset of the cursor in px
};
