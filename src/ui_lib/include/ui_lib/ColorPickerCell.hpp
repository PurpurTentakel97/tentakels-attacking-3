//
// Purpur Tentakel
// 05.10.2022
//

#pragma once

#include "Focusable.hpp"
#include "Hover.hpp"
#include "UIElement.hpp"
#include <alias/AliasUILib.hpp>

class ColorPickerCell final : public UIElement, public Focusable {
private:
    bool m_enabled{ true };
    Color m_color;
    ColorPicker* m_colorPicker;
    Hover m_hover;

    void SetColor() const;

public:
    ColorPickerCell(
            unsigned int ID,
            Vector2 pos,
            Vector2 size,
            Alignment alignment,
            Color color,
            ColorPicker* colorPicker
    );

    [[nodiscard]] Color GetColor() const;

    [[nodiscard]] bool IsBlankCell() const;

    void SetEnabled(bool enabled);

    [[nodiscard]] bool IsEnabled() const override;

    [[nodiscard]] Rectangle GetCollider() const override;

    void CheckAndUpdate(Vector2 const& mousePosition, app::AppContext_ty_c appContext) override;

    void Render(app::AppContext_ty_c appContext) override;
};
