//
// Purpur Tentakel
// 14.02.2024
//

#pragma once

#include <ui_lib/PopUpMessage.hpp>

namespace ui {
    class PopUpGameEventResult : public uil::MessagePopUp {
    public:
        PopUpGameEventResult(Vector2 pos,
                             Vector2 size,
                             uil::Alignment alignment,
                             std::string const& title,
                             std::string& text,
                             callback_ty callback);
    };
} // namespace ui
