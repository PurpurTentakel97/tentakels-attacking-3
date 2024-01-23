//
// Purpur Tentakel
// 05.10.2022
//

#include "PopUpInputColor.hpp"
#include <app/AppContext.hpp>
#include <helper/HFocusEvents.hpp>
#include <helper/HGeneral.hpp>


namespace uil {
    void PopUpInputColor::SetValue() {
        m_onClick(m_colorPicker->GetColor());
        SetShouldClose();
    }

    PopUpInputColor::PopUpInputColor(Vector2 const pos,
            Vector2 const size,
                                     Alignment const alignment,
                                     std::string const& title,
            app::AssetType const infoTexture,
            Color const currentColor,
            std::function<void(Color)> onClick
    )
        : PopUpInput{ pos, size, alignment, title, infoTexture },
          m_onClick{ std::move(onClick) } {

        app::AppContext_ty_c appContext{ app::AppContext::GetInstance() };

        auto acceptBtn = InitializeAcceptButton();
        acceptBtn->SetOnClick([this]() { this->SetValue(); });

        auto colorPicker = std::make_shared<ColorPicker>(3,
                hlp::GetElementPosition(m_pos, m_size, 0.5f, 0.5f),
                                                         hlp::GetElementSize(m_size, 0.5f, 0.38f),
                                                         Alignment::MID_MID,
                                                         true
        );

        hlp::AddFocusElement(colorPicker.get(), true);
        hlp::SelectFocusElement(colorPicker.get(), true);

        colorPicker->SetInitialColor(currentColor);
        colorPicker->SetCellFocuses(appContext);

        m_elements.push_back(colorPicker);
        m_colorPicker = colorPicker;
    }
} // namespace ui
