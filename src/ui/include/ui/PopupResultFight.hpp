//
// PurpurTentakel
// 06.07.23
//

#pragma once

#include "utils/FightResult.hpp"
#include <ui_lib/CountingNumber.hpp>
#include <ui_lib/PopUp.hpp>


namespace ui {
    class FightResultPopup : public uil::PopUp {
    private:
        using callback_ty = std::function<void()>;
        utl::FightResult const m_result;
        size_t m_index{ 1 };
        bool m_finishedCounting{ false };
        callback_ty m_callback{ []() {} };
        uil::CountingNumber_ty m_leftNumber;
        uil::CountingNumber_ty m_rightNumber;
        static inline std::string s_emptyString{};
        uil::Text_ty m_winText;
        uil::ClassicButton_ty m_closeBtn;

        void Initialize();

        void NextNumber(bool left);

        void NextNumber(uil::CountingNumber::Type, int, int, double, bool left);

        void SetLastStep();

        void SetEnd();

        void HandleButton();

    public:
        FightResultPopup(
                Vector2 pos,
                Vector2 size,
                uil::Alignment alignment,
                utl::FightResult result,
                callback_ty callback
        );
    };
} // namespace ui
