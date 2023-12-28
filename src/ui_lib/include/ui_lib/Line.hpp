//
// Purpur Tentakel
// 06.10.2022
//

#pragma once
#include "UIElement.hpp"


class Line final : public UIElement {
private:
    Vector2 m_start;
    Vector2 m_end;
    float m_thick;
    Color m_color;

public:
    Line(Vector2 start, Vector2 end, float thick, Color color);

    void Render(app::AppContext_ty_c appContext) override;

    virtual void Update();

    [[nodiscard]] Vector2 GetStart() const;

    virtual void SetStart(Vector2 start);

    [[nodiscard]] Vector2 GetEnd() const;

    virtual void SetEnd(Vector2 end);

    [[nodiscard]] float GetThick() const;

    void SetThick(float thick);

    [[nodiscard]] Color GetColor() const;

    void SetColor(Color color);
};
