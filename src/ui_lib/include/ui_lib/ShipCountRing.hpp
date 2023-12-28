//
// Purpur Tentakel
// 23.07.2023
//

#pragma once
#include "UIElement.hpp"

class CountRing final : public UIElement {
private:
    Vector2 m_absolutePos{};
    float m_relativeDotSize;
    float m_absoluteDotSize{};
    float m_relativeMaxRingSize;
    float m_absoluteRingSize{};
    int m_currentCount;
    int m_maxCount;
    Color m_dotColor{ BLACK };
    Color m_ringColor{ GREY_50 };


    void CalculateRing();

public:
    CountRing(
            Vector2 pos,
            Vector2 size,
            Alignment alignment,
            float innerSize,
            float ringSize,
            int currentCount,
            int maxCount
    );


    [[nodiscard]] bool IsOverlapping(Rectangle const& rect) const;


    void Update();

    [[nodiscard]] int GetMaxCount() const;

    void SetMaxCount(int maxCount);

    [[nodiscard]] int GetCurrentCount() const;

    void SetCurrentCount(int currentCount);

    [[nodiscard]] Color GetDotColor() const;

    void SetDotColor(Color color);

    [[nodiscard]] Color GetRingColor() const;

    void SetRingColor(Color color);

    void SetPosition(Vector2 newPos) override;

    void CheckAndUpdate(Vector2 const& mousePosition, AppContext_ty_c appContext) override;

    void Render(AppContext_ty_c appContext) override;

    void Resize(AppContext_ty_c appContext) override;
};
