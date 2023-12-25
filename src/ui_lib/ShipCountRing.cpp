//
// Purpur Tentakel
// 23.07.2023
//

#include "ShipCountRing.h"
#include "AppContext.h"

void CountRing::CalculateRing() {
    Resolution_ty_c resolution{ AppContext::GetInstance().GetResolution() };
    float diff{ m_relativeMaxRingSize - m_relativeDotSize };
    float factor{ static_cast<float>(m_currentCount) / m_maxCount };
    diff *= factor;
    if (diff < 0.001f) { diff = 0.001f; }
    diff += m_relativeDotSize;
    diff *= resolution.x;
    m_absoluteRingSize = { diff };
}

CountRing::CountRing(Vector2 pos, Vector2 size, Alignment alignment,
    float dotSize, float ringSize, int currentCount, int maxCount)
    : UIElement{ pos, size, alignment }, m_relativeDotSize{ dotSize }, m_relativeMaxRingSize{ ringSize },
    m_currentCount{ currentCount }, m_maxCount{ maxCount } {
    
    Update();
}

bool CountRing::IsOverlapping(Rectangle const& rect) const {
    return CheckCollisionCircleRec(m_absolutePos, m_absoluteRingSize, rect);
}

void CountRing::Update() {
    Resolution_ty_c resolution{ AppContext::GetInstance().GetResolution() };
    m_absolutePos = {
        m_collider.x + m_collider.width / 2,
        m_collider.y + m_collider.height / 2
    };
    m_absoluteDotSize = { m_relativeDotSize * resolution.x };
    CalculateRing();
}

int CountRing::GetMaxCount() const {
    return m_maxCount;
}
void CountRing::SetMaxCount(int maxCount) {
    m_maxCount = maxCount;
}
int CountRing::GetCurrentCount() const {
    return m_currentCount;
}
void CountRing::SetCurrentCount(int currentCount) {
    m_currentCount = currentCount;
}
Color CountRing::GetDotColor() const {
    return m_dotColor;
}
void CountRing::SetDotColor(Color color) {
    m_dotColor = color;
}
Color CountRing::GetRingColor() const {
    return m_ringColor;
}
void CountRing::SetRingColor(Color color) {
    m_ringColor = color;
}
void CountRing::SetPosition(Vector2 newPos) {
    UIElement::SetPosition(newPos);
    Update();
}

void CountRing::CheckAndUpdate(Vector2 const& mousePosition, AppContext_ty_c appContext) {
    UIElement::CheckAndUpdate(mousePosition, appContext);
}
void CountRing::Render(AppContext_ty_c) {
    if (m_currentCount == 0) { return; }

    DrawCircleV(
        m_absolutePos,
        m_absoluteRingSize,
        m_ringColor
    );

    DrawCircleV(
        m_absolutePos,
        m_absoluteDotSize,
        m_dotColor
    );
}
void CountRing::Resize(AppContext_ty_c appContext) {
    UIElement::Resize(appContext);
    Update();
}
