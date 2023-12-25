//
// Purpur Tentakel
// 05.10.2022
//

#pragma once
#include "CellPopUp.h"
#include "ui_lib/ColorPicker.h"

/**
 * provides a specific type of the cell popup for colors.
 */
class ColorCellPopUp final : public CellPopUp {
private:
    ColorPicker_ty m_colorPicker; ///< contains a pointer of a color picker for choosing a new color.
    std::function<void(Color)> m_onClick{ [](Color) {
    } }; ///< contains the onClick lambda that gets called when the new color is accepted

    /**
	 * gets the new color from the color picker and calls the onClick.
	 * set should close afterword's.
	 */
    void SetValue() override;

public:
    /**
	 * ctor.
	 * only initialisation.
	 */
    ColorCellPopUp(
            Vector2 pos,
            Vector2 size,
            Alignment alignment,
            std::string const& title,
            AssetType infoTexture,
            Color currentColor,
            std::function<void(Color)> onClick
    );
};
