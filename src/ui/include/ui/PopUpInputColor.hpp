//
// Purpur Tentakel
// 05.10.2022
//

#pragma once

#include "PopUpInput.hpp"
#include <ui_lib/ColorPicker.hpp>


namespace ui {
    class PopUpInputColor final : public PopUpInput {
    private:
        uil::ColorPicker_ty m_colorPicker;
        std::function<void(Color)> m_onClick{ [](Color) {} };

        void SetValue() override;

    public:
        PopUpInputColor(Vector2 pos,
                Vector2 size,
                uil::Alignment alignment,
                std::string const& title,
                app::AssetType infoTexture,
                Color currentColor,
                std::function<void(Color)> onClick
        );
    };
} // namespace ui
