//
// Purpur Tentakel
// 15.10.2022
//

#pragma once
#include "PopUpCell.hpp"
#include "ui_lib/InputLine.hpp"
#include <functional>

/**
 * provides a popup to choose witch player should be deleted.
 */
class DeletePlayerPopUp final : public CellPopUp {
private:
	InputLine_int_ty m_inputLine; ///< contains an input line for user input
	std::function<void(unsigned int)> m_onClick; ///< contains a lambda that gets called when the player cets deleted

	/**
	 * initializes all ui elements.
	 */
	void Initialize() override;
	/**
	 * gets the id from the input line and calls onClick.
	 * sets should close afterword's.
	 */
	void SetValue() override;

public:
	/**
	 * ctor.
	 * only initialisation.
	 */
	DeletePlayerPopUp(Vector2 pos, Vector2 size, Alignment alignemnt,
		std::string const& title, AssetType inpuTexture, std::function<void(unsigned int)> onClick);
};
