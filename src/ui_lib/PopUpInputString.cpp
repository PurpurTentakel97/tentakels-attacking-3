//
// Purpur Tentakel
// 04.01.2024
//

#include "PopUpInputString.hpp"
#include "InputLine.hpp"
#include <helper/HFocusEvents.hpp>

namespace uil {
    void PopUpInputString::SetValue() {
        m_onClick(m_inputLine->Value<std::string>());
        SetShouldClose();
    }
    PopUpInputString::PopUpInputString(Vector2 const pos,
                                       Vector2 const size,
                                       Alignment const alignment,
                                       std::string const& title,
                                       app::AssetType const infoTexture,
                                       std::string const& currentValue,
                                       std::function<void(std::string const&)> onClick)
        : PopUpInput{ pos, size, alignment, title, infoTexture },
          m_onClick{ std::move(onClick) } {

        auto acceptBtn = InitializeAcceptButton();
        acceptBtn->SetOnClick([this]() { this->SetValue(); });

        m_inputLine = std::make_shared<InputLine>(3,
                                                  hlp::GetElementPosition(m_pos, m_size, 0.5f, 0.5f),
                                                       hlp::GetElementSize(m_size, 0.8f, 0.2f),
                                                  Alignment::MID_MID,
                                                  currentValue);

        hlp::AddFocusElement(m_inputLine.get(), true);
        hlp::SelectFocusElement(m_inputLine.get(), true);

        m_elements.push_back(m_inputLine);
    }
} // namespace ui
