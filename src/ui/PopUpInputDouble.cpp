//
// Purpur Tentakel
// 04.01.2024
//

#include "PopUpInputDouble.hpp"
#include <helper/HFocusEvents.hpp>
#include <ui_lib/InputLine.hpp>

namespace ui {
    void PopUpInputDouble::SetValue() {
        m_onClick(m_inputLine->Value<double>());
        SetShouldClose();
    }
    PopUpInputDouble::PopUpInputDouble(Vector2 const pos,
                                       Vector2 const size,
                                       uil::Alignment const alignment,
                                       std::string const& title,
                                       app::AssetType const infoTexture,
                                       double const curent_value,
                                       std::function<void(double)> onClick)

        : PopUpInput{ pos, size, alignment, title, infoTexture },
          m_onClick{ std::move(onClick) } {

        auto acceptBtn = InitializeAcceptButton();
        acceptBtn->SetOnClick([this]() { this->SetValue(); });

        m_inputLine = std::make_shared<uil::InputLine>(3,
                                                       hlp::GetElementPosition(m_pos, m_size, 0.5f, 0.5f),
                                                       hlp::GetElementSize(m_size, 0.8f, 0.2f),
                                                       uil::Alignment::MID_MID,
                                                       curent_value);

        hlp::AddFocusElement(m_inputLine.get(), true);
        hlp::SelectFocusElement(m_inputLine.get(), true);

        m_elements.push_back(m_inputLine);
    }


} // namespace ui
