//
// Purpur Tentakel
// 05.10.2022
//

#pragma once
#include "ColorPickerCell.hpp"
#include <functional>
#include <memory>
#include <vector>

class ColorPicker final : public UIElement, public Focusable {
private:
    bool m_isPopUp{};

    size_t m_countX{};
    size_t m_countY{};
    std::vector<std::unique_ptr<ColorPickerCell>> m_cells{};
    ColorPickerCell* m_currentColorCell{ nullptr };
    ColorPickerCell* m_previousColorCell{ nullptr };
    std::function<void()> m_onEnter{ []() {} };

    void Initialize();

    void SetUsedColors(app::AppContext_ty_c appContext);

    void SetColorFromFocus();

    void CheckForValidColor(app::AppContext_ty_c appContext);

public:
    ColorPicker(unsigned int ID, Vector2 pos, Vector2 size, Alignment alignment, bool isPopUp = false);

    ~ColorPicker() override;

    [[nodiscard]] Color GetColor() const;

    [[nodiscard]] bool HasColorChanced() const;

    bool SetInitialColor(Color color);

    bool SetColor(Color color);

    void SetOnEnter(std::function<void()> onEnter);

    void SetCellFocuses(app::AppContext_ty_c appContext);

    void SetEnabled(bool enabled, Color color);

    [[nodiscard]] bool IsEnabled() const override;

    [[nodiscard]] bool IsPopUp() const;

    void CheckAndUpdate(Vector2 const& mousePosition, app::AppContext_ty_c appContext) override;

    void Render(app::AppContext_ty_c appContext) override;

    void Resize(app::AppContext_ty_c appContext) override;

    [[nodiscard]] Rectangle GetCollider() const override;
};
