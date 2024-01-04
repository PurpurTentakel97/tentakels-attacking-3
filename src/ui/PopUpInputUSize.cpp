//
// Purpur Tentakel
// 04.01.2024
//

#include "PopUpInputUSize.hpp"
#include <helper/HFocusEvents.hpp>
#include <ui_lib/InputLine.hpp>

namespace ui {
    void PopUpInputUSize::SetValue() {
        m_onClick(m_inputLine->Value<utl::usize>());
        SetShouldClose();
    }
    PopUpInputUSize::PopUpInputUSize(Vector2 const pos,
                                     Vector2 const size,
                                     uil::Alignment const alignment,
                                     std::string const& title,
                                     app::AssetType const infoTexture,
                                     utl::usize const currentValue,
                                     std::function<void(utl::usize)> onClick)
        : PopUpInput{ pos, size, alignment, title, infoTexture },
          m_onClick{ std::move(onClick) } {

        auto acceptBtn = InitializeAcceptButton();
        acceptBtn->SetOnClick([this]() { this->SetValue(); });

        m_inputLine = std::make_shared<uil::InputLine>(3,
                                                       hlp::GetElementPosition(m_pos, m_size, 0.5f, 0.5f),
                                                       hlp::GetElementSize(m_size, 0.8f, 0.2f),
                                                       uil::Alignment::MID_MID,
                                                       currentValue);

        hlp::AddFocusElement(m_inputLine.get(), true);
        hlp::SelectFocusElement(m_inputLine.get(), true);

        m_elements.push_back(m_inputLine);
    }


} // namespace ui
