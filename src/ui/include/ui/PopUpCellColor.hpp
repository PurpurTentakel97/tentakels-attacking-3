//
// Purpur Tentakel
// 05.10.2022
//

#pragma once

#include "PopUpCell.hpp"
#include <ui_lib/ColorPicker.hpp>


namespace ui {
    class ColorCellPopUp final : public CellPopUp {
    private:
        uil::ColorPicker_ty m_colorPicker;
        std::function<void(Color)> m_onClick{ [](Color) {} };

        void SetValue() override;

    public:
        ColorCellPopUp(
                Vector2 pos,
                Vector2 size,
                uil::Alignment alignment,
                std::string const& title,
                app::AssetType infoTexture,
                Color currentColor,
                std::function<void(Color)> onClick
        );
    };
} // namespace ui
