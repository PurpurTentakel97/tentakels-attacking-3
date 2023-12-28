//
// Purpur Tentakel
// 30.05.2023
//

#pragma once
#include "UIElement.hpp"

class LineDrag final : public UIElement {
private:
    Vector2 m_start;
    Vector2 m_end;
    float m_thick;
    Color m_color;
    std::function<void(Vector2, Vector2)> m_callback;
    bool m_render{ false };

public:
    LineDrag(float thick, Color color, std::function<void(Vector2, Vector2)> callback);

    [[nodiscard]] Vector2 GetStart() const;

    [[nodiscard]] Vector2 GetEnd() const;

    void SetThick(float thick);

    [[nodiscard]] float GetThick() const;

    void SetColor(Color color);

    [[nodiscard]] Color GetColor() const;

    void SetCallback(std::function<void(Vector2, Vector2)> callback);

    void ClearCallback();

    void CheckAndUpdate(Vector2 const& mousePosition, app::AppContext_ty_c) override;

    void Render(app::AppContext_ty_c) override;
};
