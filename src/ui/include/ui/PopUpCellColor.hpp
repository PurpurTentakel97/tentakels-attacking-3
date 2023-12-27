//
// Purpur Tentakel
// 05.10.2022
//

#pragma once
#include "PopUpCell.hpp"
#include <ui_lib/ColorPicker.hpp>


class ColorCellPopUp final : public CellPopUp {
private:
    ColorPicker_ty m_colorPicker;
    std::function<void(Color)> m_onClick{ [](Color) {} };

    void SetValue() override;

public:
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
