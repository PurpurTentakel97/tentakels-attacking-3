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
        Vector2 const pos,
        Vector2 const size,
        Alignment const alignment,
        std::string const& title,
        AssetType const infoTexture,
        Color const currentColor,
        std::function<void(Color)> onClick
)
    : CellPopUp{ pos, size, alignment, title, infoTexture },
      m_onClick{ std::move(onClick) } {

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
