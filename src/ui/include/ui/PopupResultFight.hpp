//
// PurpurTentakel
// 06.07.23
//

#pragma once

#include "utils/FightResult.hpp"
#include <ui_lib/CountingNumber.hpp>
#include <ui_lib/PopUp.hpp>

class FightResultPopup : public PopUp {
private:
    using callback_ty = std::function<void()>;
    utl::FightResult const m_result;
    size_t m_index{ 1 };
    bool m_finishedCounting{ false };
    callback_ty m_callback{ []() {} };
    CountingNumber_ty m_leftNumber;
    CountingNumber_ty m_rightNumber;
    static inline std::string s_emptyString{};
    Text_ty m_winText;
    ClassicButton_ty m_closeBtn;

    void Initialize();

    void NextNumber(bool left);

    void NextNumber(CountingNumber::Type, int, int, double, bool left);

    void SetLastStep();

    void SetEnd();

    void HandleButton();

public:
    FightResultPopup(Vector2 pos, Vector2 size, Alignment alignment, utl::FightResult result, callback_ty callback);
};
