//
// Purpur Tentakel
// 04.01.2024
//

#include "PopUpInput.hpp"

namespace ui {
    class PopUpInputString final : public PopUpInput {
    private:
        uil::InputLine_ty m_inputLine;
        std::function<void(std::string const&)> m_onClick{ [](std::string const&) {} };

        void SetValue() override;

    public:
        PopUpInputString(Vector2 pos,
                         Vector2 size,
                         uil::Alignment alignment,
                         std::string const& title,
                         app::AssetType infoTexture,
                         std::string const& currentValue,
                         std::function<void(std::string const&)> onClick);
    };
} // namespace ui
