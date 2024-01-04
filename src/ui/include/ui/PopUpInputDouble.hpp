//
// Purpur Tentakel
// 04.01.2024
//

#include "PopUpInput.hpp"

namespace ui {
    class PopUpInputDouble final : public PopUpInput {
    private:
        uil::InputLine_ty m_inputLine;
        std::function<void(double)> m_onClick{ [](double) {} };

        void SetValue() override;

    public:
        PopUpInputDouble(Vector2 pos,
                         Vector2 size,
                         uil::Alignment alignment,
                         std::string const& title,
                         app::AssetType infoTexture,
                         double curent_value,
                         std::function<void(double)> onClick);
    };
} // namespace ui
