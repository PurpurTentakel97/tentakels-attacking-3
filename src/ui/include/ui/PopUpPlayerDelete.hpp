//
// Purpur Tentakel
// 15.10.2022
//

#pragma once

#include "PopUpCell.hpp"
#include <functional>
#include <ui_lib/InputLine.hpp>


namespace ui {
    class DeletePlayerPopUp final : public CellPopUp {
    private:
        uil::InputLine_int_ty m_inputLine;
        std::function<void(utl::usize)> m_onClick;

        void Initialize() override;

        void SetValue() override;

    public:
        DeletePlayerPopUp(
                Vector2 pos,
                Vector2 size,
                uil::Alignment alignment,
                std::string const& title,
                app::AssetType inputTexture,
                std::function<void(utl::usize)> onClick
        );
    };
} // namespace ui
