//
// Purpur Tentakel
// 15.10.2022
//

#include "PopUpPlayerDelete.hpp"
#include <helper/HFocusEvents.hpp>
#include <helper/HGeneral.hpp>


namespace ui {
    void DeletePlayerPopUp::Initialize() {

        auto acceptBtn = InitializeAcceptButton();
        acceptBtn->SetOnClick([this]() { this->SetValue(); });

        auto inputLine = std::make_shared<uil::InputLine<int>>(
                3,
                hlp::GetElementPosition(m_pos, m_size, 0.5f, 0.45f),
                hlp::GetElementSize(m_size, 0.5f, 0.1f),
                uil::Alignment::TOP_MID,
                5
        );
        inputLine->SetPlaceholderText("Player ID");
        m_inputLine = inputLine;
        m_elements.push_back(inputLine);

        hlp::AddFocusElement(m_inputLine.get(), true);
        hlp::SelectFocusElement(m_inputLine.get(), true);
    }

    void DeletePlayerPopUp::SetValue() {
        utl::usize const ID{ static_cast<utl::usize>(m_inputLine->GetValue()) };

        m_onClick(ID);

        SetShouldClose();
    }

    DeletePlayerPopUp::DeletePlayerPopUp(
            Vector2 const pos,
            Vector2 const size,
            uil::Alignment const alignment,
            std::string const& title,
            app::AssetType const inputTexture,
            std::function<void(utl::usize)> onClick
    )
        : CellPopUp{ pos, size, alignment, title, inputTexture },
          m_onClick{ std::move(onClick) } {

        Initialize();

        if (IsKeyReleased(KEY_ENTER) or IsKeyReleased(KEY_KP_ENTER)) {
            m_firstEnter = true;
        }
    }
} // namespace ui
