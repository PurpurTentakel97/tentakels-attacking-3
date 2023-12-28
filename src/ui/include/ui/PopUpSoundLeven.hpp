//
// Purpur Tentakel
// 14.11.2022
//

#pragma once
#include <ui_lib/PopUp.hpp>

class ClassicButton;
class Slider;
class CheckBox;


class SoundLevelPopUp final : public PopUp {
private:
    Slider_ty m_slider;
    CheckBox_ty m_checkBox;
    ClassicButton_ty m_acceptBtn;

    void Initialize();

public:
    SoundLevelPopUp(Vector2 pos, Vector2 size, Alignment alignment, std::string const& title, std::string& subTitle);

    void Render(AppContext_ty_c appContext) override;
};
