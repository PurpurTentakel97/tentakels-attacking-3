//
// Purpur Tentakel
// 23.07.2023
//

#include "ShipCountRing.hpp"
#include <alias/AliasCustomRaylib.hpp>
#include <app/AppContext.hpp>

void CountRing::CalculateRing() {
    cst::Resolution_ty_c resolution{ app::AppContext::GetInstance().GetResolution() };
    float diff{ m_relativeMaxRingSize - m_relativeDotSize };
    float factor{ static_cast<float>(m_currentCount) / static_cast<float>(m_maxCount) };
    diff *= factor;
    if (diff < 0.001f) {
        diff = 0.001f;
    }
    diff += m_relativeDotSize;
    diff *= resolution.x;
    m_absoluteRingSize = { diff };
}

CountRing::CountRing(
        Vector2 const pos,
        Vector2 const size,
        Alignment const alignment,
        float const dotSize,
        float const ringSize,
        int const currentCount,
        int const maxCount
)
    : UIElement{ pos, size, alignment },
      m_relativeDotSize{ dotSize },
      m_relativeMaxRingSize{ ringSize },
      m_currentCount{ currentCount },
      m_maxCount{ maxCount } {

    Update();
}

bool CountRing::IsOverlapping(Rectangle const& rect) const {
    return CheckCollisionCircleRec(m_absolutePos, m_absoluteRingSize, rect);
}

void CountRing::Update() {
    cst::Resolution_ty_c resolution{ app::AppContext::GetInstance().GetResolution() };
    m_absolutePos = { m_collider.x + m_collider.width / 2, m_collider.y + m_collider.height / 2 };
    m_absoluteDotSize = { m_relativeDotSize * resolution.x };
    CalculateRing();
}

int CountRing::GetMaxCount() const {
    return m_maxCount;
}

void CountRing::SetMaxCount(int const maxCount) {
    m_maxCount = maxCount;
}

int CountRing::GetCurrentCount() const {
    return m_currentCount;
}

void CountRing::SetCurrentCount(int const currentCount) {
    m_currentCount = currentCount;
}

Color CountRing::GetDotColor() const {
    return m_dotColor;
}

void CountRing::SetDotColor(Color const color) {
    m_dotColor = color;
}

Color CountRing::GetRingColor() const {
    return m_ringColor;
}

void CountRing::SetRingColor(Color const color) {
    m_ringColor = color;
}

void CountRing::SetPosition(Vector2 const newPos) {
    UIElement::SetPosition(newPos);
    Update();
}

void CountRing::CheckAndUpdate(Vector2 const& mousePosition, app::AppContext_ty_c appContext) {
    UIElement::CheckAndUpdate(mousePosition, appContext);
}

void CountRing::Render(app::AppContext_ty_c) {
    if (m_currentCount == 0) {
        return;
    }

    DrawCircleV(m_absolutePos, m_absoluteRingSize, m_ringColor);

    DrawCircleV(m_absolutePos, m_absoluteDotSize, m_dotColor);
}

void CountRing::Resize(app::AppContext_ty_c appContext) {
    UIElement::Resize(appContext);
    Update();
}
