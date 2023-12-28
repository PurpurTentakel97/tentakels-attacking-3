//
// Purpur Tentakel
// 01.12.2022
//

#pragma once
#include "Focusable.hpp"
#include "UIElement.hpp"
#include <functional>

class DropDownElement : public UIElement, public Focusable {
private:
    bool m_isEnabled{ true };
    bool m_hover{ false };
    unsigned int m_ID;
    float m_fontSize{};
    std::string m_toRender;
    std::string m_text;
    Vector2 m_textPosition{};
    std::function<void(unsigned int)> m_onClick{ [](unsigned int) {} };
    std::function<Rectangle(Rectangle)> m_getTemporaryCollider;

    void CreateToRender();

    void UpdateCollider() override;

    void UpdateColliderReverse() override;

public:
    DropDownElement(
            Vector2 pos,
            Vector2 size,
            Alignment alignment,
            unsigned int focusID,
            unsigned int ID,
            std::string text,
            std::function<Rectangle(Rectangle)> getTemporaryCollider
    );

    void CheckAndUpdate(Vector2 const&, app::AppContext_ty_c) override;

    void Render(app::AppContext_ty_c appContext) override;

    [[nodiscard]] bool IsEnabled() const override;

    void SetEnabled(bool isEnabled);

    void SetText(std::string text);

    [[nodiscard]] std::string GetText() const;

    [[nodiscard]] unsigned int GetID() const;

    void SetOnClick(std::function<void(unsigned int)> onClick);

    [[nodiscard]] Rectangle GetCollider() const override;
};
