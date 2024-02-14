//
// Purpur Tentakel
// 14.02.2024
//

#include "PopUpResultGameEvent.hpp"

namespace ui {
    PopUpGameEventResult::PopUpGameEventResult(Vector2 pos,
                                               Vector2 size,
                                               uil::Alignment alignment,
                                               std::string const& title,
                                               std::string& text,
                                               callback_ty callback)
        : uil::MessagePopUp{
              pos, size, alignment, title, text, app::AssetType::EXCLAMATION_MARK, std::move(callback)
          } {
        m_colorBorder = RED;
        m_colorFill   = MAROON;
    }
} // namespace ui
