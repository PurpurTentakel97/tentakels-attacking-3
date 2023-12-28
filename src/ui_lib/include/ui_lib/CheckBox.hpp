//
// Purpur Tentakel
// 23.10.2022
//

#pragma once
#include "Focusable.hpp"
#include "UIElement.hpp"
#include <functional>


class CheckBox final : public UIElement, public Focusable {
private:
    bool m_isEnabled{ true };
    bool m_isChecked{ false };
    bool m_isHovered{ false };

    unsigned int m_ID;

    Texture* m_texture;
    Rectangle m_textureRec{};

    std::function<void(unsigned int, bool)> m_onCheck{ [](unsigned int, bool) {} };


    void Check(AppContext_ty_c appContext);

public:
    CheckBox(unsigned int focusID, Vector2 pos, float height, Alignment alignment, unsigned int checkBoxID);

    void SetOnCheck(std::function<void(unsigned int, bool)> onCheck);

    [[nodiscard]] unsigned int GetID() const;

    void SetChecked(bool isChecked);

    [[nodiscard]] bool IsChecked() const;

    void SetEnabled(bool isEnabled);

    [[nodiscard]] bool IsEnabled() const override;

    [[nodiscard]] Rectangle GetCollider() const override;

    void CheckAndUpdate(Vector2 const& mousePosition, AppContext_ty_c appContext) override;

    void Render(AppContext_ty_c appContext) override;

    void Resize(AppContext_ty_c appContext) override;
};
