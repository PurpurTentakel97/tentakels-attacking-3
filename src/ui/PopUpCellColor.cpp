//
// Purpur Tentakel
// 05.10.2022
//

#include "PopUpCellColor.hpp"
#include "AppContext.hpp"
#include <helper/HFocusEvents.hpp>
#include <helper/HGeneral.hpp>

void ColorCellPopUp::SetValue() {
    m_onClick(m_colorPicker->GetColor());
    SetShouldClose();
}

ColorCellPopUp::ColorCellPopUp(
        Vector2 pos,
        Vector2 size,
        Alignment alignment,
        std::string const& title,
        AssetType infoTexture,
        Color currentColor,
        std::function<void(Color)> onClick
)
    : CellPopUp{ pos, size, alignment, title, infoTexture },
      m_onClick{ onClick } {

    AppContext_ty_c appContext{ AppContext::GetInstance() };

    auto acceptBtn = InitializeAcceptButton();
    acceptBtn->SetOnClick([this]() { this->SetValue(); });

    auto colorPicker = std::make_shared<ColorPicker>(
            3,
            GetElementPosition(m_pos, m_size, 0.5f, 0.5f),
            GetElementSize(m_size, 0.5f, 0.38f),
            Alignment::MID_MID,
            true
    );

    AddFocusElement(colorPicker.get(), true);
    SelectFocusElement(colorPicker.get(), true);

    colorPicker->SetInitialColor(currentColor);
    colorPicker->SetCellFocuses(appContext);

    m_elements.push_back(colorPicker);
    m_colorPicker = colorPicker;
}
