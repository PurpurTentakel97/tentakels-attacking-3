//
// Purpur Tentakel
// 23.07.2023
//

#pragma once

#include "UIElement.hpp"


namespace uil {
    class CountRing final : public UIElement {
    private:
        Vector2 m_absolutePos{};
        float m_relativeDotSize;
        float m_absoluteDotSize{};
        float m_relativeMaxRingSize;
        float m_absoluteRingSize{};
        utl::usize m_currentCount;
        utl::usize m_maxCount;
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
                utl::usize currentCount,
                utl::usize maxCount
        );


        [[nodiscard]] bool IsOverlapping(Rectangle const& rect) const;


        void Update();

        [[nodiscard]] utl::usize GetMaxCount() const;

        void SetMaxCount(utl::usize maxCount);

        [[nodiscard]] utl::usize GetCurrentCount() const;

        void SetCurrentCount(utl::usize currentCount);

        [[nodiscard]] Color GetDotColor() const;

        void SetDotColor(Color color);

        [[nodiscard]] Color GetRingColor() const;

        void SetRingColor(Color color);

        void SetPosition(Vector2 newPos) override;

        void CheckAndUpdate(Vector2 const& mousePosition, app::AppContext_ty_c appContext) override;

        void Render(app::AppContext_ty_c appContext) override;

        void Resize(app::AppContext_ty_c appContext) override;
    };
} // namespace uil
