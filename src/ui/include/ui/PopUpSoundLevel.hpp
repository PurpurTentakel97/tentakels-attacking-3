//
// Purpur Tentakel
// 14.11.2022
//

#pragma once

#include <alias/AliasUiLib.hpp>
#include <ui_lib/PopUp.hpp>


namespace ui {
    class SoundLevelPopUp final : public uil::PopUp {
    private:
        uil::Slider_ty m_slider;
        uil::CheckBox_ty m_checkBox;
        uil::ClassicButton_ty m_acceptBtn;

        void Initialize();

    public:
        SoundLevelPopUp(
                Vector2 pos,
                Vector2 size,
                uil::Alignment alignment,
                std::string const& title,
                std::string& subTitle
        );

        void Render(app::AppContext_ty_c appContext) override;
    };
} // namespace ui
