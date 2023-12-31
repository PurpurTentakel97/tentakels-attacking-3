//
// Purpur Tentakel
// 03.10.2022
//

#pragma once

#include "PopUpInput.hpp"
#include <ui_lib/InputLine.hpp>


namespace ui {
    template<utl::InputValueTypeCol T>
    class PrimitiveCellPopUp final : public PopUpInput {
    private:
        std::shared_ptr<uil::InputLine> m_inputChange;
        std::function<void(T)> m_onClick{ [](T) {} };

        void SetValue() override {
            m_onClick(m_inputChange->Value<T>());
            SetShouldClose();
        }

    public:
        PrimitiveCellPopUp(
                Vector2 const pos,
                Vector2 const size,
                uil::Alignment const alignment,
                std::string const& title,
                app::AssetType const infoTexture,
                T const currentValue,
                std::function<void(T)> const onClick
        )
            : PopUpInput{ pos, size, alignment, title, infoTexture },
              m_onClick{ onClick } {

            app::AppContext_ty_c appContext{ app::AppContext::GetInstance() };

            auto acceptBtn = InitializeAcceptButton();
            acceptBtn->SetOnClick([this]() { this->SetValue(); });

            auto inputChance = std::make_shared<uil::InputLine>(
                    3,
                    hlp::GetElementPosition(m_pos, m_size, 0.5f, 0.55f),
                    hlp::GetElementSize(m_size, 0.9f, 0.2f),
                    uil::Alignment::MID_MID,
                    T{}
            );

            eve::NewFocusPopUpElementEvent event{ inputChance.get() };
            appContext.eventManager.InvokeEvent(event);

            eve::SelectFocusPopUpElementEvent event2{ inputChance.get() };
            appContext.eventManager.InvokeEvent(event2);
            inputChance->SetValue(currentValue);
            inputChance->SetPlaceholderText(
                    appContext.languageManager.Text("ui_primitive_cell_popup_input_line_placeholder_text")
            );

            m_elements.push_back(inputChance);
            m_inputChange = inputChance;
        }
    };
} // namespace ui
