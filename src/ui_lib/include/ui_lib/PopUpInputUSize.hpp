//
// Purpur Tentakel
// 04.01.2024
//


#include "PopUpInput.hpp"

namespace uil {
    class PopUpInputUSize final : public PopUpInput {
    private:
        InputLine_ty m_inputLine;
        std::function<void(utl::usize)> m_onClick{ [](utl::usize) {} };

        void SetValue() override;

    public:
        PopUpInputUSize(Vector2 pos,
                        Vector2 size,
                        Alignment alignment,
                        std::string const& title,
                        app::AssetType infoTexture,
                        utl::usize currentValue,
                        std::function<void(utl::usize)> onClick);
    };
} // namespace ui
