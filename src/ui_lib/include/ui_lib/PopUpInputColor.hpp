//
// Purpur Tentakel
// 05.10.2022
//

#pragma once

#include "ColorPicker.hpp"
#include "PopUpInput.hpp"


namespace uil {
    class PopUpInputColor final : public PopUpInput {
    private:
        ColorPicker_ty m_colorPicker;
        std::function<void(Color)> m_onClick{ [](Color) {} };

        void SetValue() override;

    public:
        PopUpInputColor(Vector2 pos,
                Vector2 size,
                        Alignment alignment,
                        std::string const& title,
                app::AssetType infoTexture,
                Color currentColor,
                std::function<void(Color)> onClick
        );
    };
} // namespace ui
