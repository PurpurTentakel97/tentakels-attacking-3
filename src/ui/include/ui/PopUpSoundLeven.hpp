//
// Purpur Tentakel
// 14.11.2022
//

#pragma once

#include <alias/AliasUiLib.hpp>
#include <ui_lib/PopUp.hpp>

class SoundLevelPopUp final : public PopUp {
private:
    Slider_ty m_slider;
    CheckBox_ty m_checkBox;
    ClassicButton_ty m_acceptBtn;

    void Initialize();

public:
    SoundLevelPopUp(Vector2 pos, Vector2 size, Alignment alignment, std::string const& title, std::string& subTitle);

    void Render(app::AppContext_ty_c appContext) override;
};
